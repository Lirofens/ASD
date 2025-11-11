#ifndef VECTOR_
#define VECTOR_

#include <iostream>

#define STEP_CAPACITY 15

template <class T> class TVector;
template <class T> std::ostream& operator<< (std::ostream&, const TVector<T>&);

template <class T> void quick_sort(TVector<T>& array, size_t left, size_t right) noexcept;
template <class T> size_t binary_search(const TVector<T>&, const T&) noexcept;

inline size_t calculate_capacity(size_t size) noexcept;

template <class T>
class TVector {
private:
    T* _data;
    size_t _size;
    size_t _capacity;
    inline bool is_full() const noexcept { return (_size >= _capacity) ? true : false; }
public:
    TVector(size_t size = 0) : _data(new T[calculate_capacity(size)]),
        _size(size), _capacity(calculate_capacity(size)) {}
    TVector(const T* data, const size_t size) : _data(new T[calculate_capacity(size)]),
        _size(size), _capacity(calculate_capacity(size)) {
        for (size_t i = 0; i < size; ++i)
            _data[i] = data[i];
    }
    TVector(const TVector& other) : _data(new T[other._capacity]),
        _size(other._size), _capacity(other._capacity) {
        for (size_t i = 0; i < other._size; ++i)
            _data[i] = other._data[i];
    }
    ~TVector() {
        delete[] _data;
        _data = nullptr;
    }

    void data(const T* data, const size_t size) noexcept;
    inline void size(const size_t size) noexcept {
        if (size >= _capacity) resize(_size);
        _size = size;
    }
    inline void capacity(const size_t capacity) noexcept {
        reserve(capacity);
    }
    inline void push_back(const T& element) noexcept {
        _size++;
        if (is_full()) resize(_size);
        _data[_size - 1] = element;
    }
    void push_front(const T& element) noexcept;
    void insert(const size_t, const T&, const size_t) noexcept;
    void insert(const size_t, const T*, const size_t) noexcept;

    inline void pop_back() noexcept {
        if (_capacity > calculate_capacity(_size - 1))
            resize(_size - 1);
        --_size;
    }
    void pop_front() noexcept;
    void eraze(const size_t, const size_t) noexcept;

    inline void emplace(const size_t index, const T& element) noexcept {
        _data[index] = element;
    }

    inline void assign(const size_t start, const T& element, const size_t count) noexcept {
        for (size_t i = 0; i < count; ++i)
            _data[i + start] = element;
    }
    inline void assign(const size_t start, const T* array, const size_t arrSize) noexcept {
        for (size_t i = 0; i < arrSize; ++i)
            _data[i + start] = array[i];
    }
    inline T& at(const size_t i) {
        if (i >= _size) throw std::out_of_range("Out of range");
        return _data[i];
    }
    inline const T& at(const size_t i) const {
        if (i >= _size) throw std::out_of_range("Out of range");
        return _data[i];
    }

    inline void clear() noexcept {
        _size = 0;
        shrink_to_fit();
    }

    TVector<T>& shrink_to_fit() noexcept;
    TVector<T>& reserve(size_t newCap) noexcept;
    TVector<T>& resize(size_t size) noexcept;

    inline const T* data() const noexcept { return _data; }
    inline size_t size() const noexcept { return _size; }
    inline size_t capacity() const noexcept { return _capacity; }
    inline const T& back() const noexcept { return _data[_size - 1]; }
    inline const T& front() const noexcept { return _data[0]; }
    inline T& operator[](size_t i) noexcept { return _data[i]; }
    inline const T& operator[](size_t i) const noexcept { return _data[i]; }
    inline bool is_empty() const noexcept { return (_size == 0) ? true : false; }

    TVector& operator=(const TVector<T>&) noexcept;
    bool operator== (const TVector<T>& other) noexcept;
    inline bool operator!= (const TVector& other) noexcept { return !(*this == other); }
    friend std::ostream& operator<< <T>(std::ostream&, const TVector<T>&);

    class iterator {
    protected:
        T* current;
    public:
        iterator() : current(nullptr) {}
        iterator(T* pos) : current(pos) {}
        iterator(const iterator& other) : current(other.current) {}

        iterator& operator= (const iterator& other) { this->current = other.current; return *this; }
        T& operator* () { return *(this->current); }
        bool operator!= (const iterator& other) { return this->current != other.current; }
        iterator operator++ (int) {
            iterator tmp(*this);
            this->current++;
            return tmp;
        }
        iterator& operator++ () {
            this->current++;
            return *this;
        }
        iterator operator-- (int) {
            iterator tmp(*this);
            this->current--;
            return tmp;
        }
        iterator& operator-- () {
            this->current--;
            return *this;
        }
    };

    inline const iterator begin() const noexcept { return iterator(_data); }
    inline const iterator end() const noexcept { return iterator(_data + _size - 1); }

    friend inline size_t calculate_capacity(size_t) noexcept;
    friend void quick_sort<T>(TVector<T>&, size_t, size_t) noexcept;
    friend size_t binary_search<T>(const TVector<T>&, const T&) noexcept;
};

