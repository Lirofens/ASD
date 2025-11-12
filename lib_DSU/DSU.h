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

template<int rows, int cols>
int ilands(int (&mass)[rows][cols]) noexcept {
	DSU map(rows * cols);
	int count0 = 0, count = 0;
	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < cols; ++j) {
			if (mass[i][j]) {
				if (mass[i][j + 1] && j != cols - 1)
					map.unite(cols * i + j, cols * i + j + 1);
				if (mass[i + 1][j] && i != rows - 1)
					map.unite(cols * i + j, cols * (i + 1) + j);
			}
			else count0++;
		}

	for (size_t i = 0; i < rows * cols; ++i)
		if (map.find(i) == i) count++;
	return count - count0;
}
#endif // !_DSU
