#include <iostream>
#include <fstream>
#include <cassert>


#include "spatial_sort.h"
using namespace std;



// find median value of points in x axe.
inline double find_median(
    Points & points, int pos, int size)
{
    pair<double,double> x_axe;
    int to_init = 2;
    for (int i = pos; i < pos + size; i++)
    {
        Point p = points[i];

        if (to_init >>=1)
        {
            x_axe = make_pair(p[0], p[0]);
            continue;
        }
        x_axe.first = min(x_axe.first, p[0]);
        x_axe.second = max(x_axe.second, p[0]);
    }
    double diameter = x_axe.second - x_axe.first;
    return x_axe.first + diameter/2;
}

// return the num_points on the left size
inline int reorder_points_inplace(
    Points & points, int pos, int size, double median)
{
    int l = pos;
    int r = pos + size - 1;
    while (l <= r)
    {
        if (points[l][0] > median &&
                points[r][0] <= median)
        {
            double x,y;
            x = points[l].x();
            y = points[l].y();
            points[l].set(points[r].x(),points[r].y());
            points[r].set(x,y);
        }
        if (points[l][0] <= median)
            l++;
        if (points[r][0] > median)
            r--;
    }
    return l - pos;
}

inline void spatial_sort_kernel(Points & points, int pos, int size)
{
    //cout << "thread_num=" << omp_get_thread_num() << endl;
    assert(pos >= 0 && pos + size <= points.size());
    if (size < 2)
        return;
    
    double median = find_median(points, pos, size);

    int left_size = reorder_points_inplace(points, pos, size, median);

// #pragma omp task shared(points)
    spatial_sort_kernel(points, pos, left_size);//可并行
// #pragma omp task shared(points)
    spatial_sort_kernel(points, pos + left_size, size - left_size);
}

void spatial_sort(Points & points)
{
    spatial_sort_kernel(points, 0, points.size());
}



