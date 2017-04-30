#include "ordering.h"
#include <iostream>
/*
Algorithm implementations are based on pseudocodes/ideas from Cormen,Leiserson, Stein, Rivest
- Introduction to Algorithm
*/

void Ordering::bubbleSort(std::vector<int>& t) {
	for (size_t i=0;i<t.size();i++) {
		for (size_t j=0;j<t.size()-i-1;j++) {
			if (t[j]>t[j+1]) std::swap(t[j],t[j+1]);
		}
	}
}

void Ordering::insertionSort(std::vector<int>& t, int lb, int ub) {
	for (size_t i=lb;i<ub+1;i++) {
		for (size_t j=i+1;j<ub+1;j++) {
			if (t[i]>t[j]) std::swap(t[i],t[j]);
		}
	}
}

int findIndex(std::vector<int>& t,int lb, int ub, int i) {
	for (int j=lb;j<=ub;j++) {
		if (t[j]==i) {
			return j;
		}
	}
	return -1;
}

//O(n^2) worst case naive median finding algorithm. Finds the former median when there are two.
int Ordering::naiveMedian(std::vector<int>& t,int lb, int ub) {
	Ordering::insertionSort(t,lb,ub);
	return t[(ub+lb)/2];
}

//O(n) time partition, assumes pivot at index ub.
int Ordering::partition(std::vector<int>& t, int lb, int ub) {
	int k=lb;
	for (int i=lb;i<ub;i++) {
		if (t[i]<=t[ub]) {
			std::swap(t[i],t[k]);
			k++;
		}
	}
	std::swap(t[k],t[ub]);
	return k;
}

//O(n) worst case mostly theoretical median algorithm.
int Ordering::medianOfMedians(std::vector<int>& t,int lb, int ub,int index) {
	if (ub-lb<5) {
		Ordering::insertionSort(t,lb,ub);
		return t[index];
	}
	std::vector<int> split;
	for (int i=lb;i<=ub;i+=5) {
		split.push_back(naiveMedian(t,i,std::min(i+4,ub)));
	}

	int pivot=naiveMedian(split,0,split.size()-1);
	std::swap(t[ub],t[findIndex(t,lb,ub,pivot)]);
	int q=Ordering::partition(t,lb,ub);
	if (q==index) {
		return t[q];
	} else if (q<index) {
		return medianOfMedians(t,q+1,ub,index);
	} else {
		return medianOfMedians(t,lb,q-1,index);
	}
}

int Ordering::randomizedPartition(std::vector<int> &t, int lb, int ub) {
	int pivot=lb+rand()%(ub-lb+1);
	std::swap(t[pivot],t[ub]);
	return Ordering::partition(t,lb,ub);
}

//O(n) expected time selection algorithm.
int Ordering::randomizedSelect(std::vector<int> &t, int lb,int ub,int searched) {
	if (lb==ub) {
		return t[lb];
	}
	int index=randomizedPartition(t,lb,ub);
	int k=index-lb;
	if (k==searched) {
		return t[index];
	} else if (k>searched) {
		return randomizedSelect(t,lb,index-1,searched);
	} else {
		return randomizedSelect(t,index+1,ub,searched-k-1);
	}
}

//Naive implementation of quicksort
void Ordering::naiveQuickSort(std::vector<int>& t,int lb, int ub) {
	if (ub-lb<10) {
		insertionSort(t,lb,ub);
		return;
	}
	int k=partition(t,lb,ub);
	naiveQuickSort(t,lb,k-1);
	naiveQuickSort(t,k+1,ub);
}

//Expected O(nlogn) time sorting algorithm.
void Ordering::randomizedQuickSort(std::vector<int>& t,int lb, int ub) {
	if (ub-lb<10) {
		insertionSort(t,lb,ub);
		return;
	}
	int k=randomizedPartition(t,lb,ub);
	randomizedQuickSort(t,lb,k-1);
	randomizedQuickSort(t,k+1,ub);
}

//O(nlogn) worst case quicksort using "good enough" pivots from medianOfMedians.
void Ordering::theoreticalQuickSort(std::vector<int>& t,int lb, int ub) {
	if (ub-lb<10) {
		insertionSort(t,lb,ub);
		return;
	}
	int pivot=medianOfMedians(t,lb,ub,(ub+lb+1)/2);
	std::swap(t[ub],t[findIndex(t,lb,ub,pivot)]);
	int k=partition(t,lb,ub);
	theoreticalQuickSort(t,lb,k-1);
	theoreticalQuickSort(t,k+1,ub);
}