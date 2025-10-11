#include <iostream>

template <class T>
class Queue {
private:
	T* _data;
	size_t _size;
	int _head;
	int _tail;
	int _count;
public:
	Queue(size_t size = 20) : _data (new T[size]),
		_size(size),_head(0), _tail(-1), _count(0) {}
	~Queue() {
		delete[] _data;
		_data = nullptr;
	}
	inline void push(const T& el) {
		if (is_full()) throw std::out_of_range("Queue is full!");
		++_count;
		_tail = ++_tail % _size;
		_data[_tail] = el;
	}
	inline void pop() {
		if (is_empty()) throw std::out_of_range("Queue is empty!");
		--_count;
		_head = ++_head % _size;
	}
	inline T& head() const {
		if (is_empty()) throw std::out_of_range("Queue is empty!");
		return _data[_head];
	}
	inline bool is_empty() const noexcept { return _count == 0; }
	inline bool is_full() const noexcept { return _count == _size; }
};