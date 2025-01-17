#pragma once
#include "Table.h"


template <typename TableKey, typename TableData>
class THashTable : public  Table<TableKey, TableData>
{
protected:
	virtual int HashFunc(const TableKey key_); //Хэш-функция;

public:
	THashTable() :Table<TableKey, TableData>() {}
};

template <typename TableKey, typename TableData>
int THashTable<TableKey, TableData>::HashFunc(const TableKey key_)
{
	int hashval = 0;
	int Len = key_.size();
	for (int i = 0; i < Len; i++)
	{
		hashval = (hashval << 3) + int(key_[i]);
	}
	return hashval;
}
