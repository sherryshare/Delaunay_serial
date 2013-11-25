#ifndef MERGE_H
#define MERGE_H
#include "hull.h"
#include <iostream>
using namespace std;


bool testDelaunayEdge(Points & P,int id_a,int id_b,int id_c,int id_d)//�������id_d�ڽ��id_a,id_b��id_c�����Բ�ڣ��ͷ���FALSE�����򷵻�TURE
{
    double  x1,x2,x3,x4,y1,y2,y3,y4;
    double  x,y,r,c;
    x1=P[id_a].x();
    x2=P[id_b].x();
    x3=P[id_c].x();
    x4=P[id_d].x();
    y1=P[id_a].y();
    y2=P[id_b].y();
    y3=P[id_c].y();
    y4=P[id_d].y();
    c = 2*(x3-x1)*(y2-y1)-2*((x2-x1)*(y3-y1));
    cout << "testDelaunayEdge " << id_a << "+" << id_b << "+" << id_c << "&" << id_d << endl;
    cout << "x1="<< x1 << " x2=" << x2 << " x3=" << x3 << " x4=" << x4 << endl;
    cout << "y1="<< y1 << " y2=" << y2 << " y3=" << y3 << " y4=" << y4 << endl;
    if(c == 0.0) {
        cout << "test false return c=" << c << endl;//altered 13/11/25 ������ɵ�Բֱ�����޴󣬱�������
        return false;
    }
    x=((y2-y1)*(y3*y3-y1*y1+x3*x3-x1*x1)-(y3-y1)*(y2*y2-y1*y1+x2*x2-x1*x1))/c;
    y=((x2-x1)*(x3*x3-x1*x1+y3*y3-y1*y1)-(x3-x1)*(x2*x2-x1*x1+y2*y2-y1*y1))/(-c);
    r=(x1-x)*(x1-x)+(y1-y)*(y1-y);
    if((x4-x)*(x4-x)+(y4-y)*(y4-y)>r) {
        cout << "test true return"<< endl;
        return true;
    }
    else {
        cout << "test false return"<< endl;
        return false;
    }
}
void merge(Points & P,int left,int right)//�����ұ߽���ʶΪright�����hull������߽���ʶΪleft���ұ�hull�ϲ�
{   //merge�ϲ�hull�����������hull��������ڵ���3�����ұ�hull�������Ϊ1��2�����
//???����ֻ�Ǻϲ�hull����δ�˼���Ե�ϲ����������ε�����
    bool rFlag = false;//�ж��ұ�hull�Ƿ��һ���ڵ㣬��Ϊtrue
    if(left==-1)//����û����hull����left=-1����˵������Ҫ�ϲ���
        return;
    if(P[left].getHead()->getSize() < 3) {
        cout << "The left hull size is less than 3." << endl;
        return;
    }
    if(P[right].getHead()->getSize()==1) {
        cout << "Right hull size = " << P[right].getHead()->getSize() << endl;
        rFlag = true;
    }
    int id_bl,id_br,id_tl,id_tr;
//     cout << "hull_bottom" << endl;
    hull_bottom(P,left,right,id_bl,id_br);//�˴����������޸ģ�����13/10/23������
    cout << "hull_bottom bl=" << id_bl << " + br=" << id_br << endl;
    hull_top(P,left,right,id_tl,id_tr);
    cout << "hull_top tl=" << id_tl << " + tr=" << id_tr << endl;
    bool fl,fr,f;
    DListNode *l=NULL,*r=NULL;
    l=P[id_bl].getHead();//����ߣ�id_bl,id_br)
    r=P[id_br].getHead();
    l->insertNode(id_br,true,false,0);//id_bl�����id_br
    r->insertNode(id_bl,true,true,0);//id_br�����id_bl
    cout << "l:";
    l->printAll();
    cout << "r:";
    r->printAll();
    l=P[id_tl].getHead();//����ߣ�id_tl,id_tr)
    r=P[id_tr].getHead();
    l->insertNode(id_tr,true,true,0);
    r->insertNode(id_tl,true,false,0);
    cout << "l:";
    l->printAll();
    cout << "r:";
    r->printAll();
    int R1,R2,R,L1,L2,L,preL,preR;
    DListNode* pR=NULL,*pL=NULL;
//     R=right;//deleted 13/11/25
//     L=left;//deleted 13/11/25
    R=id_br;
    L=id_bl;
//     cout << "start while" << endl;
    int count =0;//-----------����ѭ������Ϊ����ȥ����ѭ���ã�������ʵ��Ҫ
    while(!(id_bl==id_tl&&id_br==id_tr))
    {
        if(++count > 3) {
            cout << "Warning: force break!" << endl;
            break;//-----------����ѭ������Ϊ����ȥ����ѭ���ã�������ʵ��Ҫ
        }
        cout << "bl=" << id_bl << " tl=" << id_tl << " br=" << id_br << " tr=" << id_tr << endl;
        fl=false;
        fr=false;
        f=false;
        preL=L;
        preR=R;
        pL=P[L].getHead();
        pR=P[R].getHead();
        R1=pR->succ(L);//left��pR��������:l->insertNode(id_tr,true,true,0);
        cout << "R1=" << R1 << " L=" << L << " PR=" << pR->getData() << endl;
        if(R1!=R)//�ұߵ�hull��ֻ��һ���ڵ�--------??R����right
        {
//             if(is_left(P,L,R,R1)==1)
            if(is_left(P,L,R,R1)>=1)//13/11/25�����޸�
            {
                R2=pR->succ(R1);
                while(R2!=R&&R2!=R1&&!testDelaunayEdge(P,R1,L,R,R2))//R2��R1��L��R��ɵ����Բ��
                {
                    //ɾ��(R,R1)
                    pR->delNode(R1);//ɾ��R1
                    (P[R1].getHead())->delNode(R);//��R1Ϊͷ�ڵ��������ɾ��R
                    R1=R2;//R1ʼ�մ������L��R��������εĽڵ�
                    R2=pR->succ(R1);//���汸ѡ�ڵ�
		    cout << "L=" << L << " R=" << R << " R1=" << R1 << " R2=" << R2 << endl;
                }
            }
            else
                fr=true;
        }
        else//�ұߵ�hullֻ��һ���ڵ㣬��R
            f=true;

        L1=pL->pred(R);//rightΪ����pL��������:r->insertNode(id_tl,true,false,0);
        cout << "L1=" << L1 << " R=" << R << " L=" << pL->getData() << endl;
//         if(is_left(P,L,R,L1)==1)//=2�����ֱ�ӽ���else��fl=trueһ��whileѭ����R=R1
        if(is_left(P,L,R,L1)>=1)//13/11/25�����޸ģ�=2�����ɾ���ڵ�ʧ�ܣ��������˳�--��������֤���ַ�����ȷ������
// 	��fl=false,L1=pL->pred(L1),��β�ڵ�id,һ��whileѭ������testDelaunayEdge(P,L,R,R1,L1)==true�������ΪR=R1
	//ʵ����Խ�����������������ͬ
        {
            L2=pL->pred(L1);
            while(L2!=L&&L2!=L1&&!testDelaunayEdge(P,L,R,L1,L2))
            {
                //ɾ��(L,L1)
                pL->delNode(L1);
                (P[L1].getHead())->delNode(L);
                L1=L2;
                L2=pL->succ(L1);
		cout << "L=" << L << " R=" << R << " L1=" << L1 << " L2=" << L2 << endl;
            }
        }
        else
            fl=true;
        if(fr)
            L=L1;
        else
        {
            if(fl)
                R=R1;
            else
            {
                if(!f)
                {
                    if(testDelaunayEdge(P,L,R,R1,L1))
                        R=R1;
                    else//������if(is_left(P,L,R,L1)>=1)���������˳�whileѭ��
                        L=L1;
                }
                else
                    L=L1;
            }
        }
        id_bl=L;
        id_br=R;
        cout << "id_bl=" << id_bl << " id_br=" << id_br << endl;
        //����ߣ�L��R��
        if(!(id_bl==id_tl&&id_br==id_tr))//��(tl��tb)��ǰ���Ѳ��룬���ԾͲ�Ҫ�ٲ���
        {
            l=P[L].getHead();
            r=P[R].getHead();
            cout << "L=" << L << " R=" << R << " preL=" << preL << " preR=" << preR << endl;
            if(preL==L)
            {
                l->insertNode(R,false,false,preR);
//                 r->insertNode(L,false,false,r->succ(R));//deleted 13/11/25
                r->insertNode(L,false,false,L1);//added 13/11/25--if(is_left(P,L,R,L1)>=1)L1����仯Ӱ��˴����
		//������if(is_left(P,L,R,L1)>=1)��˴����붯��ʧ��
                cout << "perL==L\tl:";
                l->printAll();
                cout << "r:";
                r->printAll();
            }
            else
            {
                l->insertNode(R,false,false,preL);
                r->insertNode(L,false,false,R1);
                cout << "perR==R?\tl:";
                l->printAll();
                cout << "r:";
                r->printAll();
            }
        }

    }
}

#endif
