#ifndef VECTOR_TOP_IT_HPP
#define VECTOR_TOP_IT_HPP
#include <cstddef>

namespace topit {
template < class T >
struct Vector
{
  Vector();
  explicit Vector(size_t s);
  explicit Vector(size_t s, const T& val);
  ~Vector();
  
  
  Vector(const Vector< T >&);
  Vector< T >& operator=(const Vector< T >& );
  Vector(Vector< T >&&) noexcept;
  Vector< T >& operator=(Vector< T >&&) noexcept; //конструктор перемещения
  
  void swap(Vector< T >&) noexcept;
  size_t getSize() const noexcept;
  size_t getCapacity() const noexcept;
  bool isEmpty() const noexcept;

  T& operator[](size_t id) noexcept;
  const T& operator[](size_t id) const noexcept;
  T& at(size_t id);
  const T& at(size_t id) const;

  void pushBack(const T& value);
  void pushFront(const T& value);

  void insert(size_t pos, const T& val);
  void insert(size_t pos, const Vector<T>& rhs, size_t b, size_t e);
  void erase(size_t pos);
  
  struct Iterator {
    T* ptr;
    Iterator() : ptr(nullptr) {}
    explicit Iterator(T* p) : ptr(p) {}
    
    T& operator*() { return *ptr; }
    const T& operator*() const { return *ptr; }
    
    Iterator& operator++() { ++ptr; return *this; }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++ptr;
      return tmp;
    }
    
    bool operator==(const Iterator& other) const { return ptr == other.ptr; }
    bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
  };

  void insert(Iterator pos, const T& val);
  void erase(Iterator pos);
  
  template<class IT>
  void insert(Iterator pos, IT begin, IT end);
  
  Iterator begin() { return Iterator(data_); }
  Iterator end() { return Iterator(data_ + size_); }


  
private:
  T* data_;
  size_t size_;
  size_t capacity_;
  
  explicit Vector(size_t s);
  void reserve(size_t new_cap);
};

template < class T >
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
  return false;
}

template < class T >
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
  return false;
}
}

template< class T >
void topit::Vector< T >::pushFront(const T& value)
{
  Vector< T > result(getSize() + 1);
  result[0] = value;
  for (size_t i = 0; i < getSize(); ++i) {
    result[i + 1] = (*this)[i];
  }
  swap(result);
}

template< class T >
topit::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
}

template< class T >
topit::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
    for (size_t i = 0; i < getSize(); ++i) {
      data_[i] = rhs.data_[i];
    }
  }

//template< class T >
//topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs)
//{
//  T* d = new T[rhs.getSize()];
//  try {
//    for (size_t i = 0; i < rhs.getSize(); ++i) {
//      d[i] = rhs.data_[i];
//    }
//  } catch (...) {
//    delete [] d;
//    throw;
//  }
//  delete [] data_;
//  data_ = d;
//  size_ = rhs.getSize();
//  capacity_ = rhs.getSize();
//  return *this;
//}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs) noexcept
{
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}

template< class T >
void topit::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T >
T& topit::Vector< T >::at(size_t id) {
  if (id < getSize()) {
    return data_[id];
  }
  throw std::out_of_range("bad id");
}

// template< class T >
// T& topit::Vector< T >::at(size_t id) {
//   return const_cast< T& >(static_cast< const Vector < T >* >(this)->at(id));
// }
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// можно и так, но лучше дублирование кода, которое выше

template< class T >
const T& topit::Vector< T >::at(size_t id) const {
  if (id < getSize()) {
    return data_[id];
  }
  throw std::out_of_range("bad id");
}

template< class T >
topit::Vector< T >::Vector(size_t size, const T& val):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i) {
    data_[i] = val;
  }
}

template< class T >
topit::Vector< T >::Vector(size_t size):
data_(size ? new T[size] : nullptr),
size_(size),
capacity_(size)
{}

template< class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template< class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

