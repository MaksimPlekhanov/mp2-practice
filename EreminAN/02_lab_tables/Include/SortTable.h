#pragma once
#include "ScanTable.h"
#include <iostream>
#include <string>
template <typename TableKey, typename TableData>
class  SortTable : public ScanTable<TableKey, TableData>
{
public:

	void SortData();   // сортировка данных по ключам;

public:
	SortTable(int Size_ = TabMaxSize) :ScanTable<TableKey, TableData>(Size_) {};
	SortTable(const SortTable<TableKey, TableData>& table_);
	SortTable(const ScanTable<TableKey, TableData>& table_);

	// основные методы
	virtual TableData* FindRecord(const TableKey key_);                             //найти запись;                     
	virtual void InsRecord(const TableKey key_, const TableData data_);            //вставить;                      
	virtual void DelRecord(const TableKey key_);                                  //удалить запись;   


};


template <typename TableKey, typename TableData>
SortTable<TableKey, TableData>::SortTable(const SortTable<TableKey, TableData>& Table_)
{
	TabSize = Table_.TabSize;
	DataCount = Table_.DataCount;
	CurrPos = Table_.CurrPos;
	pRecs = new TabRecord<TableKey, TableData> * [TabSize];
	for (int i = 0; i < DataCount; i++)
	{
		pRecs[i] = new TabRecord<TableKey, TableData>(*(Table_.pRecs[i]));
	}
}

template <typename TableKey, typename TableData>
SortTable<TableKey, TableData>::SortTable(const ScanTable<TableKey, TableData>& Table_)
{
	TabSize = Table_.GetTabSize();
	DataCount = Table_.GetDataCount();
	CurrPos = Table_.GetCurrentPos();
	pRecs = new TabRecord<TableKey, TableData> * [TabSize];
	for (int i = 0; i < DataCount; i++)
	{
		pRecs[i] = new TabRecord<TableKey, TableData>(*(Table_.GetRecs(i)));
	}
	SortData();
}


template <typename TableKey, typename TableData>
TableData* SortTable<TableKey, TableData>::FindRecord(const TableKey key_)
{
		if (IsEmpty())
		{
			throw "SortTable Пуста;";
		}
		Reset();
		TableData* tmp = nullptr;

		int i, i1 = 0, i2 = DataCount - 1; // границы области поиска;
		bool flag = true;
		while (i1 <= i2)
		{
			i = (i1 + i2) >> 1;// середина области поиска;
			if (pRecs[i]->GetKey() == key_)
			{
				i1 = i + 1;
				i2 = i;
				break;
			}
			if ((pRecs[i]->GetKey()) > (key_))
			{
				i2 = i - 1;
			}
			else
				i1 = i + 1;
		}
		if ((i2 < 0) || ((pRecs[i2]->GetKey()) < (key_)))
			i2++;
		CurrPos = i2;
		if ((i2 < DataCount) && (pRecs[i]->GetKey() == key_))
			return pRecs[i2]->GetData();
		return nullptr;
}


template <typename TableKey, typename TableData>
void SortTable<TableKey, TableData>::InsRecord(const TableKey key_, const TableData data_)
{
		if (IsFull())
			throw "SortTable Полна;";

		if ((IsEmpty()) || (FindRecord(key_) == nullptr))
		{
			for (int i = DataCount; i > CurrPos; i--)
				pRecs[i] = pRecs[i - 1];
			pRecs[CurrPos] = new TabRecord<TableKey, TableData>(key_, data_);;
			DataCount++;
		}
		else throw "Такая запись уже есть;";
}

template <typename TableKey, typename TableData>
void SortTable<TableKey, TableData>::DelRecord(const TableKey key_)
{
		if (FindRecord(key_) == nullptr)
			throw "SortTable - запись не найдена;";

		for (int i = CurrPos; i < DataCount - 1; i++)
			pRecs[i] = pRecs[i + 1];
		pRecs[DataCount - 1] == nullptr;
		DataCount--;
}



template <typename TableKey, typename TableData>
void SortTable<TableKey, TableData>::SortData()
{
	int i, j;
	for (i = 0; i < DataCount; i++)
	{
		for (j = 0; j < DataCount; j++)
		{
			if (stoi(pRecs[i]->GetKey()) < stoi(pRecs[j]->GetKey()))
			{
				TabRecord<TableKey, TableData>* temp(pRecs[i]);
				pRecs[i] = pRecs[j];
				pRecs[j] = temp;
			}
		}
	}
}

