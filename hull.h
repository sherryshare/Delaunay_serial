#ifndef HULL_H
#define HULL_H
#include "Point.h"
#include "doubly_linked_listnode.h"

#include <iostream>
using namespace std;
int is_left(Points & P,int id_a,int id_b,int id_c)//�����c������ab��߿ɾͷ���TURE,���ڽ������ֻ���ڶ������Բ������������ʡ�
{
    //�ӽ������P���ý��id�����꣨x��y������(P[id].x,P[id].y);
    //��������ab������ac������ķ�������Ƿ�����ߡ������ǵ������������Ϊz�᷽����˵����c������ab��ߣ��򷵻�TURE�����򷵻�FALSE
    //��������ab=��x1,y1,0)��ac=(x2,y2,0)�������x��y��z����z����
    cout << "is left start " << id_a << " + " << id_b << " + " << id_c << endl;
    if(id_c >= P.size() || id_c < 0) {
        cout << "Wrong input! id_c = " << id_c << endl;
        return -1;
    }
//     cout << "is left start " << id_a << " + " << id_b << " + " << id_c << endl;
    double z=(P[id_b][0]-P[id_a][0])*(P[id_c][1]-P[id_a][1])-(P[id_b][1]-P[id_a][1])*(P[id_c][0]-P[id_a][0]);
//     cout << "z = " << z << endl;
    if(z>0) {
        cout << "1 return z=" << z << endl;
        return 1;
    }
    else if(z<0) {
        cout << "0 return! z=" << z << endl;
        return 0;
    }
    else { //z==0
        cout << "2 return z=0" << endl;
        return 2;
    }
}

void hull_bottom(Points & P,int left,int right,int & id_bl,int & id_br)//��ײ���������Ϊ��id_bl,id_br��
{   //���hull�����ҽ����ұ�hull����߽���ʶ�ֱ�Ϊright��left
    //����id_bl,id_br,left,right��Ϊ�����ʶ
    DListNode* X,*Y,*Z;
    int a,b,c;
    int pre_bl,pre_br;
    id_bl = left;
    id_br = right;
    do
    {
        pre_bl = id_bl;
        pre_br = id_br;
        X=(DListNode*)(P[pre_bl].getHead());
        Y=(DListNode*)(P[pre_br].getHead());
        Z=(DListNode*)(Y->getPre());//��ʱ������
        a=X->getData();
        b=Y->getData();
        c=Z->getData();
//     cout << "enter while" << endl;
        while(is_left(P,a,b,c)==0)//Ѱ��id_br
        {
// 	cout << "into while!" << endl;//Z==Yʱ�������ѭ��
            Y=Z;
            Z=(DListNode*)(Z->getPre());
            b=Y->getData();
            c=Z->getData();
        }
        id_br=Y->getData();


        Z=(DListNode*)(X->getNext());//˳ʱ������
        a=Y->getData();
        b=X->getData();
        c=Z->getData();
//     while(is_left(P,a,b,c)==0)//Ѱ��id_bl--13/11/20�޸�
        while(is_left(P,a,b,c)==1)//Ѱ��id_bl
        {
//       cout << "into while!" << endl;
            X=Z;
            Z=(DListNode*)(Z->getNext());
            b=X->getData();
            c=Z->getData();
// 	cout << "b=" << b << " c=" << c << endl;
        }
        id_bl=X->getData();
        cout << "id_br=" << id_br << " id_bl=" << id_bl << endl;
    } while(id_bl!=pre_bl||id_br!=pre_br);
//     cout << "id_br=" << id_br << " id_bl=" << id_bl << endl;
}
void hull_top(Points & P,int left,int right,int & id_tl,int & id_tr)//�������������Ϊ��id_tl,id_tr��
{   //���hull�����ҽ����ұ�hull����߽���ʶ�ֱ�Ϊright��left
    //����id_tl,id_tr,left,right��Ϊ�����ʶ
    DListNode* X,*Y,*Z;
    int a,b,c;
    int pre_tl,pre_tr;
    id_tl = left;
    id_tr = right;
    do 
    {
        pre_tl = id_tl;
        pre_tr = id_tr;
        X=(DListNode*)(P[pre_tl].getHead());
        Y=(DListNode*)(P[pre_tr].getHead());
        Z=(DListNode*)(Y->getNext());//˳ʱ������
        a=X->getData();
        b=Y->getData();
        c=Z->getData();
//     while(is_left(P,a,b,c)==0)//Ѱ��id_tr
        while(is_left(P,a,b,c)==1)//Ѱ��id_tr--13/11/20�޸�
        {
            Y=Z;
            Z=(DListNode*)(Z->getNext());
            b=Y->getData();
            c=Z->getData();
        }
        id_tr=Y->getData();

        Z=(DListNode*)(X->getPre());//��ʱ������
        a=Y->getData();
        b=X->getData();
        c=Z->getData();
        while(is_left(P,a,b,c)==0)//Ѱ��id_tl
        {
            X=Z;
            Z=(DListNode*)(Z->getPre());
            b=X->getData();
            c=Z->getData();
        }
        id_tl=X->getData();
        cout << "id_tr=" << id_tr << " id_tl=" << id_tl << endl;
    } while(id_tl!=pre_tl || id_tr!=pre_tr);
}
#endif
