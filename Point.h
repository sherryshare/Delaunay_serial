#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <assert.h>
#include <vector>
#include "doubly_linked_listnode.h"

#define absf(a) ( a < 0.0 ? - a : a )

class Point//这个作为结点数组里的一个结点，同时也是它的doubly linked list的头结点
{

public:

    Point()
    {
    }

    Point( const double& x, const double& y , int id = 0)
    {
        this->set( x, y );
	ID = id;
	DListNode* p=new DListNode(ID);
	m_ptrHead=p;
	p->setNext(p);
	p->setPre(p);	
    }
    
    ~Point(){};

public:
    DListNode * getHead() const{return m_ptrHead;}
    void set( const double& x, const double& y )
    {
        _elements[0] = x;
        _elements[1] = y;
    }
    int getID() {return ID;}

    const double& operator [] ( const unsigned int index ) const
    {
        assert( index < 2 );
        return _elements[ index ];
    }

    double& operator [] ( const unsigned int index )
    {
        assert( index < 2 );
        return _elements[ index ];
    }

    const double& x() const { return _elements[0]; }
    const double& y() const { return _elements[1]; }

    double& x() { return _elements[0]; }
    double& y() { return _elements[1]; }

public:

    const double length() const
    {
        return sqrt( _elements[0] * _elements[0] + _elements[1] * _elements[1] );
    }

    const double length( const Point& point ) const
    {
        Point p( point.x() - _elements[0], point.y() - _elements[1] );
        return p.length();
    }

    const bool isEqual( const Point& p ) const
    {
        return ( _elements[0] == p[0] && _elements[1] == p[1] );
    }
    
  

protected:
    double _elements[2];
    int ID;
    DListNode *						m_ptrHead;
};

typedef std::vector<Point> Points;

#endif
