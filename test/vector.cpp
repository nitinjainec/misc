#include <iostream>
#include <cstring>


namespace nj {
  template <typename T>
  class vector {
    T *_ptr;
    size_t _size;
    size_t _capacity;

    T* allocate (size_t capacity) {
      T *ptr = static_cast<T*>(malloc (sizeof (T) * capacity));
      if (ptr == NULL) throw std::runtime_error ("Bad Allocation");
      return ptr;
    }

    void deallocate (T* ptr) {
      if (ptr != nullptr)
	free (ptr);
    }

    void moveTo (T* to_ptr) {
      if (_ptr != nullptr) {
	std::memcpy ((void *)to_ptr, (void *)_ptr, sizeof (T)*_size);
	deallocate (_ptr);
      }
    }
  
    void resize (size_t size) {
      if (_capacity < size) {
	T *ptr = allocate (_capacity == 0 ? 1 : _capacity * 2);
	moveTo (ptr);
	deallocate (_ptr);
	_ptr = ptr;
      }
    }
  
  public:
    // default constructor
    vector () : _ptr (nullptr), _size (0), _capacity (0) {}

    // copy constructor
    vector (const vector<T> &o)
      : _size (o._size)
      , _capacity (o._capacity)
    {
      o._ptr = allocate (_capacity);
      for (int i = 0; i < _size; ++i) {
	new (_ptr + i) T (o._ptr[i]);
      }
    }

    // move constructor
    vector (vector<T> &&o)
      : _ptr (o._ptr)
      , _size (o._size)
      , _capacity (o._capacity)
    {
      o._ptr = nullptr;
    }

    // lvalue
    void push_back (T& value) {
      resize (_size+1);
      new (_ptr + _size++) T (std::forward<T>(value));
    }

    // rvalue
    void push_back (T&& value) {
      resize (_size+1);
      new (_ptr + _size++) T (std::forward<T>(value));
    }
    
    T& operator [] (size_t i) {
      return _ptr[i];
    }
  };
  
}

using namespace std;
int main () {
  using nj::vector;
  vector <int> a;
  for (auto i : {1, 2, 3, 4, 5, 6, 7}) {
    a.push_back (i);
  }
  for (auto i : {1, 2, 3, 4, 5, 6, 7}) {
    cout << a[i-1] << "\n";
  }
  cout << "Finished\n";
}
