#include <bits/stdc++.h>
#include "../include/heap.hpp"

using namespace std;

void minHeapViaConstructor () {
  int n = 10;
  int arr[] = {3, 1, 4, 6, 9, 0, 2, 7, 5, 8};
  heap h (arr, n);
  int count = 1;
  int prev = h.extractMin ();
  while (h.size () > 0) {
    ++count;
    int value = h.extractMin ();
    assert (value > prev);
    prev = value;
  }
  assert (count == n);
  cout << "Min heap via constructor: Passed\n";
}

void maxHeapViaConstructor () {
  int n = 10;
  int arr[] = {3, 1, 4, 6, 9, 0, 2, 7, 5, 8};
  heap h (arr, n, false);
  int count = 1;
  int prev = h.extractMax ();
  while (h.size () > 0) {
    ++count;
    int value = h.extractMax ();
    assert (value < prev);
    prev = value;
  }
  assert (count == n);
  cout << "Min heap via constructor: Passed\n";
}

void buildMinHeapViaFunction () {
  int n = 10;
  int arr[] = {3, 1, 4, 6, 9, 0, 2, 7, 5, 8};
  heap h (arr, n, false);
  h.buildMinHeap ();
  int count = 1;
  int prev = h.extractMin ();
  while (h.size () > 0) {
    ++count;
    int value = h.extractMin ();
    assert (value > prev);
    prev = value;
  }
  assert (count == n);
  cout << "Build min heap function: Passed\n";
}

void buildMaxHeapViaFunction () {
  int n = 10;
  int arr[] = {3, 1, 4, 6, 9, 0, 2, 7, 5, 8};
  heap h (arr, n);
  h.buildMaxHeap ();
  int count = 1;
  int prev = h.extractMax ();
  while (h.size () > 0) {
    ++count;
    int value = h.extractMax ();
    assert (value < prev);
    prev = value;
  }
  assert (count == n);
  cout << "Build max heap function: Passed\n";
}

void nSizeHeap (int n) {
  int arr[] = {3, 1, 4, 6, 9, 0, 2, 7, 5, 8};
  heap h (arr, n);
  assert (h.size () == n);
  int count = n == 0 ? 0 : 1;
  int prev = n == 0 ? 0 : h.extractMin ();
  while (h.size () > 0) {
    ++count;
    int value = h.extractMin ();
    assert (value > prev);
    prev = value;
  }
  assert (count == n);
  cout << n << " size heap: Passed\n";
}

void zeroToThreeSize () {
  heap h (10);
  assert (h.size () == 0);
  for (int i = 0; i < 4; ++i)
    nSizeHeap (i);
}

void ascendingSort () {
  int n = 10;
  int arr[] = {3, 1, 4, 6, 9, 0, 2, 7, 5, 8};
  heap h (arr, n, false);
  h.sort ();
  assert (h.size () == n);
  for (int i = 1; i < n; ++i) {
    assert (arr[i] > arr[i-1]);
  }
  cout << "Ascending sort: Passed\n";
}

void descendingSort () {
  int n = 10;
  int arr[] = {3, 1, 4, 6, 9, 0, 2, 7, 5, 8};
  heap h (arr, n, true);
  h.sort ();
  assert (h.size () == n);
  for (int i = 1; i < n; ++i) {
    assert (arr[i] < arr[i-1]);
  }
  cout << "Descending sort: Passed\n";
}

int main () {
  minHeapViaConstructor ();
  maxHeapViaConstructor ();
  buildMinHeapViaFunction ();
  buildMaxHeapViaFunction ();
  zeroToThreeSize ();
  ascendingSort ();
  descendingSort ();
};
