#ifndef DOUBLY_LINKED_LISTNODE_H
#define DOUBLY_LINKED_LISTNODE_H

#include <iostream>
using namespace std;
class DListNode //双向循环链表
{
public:
    DListNode(int id);//结点的id
    ~DListNode() {}
    int					getData() const {
        return id;
    }
    DListNode *	getNext() const {
        return m_ptrNext;   //getNext()和getPre()都以hull的顺时针为准分别求hull外表的下一结点和前一结点
    }
    DListNode *		getPre() const {
        return m_ptrPre;
    }
    void	setNext(DListNode * next) {
        m_ptrNext = next;   //getNext()和getPre()都以hull的顺时针为准分别求hull外表的下一结点和前一结点
    }
    void		setPre(DListNode * pre) {
        m_ptrPre = pre;
    }
    bool                delNode(int ID_del);//Unchecked!!//插入删除操作都是为头结点POINT指向的那个双向链表节点用于操作其管理的其他结点使用的
    bool                insertNode(int ID_insert,bool f1,bool f2,int succ_id);//Half-unchecked!!//插入结点ID_insert，且f1=TURE说明此结点为hull的表层结点
    bool		searchNode(int ID);
    int                 pred(int id);//返回id的前一个结点的id号
    int                 succ(int id);//返回id的下一个结点的id号
    //void				setNext(TMSharedDataPtr ptr) {m_ptrNext = ptr;}
    int 		getSize(void);
    
    void		printAll(void);

private:
    int                                 id;
    DListNode *						m_ptrNext;//注：这里的双向链表是以本结点为中心的邻接结点们按顺时针方向组织的从前到后的链表。
    //结点数组里的一个POINT算是表头。头结点指向本结点，而本结点的next指向的结点保证为hull顺时针方向的下一个表层结点
    //本结点的pre指向的结点保证为hull顺时针方向的前一个表层结点
    DListNode *						m_ptrPre;
};
#endif
