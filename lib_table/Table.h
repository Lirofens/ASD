#ifndef TABLE_H
#define TABLE_H

#include <iostream>

template <typename TKey, typename TValue>
class TTable {
public:
	~TTable() {}
	virtual void insert(const TKey& key, const TValue& val) = 0;
	virtual void replace(const TKey& key, const TValue& val) = 0;
	virtual TValue& find(const TKey& key) = 0;
	virtual void eraze(const TKey& key) = 0;
	virtual std::ostream& print(std::ostream& out) const noexcept = 0;
	virtual bool is_empty() const noexcept = 0;
	virtual bool consist(const TKey& key) const noexcept = 0;
	virtual size_t size() const noexcept = 0;

};
#endif
