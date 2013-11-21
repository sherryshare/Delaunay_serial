#ifndef DELAUNAY_H
#define DELAUNAY_H
#include "merge.h"
#include <iostream>
using namespace std;
// bool Delaunay_serial(Points & points, int first, int last)
// {
//   if(last - first < 2)
//       return false;
//   else if(last - first = 2){
//       points[first];
//   }
//   if(testDelaunayEdge(points,first,first+1,first+2)){
//   }
// }

void Delaunay(Points & points,int first,int last)//,int serialSize,bool isPara)
{
    if(last - first == 0) {
        cout << "Delaunay start " << first << " + " << last << endl;
        return;
    }
    else if(last - first == 1) {
	cout << "Delaunay start " << first << " + " << last << endl;
        points[first].getHead()->insertNode(last,true,true,0);
        points[last].getHead()->insertNode(first,true,true,0);
    }
    else if(last - first == 2) {
        cout << "Delaunay start " << first << " + " << last << endl;
        if(!is_left(points,first,first+1,last)) {
            points[first].getHead()->insertNode(first+1,true,true,0);
            points[first].getHead()->insertNode(last,true,false,0);
            points[last].getHead()->insertNode(first,true,true,0);
            points[last].getHead()->insertNode(first+1,true,false,0);
	    points[last].getHead()->printAll();
        }
        else {
            points[first].getHead()->insertNode(last,true,true,0);
            points[first].getHead()->insertNode(first+1,true,false,0);
            points[last].getHead()->insertNode(first+1,true,true,0);
            points[last].getHead()->insertNode(first,true,false,0);
	    points[last].getHead()->printAll();
        }
    }
    else if(last - first < 5) { //保证左边>=3个点
        cout << "Delaunay start " << first << " + " << last << endl;
//         cout << first << " + " << first+2 << endl;
        Delaunay(points,first,first+2);//,isPara);
//         cout << first+3 << " + " << last << endl;
        Delaunay(points,first+3,last);//,isPara);
        cout << "merge " << first << " to " << last << " input: "<< first+2 << " + " << first+3 << endl;
        merge(points,first+2,first+3);
        cout << "merge end " << first << " + " << last << endl;
	points[first+2].getHead()->printAll();
	points[first+3].getHead()->printAll();
    }
    else
    {
        cout << "Delaunay start " << first << " + " << last << endl;
//         cout << first << " + " << (first+last)/2 << endl;
        Delaunay(points,first,(first+last)/2);//,isPara);
//         cout << (first+last)/2+1 << " + " << last << endl;
        Delaunay(points,(first+last)/2+1,last);//,isPara);
        cout << "merge " << first << " to " << last << " input: "<< (first+last)/2 << " + " << (first+last)/2+1 << endl;
        merge(points,(first+last)/2,(first+last)/2+1);
        cout << "merge end " << first << " + " << last << endl;
	points[(first+last)/2].getHead()->printAll();
	points[(first+last)/2+1].getHead()->printAll();
    }
}
#endif
