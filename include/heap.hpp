#include <bits/stdc++.h>
using namespace std;

void check (bool cond, const std::string &msg = "Condition failed") {
  if (!cond) throw msg;
}

class heap {
  int _capacity;
  int _n;
  int *_arr;
  bool _min_heap;
  bool _owner;
  
  void swap (int &a, int &b) {
    if (a != b) {
      int t = b;
      b = a;
      a = t;
    }
  }

  void buildHeap () {
    for (int i = _n/2; i >= 0; --i)
      heapify (i, _n);
  }

  int minHeapify (int i, int c1, int c2) {
    int min_idx = i;
    if (c1 < _n && _arr[c1] < _arr[min_idx]) min_idx = c1;
    if (c2 < _n && _arr[c2] < _arr[min_idx]) min_idx = c2;
    return min_idx;
  }

  int maxHeapify (int i, int c1, int c2) {
    int max_idx = i;
    if (c1 < _n && _arr[c1] > _arr[max_idx]) max_idx = c1;
    if (c2 < _n && _arr[c2] > _arr[max_idx]) max_idx = c2;
    return max_idx;
  }

  void heapify (int i, int n) {
    if (n == 0 || (2*i + 1) >= n) return;
    int c1 = 2*i + 1;
    int c2 = 2*i + 2;
    int idx = _min_heap ? minHeapify (i, c1, c2) : maxHeapify (i, c1, c2);
    if (idx != i) {
      swap (_arr[i], _arr[idx]);      
      heapify (idx, n);
    }
  }

  void minInsert (int i) {
    if (i == 0) return;
    int p = i-1/2;
    if (_arr[p] > _arr[i]) {
      swap (_arr[p], _arr[i]);
      minInsert (p);
    }
  }
  
  void maxInsert (int i) {
    if (i == 0) return;
    int p = i-1/2;
    if (_arr[p] < _arr[i]) {
      swap (_arr[p], _arr[i]);
      minInsert (p);
    }
  }

public:
  heap (int size, bool min_heap = true)
    : _capacity (size * 2)
    , _n (0)
    , _arr (new int [_capacity])
    , _min_heap (min_heap)
    , _owner (false)
  {}
  
  heap (int *arr, int size, bool min_heap = true, bool copy = false)
    : _capacity (copy ? size * 2 : size)
    , _n (size)
    , _arr (copy ? new int [_capacity] : arr)
    , _min_heap (min_heap)
    , _owner (copy)
  {
    if (copy) for (int i = 0; i < _n; ++i) _arr[i] = arr[i];
    buildHeap ();
  }

  void sort () {
    int n = _n;
    for (int i = 0; i < n; ++i) extract ();
    _n = n;
  }
  
  void insert (int data) {
    check (_n < _capacity, "Overflow");
    _arr[_n++] = data;
    if (_min_heap)
      minInsert (_n-1);
    else
      maxInsert (_n-1);
  }

  int getMin () {
    check (_min_heap, "Not a min heap");
    check (_n > 0, "getMin");
    return _arr[0];
  }
  
  int extract () {
    check (_n > 0, "extract");
    swap (_arr[0], _arr[--_n]);
    heapify (0, _n);
    return _arr [_n];
  }

  int extractMin () {
    check (_min_heap, "Not a min heap");
    return extract ();
  }

  int getMax () {
    check (!_min_heap, "Not a max heap");
    check (_n > 0, "getMax");
    return _arr[0];
  }

  int extractMax () {
    check (!_min_heap, "Not a max heap");
    return extract ();
  }

  void buildMinHeap () {
    if (!_min_heap) {
      _min_heap = true;
      buildHeap ();
    }
  }

  void buildMaxHeap () {
    if (_min_heap) {
      _min_heap = false;
      buildHeap ();
    }
  }
  
  int size () {
    return _n;
  }

  ~heap () { if (_owner) delete [] _arr; }
};
