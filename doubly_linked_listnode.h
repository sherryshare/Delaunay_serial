#ifndef DOUBLY_LINKED_LISTNODE_H
#define DOUBLY_LINKED_LISTNODE_H

#include <iostream>
using namespace std;
class DListNode //˫��ѭ������
{
public:
    DListNode(int id);//����id
    ~DListNode() {}
    int					getData() const {
        return id;
    }
    DListNode *	getNext() const {
        return m_ptrNext;   //getNext()��getPre()����hull��˳ʱ��Ϊ׼�ֱ���hull������һ����ǰһ���
    }
    DListNode *		getPre() const {
        return m_ptrPre;
    }
    void	setNext(DListNode * next) {
        m_ptrNext = next;   //getNext()��getPre()����hull��˳ʱ��Ϊ׼�ֱ���hull������һ����ǰһ���
    }
    void		setPre(DListNode * pre) {
        m_ptrPre = pre;
    }
    bool                delNode(int ID_del);//Unchecked!!//����ɾ����������Ϊͷ���POINTָ����Ǹ�˫������ڵ����ڲ����������������ʹ�õ�
    bool                insertNode(int ID_insert,bool f1,bool f2,int succ_id);//Half-unchecked!!//������ID_insert����f1=TURE˵���˽��Ϊhull�ı����
    bool		searchNode(int ID);
    int                 pred(int id);//����id��ǰһ������id��
    int                 succ(int id);//����id����һ������id��
    //void				setNext(TMSharedDataPtr ptr) {m_ptrNext = ptr;}
    int 		getSize(void);
    
    void		printAll(void);

private:
    int                                 id;
    DListNode *						m_ptrNext;//ע�������˫���������Ա����Ϊ���ĵ��ڽӽ���ǰ�˳ʱ�뷽����֯�Ĵ�ǰ���������
    //����������һ��POINT���Ǳ�ͷ��ͷ���ָ�򱾽�㣬��������nextָ��Ľ�㱣֤Ϊhull˳ʱ�뷽�����һ�������
    //������preָ��Ľ�㱣֤Ϊhull˳ʱ�뷽���ǰһ�������
    DListNode *						m_ptrPre;
};
#endif
