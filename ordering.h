#ifndef __ORDERING_H_INCLUDED__
#define __ORDERING_H_INCLUDED__

#include <algorithm>
#include "mymath.h"
#include <vector>

class Ordering {
    public:
    static void bubbleSort(std::vector<int>& t);
    static void insertionSort(std::vector<int>& t, int lb, int ub);
    static int medianOfMedians(std::vector<int>& t, int lb, int ub, int index);
    static int naiveMedian(std::vector<int>& t,int lb, int ub);
    static void naiveQuickSort(std::vector<int>& t, int lb, int ub);
    static int partition(std::vector<int>& t, int lb, int ub);
    static int randomizedPartition(std::vector<int>& t,int lb, int ub);
    static void randomizedQuickSort(std::vector<int>& t, int lb, int ub);
    static int randomizedSelect(std::vector<int>& t, int lb, int ub, int searched);
    static void theoreticalQuickSort(std::vector<int>& t, int lb, int ub);
};

#endif