// template< class T >
// topit::Vector< T >::Vector(size_t size, const T& val) :
//   data_(size ? new T[size] : nullptr),
//   size_(size),
//   capacity_(size)
// {
//   for (size_t i = 0; i < size; ++i) {
//     try {
//       data_[i] = val;
//     } catch (...) {
//       delete[] data_;
//       throw;
//     }
//   }
// }
// template< class T >

template< class T >
size_t topit::Vector< T >::getCapacity() const noexcept {
  return capacity_;
}

template< class T >
T& topit::Vector< T >::operator[](size_t id) noexcept {
  return data_[id];
}

template< class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept {
  return data_[id];
}

template< class T >
void topit::Vector< T >::pushBack(const T& value) {
  if (size_ == capacity_) {
    size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    
    T* new_data = new T[new_capacity];
    
    for (size_t i = 0; i < size_; ++i) {
      new_data[i] = data_[i];
    }
    
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  }
  
  data_[size_] = value;
  ++size_;
}

template < class T >
bool topit::operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
  if (lhs.getSize() != rhs.getSize()) {
    return false;
  }
  for (size_t i = 0; i < lhs.getSize(); ++i) {
    if (lhs[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

template < class T >
bool topit::operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
  return !(lhs == rhs);
}

##############
template<class T>
void Vector<T>::reserve(size_t new_cap) {
  if (new_cap <= capacity_) return;
  
  T* new_data = new T[new_cap];
  for (size_t i = 0; i < size_; ++i) {
    new_data[i] = std::move(data_[i]);
  }
  delete[] data_;
  data_ = new_data;
  capacity_ = new_cap;
}

template<class T>
void Vector<T>::insert(size_t pos, const T& val) {
  if (pos > size_) {
    throw std::out_of_range("insert: pos > size");
  }
  
  if (size_ == capacity_) {
    size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
    reserve(new_cap);
  }
  
  for (size_t i = size_; i > pos; --i) {
    data_[i] = std::move(data_[i - 1]);
  }
  data_[pos] = val;
  ++size_;
}

template<class T>
void Vector<T>::insert(size_t pos, const Vector<T>& rhs, size_t b, size_t e) {
  if (pos > size_) {
    throw std::out_of_range("insert: pos > size");
  }
  if (b > e || e > rhs.size_) {
    throw std::out_of_range("insert: invalid range");
  }
  
  size_t count = e - b;
  if (count == 0) return;
  
  if (size_ + count > capacity_) {
    reserve(size_ + count);
  }
  
  for (size_t i = size_; i > pos; --i) {
    data_[i + count - 1] = std::move(data_[i - 1]);
  }
  for (size_t i = 0; i < count; ++i) {
    data_[pos + i] = rhs.data_[b + i];
  }
  size_ += count;
}

template<class T>
void Vector<T>::erase(size_t pos) {
  if (pos >= size_) {
    throw std::out_of_range("erase: pos >= size");
  }
  
  for (size_t i = pos; i < size_ - 1; ++i) {
    data_[i] = std::move(data_[i + 1]);
  }
  --size_;
}

template<class T>
void Vector<T>::insert(Iterator pos, const T& val) {
  insert(pos.ptr - data_, val);
}

template<class T>
void Vector<T>::erase(Iterator pos) {
  erase(pos.ptr - data_);
}

template<class T>
template<class IT>
void Vector<T>::insert(Iterator pos, IT begin, IT end) {
  size_t index = pos.ptr - data_;
  size_t count = 0;
  
  for (IT it = begin; it != end; ++it) {
    ++count;
  }
  
  if (count == 0) return;
  
  if (size_ + count > capacity_) {
    reserve(size_ + count);
  }
  
  for (size_t i = size_; i > index; --i) {
    data_[i + count - 1] = std::move(data_[i - 1]);
  }
  
  IT it = begin;
  for (size_t i = 0; i < count; ++i, ++it) {
    data_[index + i] = *it;
  }
  size_ += count;
}

template< class T >
topit::Vector< T >::Vector():
data_(nullptr),
size_(0),
capacity_(0)
{}

template< class T >
topit::Vector< T >::~Vector()
{
  delete [] data_;
}
#endif
