#ifndef SORT_H
#define SORT_H

#include <vector>

using std::vector;

template <typename T>
class QuickSort {
    public: 
        void sort(vector<T>&, int, int);
    
    private:
        int partition(vector<T>&, int, int);
        void swap(vector<T>&, int, int);
};

template <typename T>
class MergeSort {
  public: 
      void sort(vector<T>&, int, int);
};

template <typename T>
void QuickSort<T>::sort(vector<T>& A, int lo, int hi) {
  if (lo >= hi) {
    return;
  }
  int pivot = partition(A, lo, hi);

  sort(A, lo, pivot - 1);
  sort(A, pivot + 1, hi);
}

template <typename T>
int QuickSort<T>::partition(vector<T>& A, int lo, int hi) {
  // Middle element
  int leftPointer = lo;
  int rightPointer = hi;
  int pivotLocation = hi;
  T pivotElement = A[pivotLocation];

  while(leftPointer < rightPointer) {
    while (A[leftPointer] <= pivotElement && leftPointer < rightPointer) {
      leftPointer++;
      // Move towards middle
    }
    // Stops when finds an element greater than or equal the pivot
    while (A[rightPointer] > pivotElement && leftPointer < rightPointer) {
      rightPointer--;
    }
    swap(A, leftPointer, rightPointer);
  }
  swap(A, rightPointer, pivotLocation);
  return rightPointer;
}
template <typename T>
void QuickSort<T>::swap(vector<T>& A, int index1, int index2) {
  T temp = A[index1];
  A[index1] = A[index2];
  A[index2] = temp;
}
#endif