#ifndef SORT_H
#define SORT_H

/*
A learning tool to learn the art of sorting algorithms. This enables a deeper understanding of the power of
divide and conquer algorithms as a whole. 
*/

#include <vector>

using std::vector;

template <typename T>
class QuickSort
{
public:
	void sort(vector<T> &, int, int);

private:
	int partition(vector<T> &, int, int);
	void swap(vector<T> &, int, int);
};

template <typename T>
class MergeSort
{
public:
	void sort(vector<T> &, int, int);
};
template <typename T>
void QuickSort<T>::sort(vector<T> &A, int lo, int hi)
{
	if (lo >= hi || lo < 0)
	{
		return;
	}
	int pivot = partition(A, lo, hi);

	sort(A, lo, pivot - 1);
	sort(A, pivot + 1, hi);
}

template <typename T>
int QuickSort<T>::partition(vector<T> &A, int lo, int hi)
{
	// Middle element
	// Median-of-three pivot selection
	int mid = lo + (hi - lo) / 2;
	if (A[lo] > A[mid])
	{
		swap(A, lo, mid);
	}
	if (A[lo] > A[hi])
	{
		swap(A, lo, hi);
	}
	if (A[mid] > A[hi])
	{
		swap(A, mid, hi);
	}
	swap(A, mid, hi - 1); // Place pivot at hi-1

	// Middle element
	int pivotLocation = hi - 1;
	T pivotElement = A[pivotLocation];
	int leftPointer = lo;
	int rightPointer = hi - 2; // Adjusted rightPointer

	while (leftPointer < rightPointer)
	{
		while (A[leftPointer] < pivotElement)
		{
			leftPointer++;
		}
		while (A[rightPointer] > pivotElement)
		{
			rightPointer--;
		}
		if (leftPointer <= rightPointer)
		{
			swap(A, leftPointer, rightPointer);
			// leftPointer++;
			// rightPointer--;
		}
	}
	swap(A, leftPointer, pivotLocation);
	return leftPointer;
}
template <typename T>
void QuickSort<T>::swap(vector<T> &A, int index1, int index2)
{
	T temp = A[index1];
	A[index1] = A[index2];
	A[index2] = temp;
}
#endif