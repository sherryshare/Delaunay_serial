#ifdef __APPLE__
#include <GLUT/GLUT.h>
#else
#include <GL/glut.h>
#endif

#include "Delaunay.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "spatial_sort.h"
#define SERIALSIZE 5
#define MAXPOINTS 1000

#define MAX_X 2
#define MAX_Y 2
#define MIN_X 1
#define MIN_Y 1

using namespace std;
Points points;

// Generate points ramdomly.
int generate_points() {
    string in_file_name = "../inputs.txt";
    ifstream in_file(in_file_name.c_str());
    int i;
    if(!in_file.is_open()) {
        cout << "Can't open the file " << in_file_name << endl;
        return 0;
    }
    for(i=0; !in_file.eof() && i < MAXPOINTS; i++)
    {
        double x,y;
        in_file >> x >> y;
        points.push_back( Point( x, y, i ) );
    }
    in_file.close();
    return i;
}


void displayFunction()
{
    glClear( GL_COLOR_BUFFER_BIT );
    glLineWidth( 1.0 );
    int count=0;
    for(int i=0; i<points.size()/SERIALSIZE; i++)
    {
        glBegin( GL_LINE_LOOP );
        switch(i%3)
        {
        case 0:
            glColor4f( 0.5,0.0,0.0, 0.0 );
            break;
        case 1:
            glColor4f( 0.0,0.5,0.0, 0.0 );
            break;
        case 2:
            glColor4f( 0.0,0.0,0.5, 0.0 );
            break;
        }
        for(int j=0; j<SERIALSIZE; j++) {
            glVertex2f( points[i*SERIALSIZE + j][0], points[i*SERIALSIZE + j][1]);//一个点的x、y坐标
            count ++;
        }
        glEnd();
    }
    glutSwapBuffers();
    cout << "\nCount = " << count << endl;
}

void displayFunction3()
{
    glClear( GL_COLOR_BUFFER_BIT );

    glLineWidth( 1.0 );

    int count=0;
//     for(int i=5; i < 10; i++)//altered for test
    for(int i=0; i < points.size(); i++)
    {
        glBegin( GL_LINES );
        glColor4f( 0.0, 0.0, 0.0, 0.0 );
        int listSize = 0;
        if((listSize = points[i].getHead()->getSize()) > 1) {
	    DListNode * pNode = points[i].getHead()->getNext();//不从头节点算起
	    do{
	      int id = pNode->getData();
	      glVertex2f( points[i][0], points[i][1]);
// 	      if(id < 10 && id > 4)//--added for test
                glVertex2f( points[id][0], points[id][1]);//一个点的x、y坐标	
	      pNode = pNode->getNext();
	    }while(pNode!=points[i].getHead());
        }
        glEnd();
    }
    glutSwapBuffers();
//     cout << "\nCount = " << count << endl;
}

void resizeFunction( int width, int height )
{
    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( MIN_X, MAX_X, MIN_Y, MAX_Y, - 1.0, 1.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void initializeGL()
{
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
}

int main(int argc, char *argv[])
{
    if(!(generate_points())){
      cout << "Fail to read the inputs!" << endl;
      return -1;      
    }
    for(int i=0; i<points.size(); i++) {
        cout << points[i].getID() << " = (" << points[i].x() << ", " << points[i].y() << ")\t";
    }
    cout << endl << "generate end " << points.size() << endl;
    spatial_sort(points);
    cout << "spatial sorted" << endl;

    for(int i=0; i<points.size(); i++) {
        cout << points[i].getID() << " = (" << points[i].x() << ", " << points[i].y() << ")\t";
    }
    cout << endl;

    Delaunay(points,0,points.size()-1);//,SERIALSIZE,true);

    cout << "Final:" << endl;
    for(int i=0; i < points.size(); i++)
    {
        int listSize = 0;
        if((listSize = points[i].getHead()->getSize()) > 1) {
            cout << "Size = " << listSize << " : ";
	    points[i].getHead()->printAll();
        }
    }
    glutInitWindowPosition( 0, 0 );
    glutInitWindowSize( 640, 640 );
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );
    glutCreateWindow( "Delaunay" );
    glutDisplayFunc( displayFunction3 );
//     glutDisplayFunc( displayFunction );
    glutReshapeFunc( resizeFunction );
    initializeGL();
    glutMainLoop();
    cout << "haha" << endl;

}

