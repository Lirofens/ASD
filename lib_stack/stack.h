#ifndef STACK_H_
#define STACK_H_

#include <iostream>

template <class T>
class Stack {
private:
	T* _data;
	size_t _size;
	int _top;
public:
	Stack(size_t size = 20) : _data (new T[size]), _size(size), _top(-1) {}
	~Stack() {
		delete[] _data;
		_data = nullptr;
	}
	inline void push(const T& el) { 
		if (is_full()) throw std::out_of_range("Stack is full!");
		_data[++_top] = el;
	}
	inline void pop() { 
		if (is_empty()) throw std::out_of_range("Stack is empty!");
		--_top;
	}
	inline T& top() const {
		if (is_empty()) throw std::out_of_range("Stack is empty!");
		return _data[_top];
	}
	inline bool is_empty() const noexcept { return _top == -1; }
	inline bool is_full() const noexcept { return (_top + 1) == _size; }
};

#endif