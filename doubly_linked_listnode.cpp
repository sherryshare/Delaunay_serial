#include "doubly_linked_listnode.h"
DListNode::DListNode(int id):id(id)//����id
{
}

bool DListNode::delNode(int ID_del)//ɾ�����ID_del,����Ҫɾ���Ľ���ڣ�����ʲôҲ����
//�Ҳ�׼ɾ�������㣬��thisָ��Ľ��
{
    DListNode * ptr1,* ptr2;
    ptr1=this;
    ptr2=m_ptrNext;
    while(ptr2!=this)
    {
        if(ptr2->getData()==ID_del)
        {
            ptr1->m_ptrNext=ptr2->getNext();
            ptr2->m_ptrNext->m_ptrPre=ptr1;
            delete ptr2;
            return true;
        }
        else {
            ptr1=ptr2;
            ptr2=ptr2->getNext();
        }
    }
    return false;
}

bool DListNode::searchNode(int id)
{
    DListNode * ptr=this;
    do{
      if(ptr->getData()==id)
	return true;
      ptr = ptr->getNext();
    }while(ptr!=this);
    return false;
}

bool DListNode::insertNode(int ID_insert,bool f1,bool f2,int succ_id)//������ID_insert����f1=true˵���˽��Ϊhull�ı����
{   //��f1=true������£�f2=true˵������Ľ��Ϊ˳ʱ�뷽��hull������һ��㡣
    DListNode* newnode=new DListNode(ID_insert);                                   //succ_idΪҪ����Ľ��ĺ�һ����ʶ,�ұ�֤����succ_id����,��������
    DListNode* next=m_ptrNext;
    DListNode* pre=m_ptrPre;                                     //��˫�������ǰ������֯��˳ʱ�뷽��Ľ��
    DListNode* p;
    if(ID_insert == this->getData()){//�������ڵ�Ϊͷ�ڵ㣬����false
      cout << "Waring: inserting head node: " << this->getData() << endl; 
      return false;
    }
    else if(searchNode(ID_insert)){
//       cout << "Warning: Node " << ID_insert << " already exit in Point:" << this->getData() << endl;
       //����һ������ڵ�����򲻲��롣
//       return false;
      //����������ɾ��ԭ�ڵ��ٲ��롪��Ч���Ϸ���һ�á�
      delNode(ID_insert);
    }
    if(f1)
    {
        if(f2)//��������thisָ��Ľ��ĺ���һ��λ��
        {
//             cout << "Into true true! newId = " << newnode->getData() << endl;
            newnode->m_ptrNext=m_ptrNext;
            m_ptrNext=newnode;
            newnode->m_ptrPre=this;
            next->m_ptrPre=newnode;
        }
        else//��������thisָ��Ľ���ǰ��һ��λ��
        {
//             cout << "Into true false! newId = " << newnode->getData() << endl;
            newnode->m_ptrNext=this;
            newnode->m_ptrPre=pre;
            m_ptrPre=newnode;
            pre->m_ptrNext=newnode;
        }
    }
    else
    {
        p=this;//���Բ���this�ڵ��ǰһ���һλ�ã���
        do
        {
            if(p->getData()==succ_id)
            {
                newnode->m_ptrNext=p;
                newnode->m_ptrPre=p->getPre();
                p->getPre()->m_ptrNext=newnode;
                p->m_ptrPre=newnode;
                return true;
            }
            p=p->getNext();
        } while(p!=this);
	cout << "Warning: inserting " << ID_insert << " to " << this->getData() << " before " << succ_id << " failed!" << endl;
	return false;
    }
    return true;
}

int DListNode::succ(int id)//����id����һ������id��
{
    DListNode * ptr;
    ptr=this;
    do{
        if(ptr->getData()==id)
            return ptr->getNext()->getData();
        ptr=ptr->getNext();
    }while(ptr!=this);
    return this->id;//-1//�����һ���ڵ��򷵻�ͷ�ڵ�id������
}
int DListNode::pred(int id)//����id��ǰһ������id��
{
    DListNode * ptr;
    ptr=this;
    do{
        if(ptr->getData()==id)
            return ptr->getPre()->getData();
        ptr=ptr->getPre();
    }while(ptr!=this);
    return this->id;//�����һ���ڵ��򷵻�ͷ�ڵ�id������
}

int DListNode::getSize(void)
{
    DListNode * ptr = this;
    int count = 0;//Ĭ��ͷ�ڵ��Ȼ�������޷�ɾ����
    do{      
      count ++;
//     cout << count << ":ID=" << ptr->getData() << ' ';
        ptr = ptr->getNext();
    }while(ptr!=this);
//   cout << endl;
    return count;
}

void DListNode::printAll(void )
{
  DListNode * ptr=this;
  int i=0;
//   cout << "prsintAll: ";
  do{
    cout << i << ":ID=" << ptr->getData() << ' ';
    i++;
    ptr = ptr->getNext();
  }while(ptr!=this);
  cout << endl;
}

