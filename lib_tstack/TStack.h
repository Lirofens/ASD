#ifndef TSTACK_
#define TSTACK_

#include "list.h"
#include <stdexcept>

template <class T>
class TStack {
private:
	List<T> _list;
public:
	TStack() {}
	~TStack() { _list.~List<T>(); }

	inline void push(const T& el) {
		_list.push_front(el);
	}
	inline void pop() {
		if (is_empty()) throw std::out_of_range("Stack is empty!");
		_list.pop_front();
	}
	inline T& top() const {
		if (is_empty()) throw std::out_of_range("Stack is empty!");
		return _list.head();
	}
	inline bool is_empty() const noexcept { return !_list.size(); }
};

#endif