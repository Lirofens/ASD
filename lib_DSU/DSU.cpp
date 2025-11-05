#include "DSU.h"
#include <stdexcept>

DSU::DSU(size_t size) : _parent(new int[size]), _rank(new int[size]), _size(size) {
	for (size_t i = 0; i < size; ++i) {
		_parent[i] = i;
		_rank[i] = 0;
	}
}

DSU::~DSU() {
	delete[] _parent;
	delete[] _rank;
}

void DSU::unite(int x, int y) {
	if (x == y) throw std::exception("Identical sets.");
	int rankX = _rank[find(x)], rankY = _rank[find(y)];
	if (rankX < rankY) _parent[find(x)] = find(y);
	else if (rankX == rankY) { _rank[find(x)]++; _parent[find(y)] = find(x); }
	else _parent[find(y)] = find(x);
}

int DSU::find(int x) {
	if (x < 0 || x > _size) std::logic_error("There is no such set.");
	if (_parent[x] == x) return x;
	else return _parent[x] = find(_parent[x]);
}