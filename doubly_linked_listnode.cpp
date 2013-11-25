#include "doubly_linked_listnode.h"
DListNode::DListNode(int id):id(id)//结点的id
{
}

bool DListNode::delNode(int ID_del)//删除结点ID_del,除非要删除的结点在，否则什么也不做
//且不准删除管理结点，即this指向的结点
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

bool DListNode::insertNode(int ID_insert,bool f1,bool f2,int succ_id)//插入结点ID_insert，且f1=true说明此结点为hull的表层结点
{   //在f1=true的情况下，f2=true说明插入的结点为顺时针方向hull表层的下一结点。
    DListNode* newnode=new DListNode(ID_insert);                                   //succ_id为要插入的结点的后一结点标识,且保证这种succ_id存在,否则不做事
    DListNode* next=m_ptrNext;
    DListNode* pre=m_ptrPre;                                     //此双向链表从前到后组织按顺时针方向的结点
    DListNode* p;
    if(ID_insert == this->getData()){//如果插入节点为头节点，返回false
      cout << "Waring: inserting head node: " << this->getData() << endl; 
      return false;
    }
    else if(searchNode(ID_insert)){
//       cout << "Warning: Node " << ID_insert << " already exit in Point:" << this->getData() << endl;
       //方案一：如果节点存在则不插入。
//       return false;
      //方案二：先删除原节点再插入——效果较方案一好。
      delNode(ID_insert);
    }
    if(f1)
    {
        if(f2)//将结点插在this指向的结点的后面一个位子
        {
//             cout << "Into true true! newId = " << newnode->getData() << endl;
            newnode->m_ptrNext=m_ptrNext;
            m_ptrNext=newnode;
            newnode->m_ptrPre=this;
            next->m_ptrPre=newnode;
        }
        else//将结点插在this指向的结点的前面一个位子
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
        p=this;//绝对不在this节点的前一或后一位置？？
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

int DListNode::succ(int id)//返回id的下一个结点的id号
{
    DListNode * ptr;
    ptr=this;
    do{
        if(ptr->getData()==id)
            return ptr->getNext()->getData();
        ptr=ptr->getNext();
    }while(ptr!=this);
    return this->id;//-1//如果仅一个节点则返回头节点id？？？
}
int DListNode::pred(int id)//返回id的前一个结点的id号
{
    DListNode * ptr;
    ptr=this;
    do{
        if(ptr->getData()==id)
            return ptr->getPre()->getData();
        ptr=ptr->getPre();
    }while(ptr!=this);
    return this->id;//如果仅一个节点则返回头节点id？？？
}

int DListNode::getSize(void)
{
    DListNode * ptr = this;
    int count = 0;//默认头节点必然存在且无法删除。
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

