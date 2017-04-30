#include <iostream>
#include "patternmatching.h"
#include "ordering.h"
#include <ctime>
#include <chrono>
#include <ratio>
using namespace std;
using namespace std::chrono;

vector<int> randVec(int size) {
    vector<int> v(size);
    for (int i = 0; i < size; i++) {
        v[i] = rand();
    }
    return v;
}

void testRSvsSort() {
    vector<int> t, v;
    int n = 10, s = 3;
    cin >> s;
    srand(time(NULL));
    double c1 = 0, c2 = 0;

    for (int i = 0; i < n; i++) {
        t = randVec(MyMath::power(10, s));
        v = t;
        int j = rand() % t.size();
        high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
        Ordering::naiveQuickSort(v,0,v.size()-1);
        high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
        sort(t.begin(), t.end());
        high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();
        c1 += (duration_cast<duration<double>>(t2 - t1)).count();
        c2 += (duration_cast<duration<double>>(t3 - t2)).count();
    }
    cout << "Trials: " << n << " COMP avg: " << c1 / n << " STDSORT avg: " << c2 / n << endl;
}


int main() {
    testRSvsSort();
}