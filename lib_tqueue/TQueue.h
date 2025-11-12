#ifndef TQUEUE_
#define TQUEUE_

#include <stdexcept>
#include "list.h"

template <class T>
class TQueue {
private:
	List<T> _list;
public:
	TQueue() {}
	~TQueue() { _list.~List<T>();  }

	inline void push(const T& el) {
		_list.push_back(el);
	}
	inline void pop() {
		if (is_empty()) throw std::out_of_range("Queue is empty!");
		_list.pop_front();
	}
	inline T& head() const {
		if (is_empty()) throw std::out_of_range("Queue is empty!");
		return _list.head();
	}
	inline bool is_empty() const noexcept { return !_list.size(); }
};

#endif
