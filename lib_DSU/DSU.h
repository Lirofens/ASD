#ifndef _DSU
#define _DSU

class DSU {
private:
	int *_parent;
	int* _rank;
	size_t _size;
public:
	DSU(size_t);
	~DSU();
	void unite(int, int);
	int find(int);
};

#endif // !_DSU
