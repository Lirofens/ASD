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
	int pX = find(x), pY = find(y);
	int rankX = _rank[pX], rankY = _rank[pY];
	if (rankX < rankY) _parent[pX] = pY;
	else if (rankX == rankY) { _rank[pX]++; _parent[pY] = pX; }
	else _parent[pY] = pX;
}

int DSU::find(int x) {
	if (x < 0 || x > _size) std::logic_error("There is no such set.");
	if (_parent[x] == x) return x;
	else return _parent[x] = find(_parent[x]);
}