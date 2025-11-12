#ifndef LIST_
#define LIST_


template <class T>
struct Node {
	T value;
	Node<T> *next;
	Node(T val, Node<T>* n) : value(val), next(n) {}
};

template <class T> 
class List {
private:
	Node<T> *_head, *_tail;
	size_t _count;
public:
	List() : _head(nullptr), _tail(nullptr), _count(0) {}
	List(const List& other);
	~List();

	void push_front(const T& val) noexcept;
	void push_back(const T& val) noexcept;
	void insert(size_t pos, const T& val);
	void insert(Node<T> *node, const T& val);
	void pop_front();
	void pop_back();
	void eraze(size_t pos);
	void eraze(Node<T> *node);

	inline bool is_empty() const noexcept { return _count == 0; }
	inline size_t size() const noexcept { return _count; }
	inline T& head() const;
	inline T& tail() const;
	Node<T>* const node(size_t pos) const;

	class Iterator {
	private:
		Node<T>* current;
	public:
		Iterator() : current(nullptr) {}
		Iterator(Node<T>* pos) : current(pos) {}
		Iterator(const Iterator& other) : current(other.current) {}

		Iterator& operator= (const Iterator& other);
		T& operator* ();
		bool operator!= (const Iterator& other);
		Iterator operator++ (int); //x++
		Iterator& operator++ ();   //++x
	};

	Iterator begin() const noexcept { return iterator(_head); }
	Iterator end() const noexcept { return Iterator(); }

	typedef Iterator iterator;
	
};

template <class T> List<T>::List(const List& other) : _count(0) {
	Node<T>* current = other._head;
	while (current != nullptr) {
		push_back(current->value);
		current = current->next;
	}
}

template <class T> List<T>::~List() {
	while (_count) {
		Node<T>* next = _head->next;
		delete _head;
		_head = next;
		--_count;
	}
}

template <class T> void List<T>::push_front(const T& val) noexcept {
	Node<T> *new_node = new Node<T>(val, _head);
	_head = new_node;
	if (is_empty()) _tail = _head;
	_count++;
}

template <class T> void List<T>::push_back(const T& val) noexcept {
	Node<T> *new_node = new Node<T>(val, nullptr);
	if (!is_empty()) {
		_tail->next = new_node;
		_tail = new_node;
	}
	else {
		_tail = new_node;
		_head = _tail;
	}
	_count++;
}

template <class T> void List<T>::pop_front() {
	if (is_empty()) throw std::logic_error("List is empty in pop_front()!");
	Node<T> *next = _head->next;
	delete _head;
	_head = next;
	--_count;
}

template <class T> void List<T>::pop_back() {
	if (is_empty()) throw std::logic_error("List is empty in pop_back()!");
	if (_count == 1) delete _tail;
	else {
		Node<T>* current = _head;
		while (current->next != _tail)
			current = current->next;
		delete _tail;
		_tail = current; _tail->next = nullptr;
	}
	--_count;
}

template <class T> void List<T>::insert(size_t pos, const T& val) {
	if (pos > _count) throw std::logic_error("There is no such position in the list!");
	else if (pos == 0) push_front(val);
	else if (pos == _count) push_back(val);
	else {
		Node<T>* current = _head;
		while (pos-- - 1) current = current->next;
		Node<T>* new_node = new Node<T>(val, current->next);
		current->next = new_node;
		++_count;
	}
}

template <class T> void List<T>::insert(Node<T>* node, const T& val) {
	if (node == nullptr) throw std::logic_error("Node is nullptr!");
	Node<T>* new_node = new Node<T>(val, node->next);
	node->next = new_node;
	if (_tail == node) _tail = new_node;
	++_count;
}

template <class T> void List<T>::eraze(size_t pos) {
	if (pos >= _count) throw std::logic_error("There is no such position in the list!");
	else if (pos == 0) pop_front();
	else if (pos == (_count - 1)) pop_back();
	else {
		Node<T>* current = _head;
		while (pos-- - 1) current = current->next;
		Node<T>* pre_cur = current;
		current = current->next;
		pre_cur->next = current->next;
		delete current;
		--_count;
	}
}

template <class T> void List<T>::eraze(Node<T>* node) {
	if (node == nullptr) throw std::logic_error("Node is nullptr!");
	else if (node == _head) pop_front();
	else if (node == _tail) pop_back();
	else {
		Node<T>* current = _head;
		while (current->next != node)
			current = current->next;
		Node<T>* pre_cur = current;
		current = current->next;
		pre_cur->next = current->next;
		delete current;
		--_count;
	}
}

template <class T> T& List<T>::head() const {
	if (is_empty()) throw std::logic_error("List is empty in head()!");
	return _head->value;
}

template <class T> T& List<T>::tail() const {
	if (is_empty()) throw std::logic_error("List is empty in tail()!");
	return _tail->value;
}

template <class T> Node<T>* const List<T>::node(size_t pos) const {
	if (pos >= _count) throw std::logic_error("There is no such position in the list!");
	Node<T>* current = _head;
	while (pos--) current = current->next;
	return current;
}

template <class T> typename List<T>::Iterator& List<T>::iterator::operator= (const Iterator& other) {
	this = other.current;
	return *this;
}

template <class T> T& List<T>::iterator::operator* () {
	return this->current->value;
}

template <class T> bool List<T>::iterator::operator!= (const Iterator& other) {
	return this->current != other.current;
}

template <class T> typename List<T>::Iterator List<T>::iterator::operator++ (int) {
	List<T>::Iterator tmp(*this);
	current = current->next;
	return tmp;
}

template <class T> typename List<T>::Iterator& List<T>::iterator::operator++ () {
	current = current->next;
	return *this;
}

#endif