#include<iostream>
#include<fstream>
#include<cstdlib>
#define SIZE 10
#define MAX_X 2
#define MAX_Y 2
#define MIN_X 1
#define MIN_Y 1
using namespace std;
int main()
{
    ofstream out("inputs.txt");
    for(int i = 0; i < SIZE; ++i)
    {
        srand(time(NULL)+i);
        const double x = static_cast<double>( rand() * ( MAX_X - MIN_X )) / RAND_MAX + MIN_X;
        const double y = static_cast<double>( rand() * ( MAX_Y - MIN_Y )) / RAND_MAX + MIN_Y;
        out << x << "\t" << y;
	if(i != SIZE - 1)
	  out << endl;
    }
    return 0;
}