inline size_t calculate_capacity(size_t size) noexcept { return (size / STEP_CAPACITY + 1) * STEP_CAPACITY; }


template <class T> std::ostream& operator<< <T>(std::ostream& out, const TVector<T>& vector) {
    for (size_t i = 0; i < vector.size(); i++) {
        out << vector[i] << " ";
    }
    return out;
}
template <class T> TVector<T>& TVector<T>::operator=(const TVector& other) noexcept {
    if (this == &other) return *this;
    if (_capacity != other._capacity) {
        if (_data != nullptr) delete[] _data;
        _data = new T[calculate_capacity(other._size)];
        _capacity = other._capacity;
    }
    _size = other._size;
    for (size_t i = 0; i < _size; ++i)
        _data[i] = other[i];
    return *this;
}
template <class T> bool TVector<T>::operator== (const TVector& other) noexcept {
    if (_size != other._size) return false;
    for (size_t i = 0; i < _size; ++i)
        if (_data[i] != other._data[i]) return false;
    return true;
}


template <class T> void TVector<T>::data(const T* data, const size_t size) noexcept {
    delete[] _data;
    _data = new T[calculate_capacity(size)];
    _size = size;
    _capacity = calculate_capacity(size);
    for (size_t i = 0; i < _size; ++i)
        _data[i] = data[i];
}
template <class T> void TVector<T>::push_front(const T& element) noexcept {
    _size++;
    if (is_full()) resize(_size);
    for (size_t i = _size - 1; i > 0; --i)
        _data[i] = _data[i - 1];
    _data[0] = element;
}
template <class T> void TVector<T>::insert(const size_t start, const T& element, const size_t count = 1) noexcept {
    _size += count;
    if (is_full()) resize(_size);
    size_t i = _size + count - 1;
    while (i != start + count)
        _data[i] = _data[i-- - count];
    for (size_t i = start; i < count + start; ++i) {
        _data[i + count] = _data[i];
        _data[i] = element;
    }
}
template <class T> void TVector<T>::insert(const size_t start, const T* array, const size_t arrSize) noexcept {
    _size += arrSize;
    if (is_full()) resize(_size);
    size_t i = _size + arrSize - 1;
    while (i != start + arrSize)
        _data[i] = _data[i-- - arrSize];
    for (size_t i = start; i < arrSize + start; ++i) {
        _data[i + arrSize] = _data[i];
        _data[i] = array[i - start];
    }
}
template <class T> void TVector<T>::pop_front() noexcept {
    if (_capacity > calculate_capacity(_size - 1))
        resize(_size - 1);
    for (int i = 0; i < _size - 1; ++i)
        _data[i] = _data[i + 1];
    --_size;
}
template <class T> void TVector<T>::eraze(const size_t start, const size_t count = 1) noexcept {
    for (size_t i = start; i < _size - count; ++i)
        _data[i] = _data[i + count];
    _size -= count;
    resize(_size);
}
template <class T> TVector<T>& TVector<T>::shrink_to_fit() noexcept {
    TVector tmp(*this);
    delete[] _data;
    _capacity = _size;
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; ++i)
        _data[i] = tmp._data[i];
    return *this;
}
template <class T> TVector<T>& TVector<T>::reserve(size_t newCap) noexcept {
    if (newCap <= _capacity) return *this;
    TVector tmp(*this);
    delete[] _data;
    _capacity = newCap;
    _data = new T[_capacity];
    size_t minSize = (_size < newCap) ? _size : newCap;
    for (size_t i = 0; i < minSize; ++i)
        _data[i] = tmp._data[i];
    _size = minSize;
    return *this;
}
template <class T> TVector<T>& TVector<T>::resize(size_t size) noexcept {
    TVector tmp(*this);
    delete[] _data;
    _capacity = calculate_capacity(size);
    _data = new T[_capacity];
    size_t minSize = (_size < size) ? _size : size;
    for (size_t i = 0; i < minSize; ++i)
        _data[i] = tmp._data[i];
    _size = minSize;
    return *this;
}
template <class T> void quick_sort<T>(TVector<T>& array, size_t left, size_t right) noexcept { //Ѕыстра€ сортировка, сортировка ’оара.
    size_t i = left, j = right;
    T& pilot = array[left + (right - left) / 2];
    while (i <= j) {
        while (array[i] < pilot) i++;
        while (array[j] > pilot) j--;
        if (i <= j) {
            T swap = array[i];
            array[i] = array[j];
            array[j] = swap;
            i++;
            if (j > 0) j--;
        }
    }
    if (i < right) quick_sort(array, i, right);
    if (j > left) quick_sort(array, left, j);
}
template <class T> size_t binary_search<T>(const TVector<T>& vec, const T& key) noexcept {
    size_t left = 0;
    size_t right = vec.size() - 1;
    while (left <= right) {
        size_t mid = left + (right - left) / 2;
        if (vec[mid] == key) return mid;
        else if (vec[mid] < key)
            left = mid + 1;
        else right = mid - 1;
    }

    return -1; // Ёлемент не найден
}

#endif