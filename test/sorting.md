### Flawed Quick Sort Algorithm

```
int pivotLocation = (hi + lo) / 2;
  T pivotElement = A[pivotLocation];
  int leftPointer = lo + 1;
  int rightPointer = hi;

  cout << "Pivot element " << pivotElement << "\n";
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
  swap(A, leftPointer, pivotLocation);
  return rightPointer;

```