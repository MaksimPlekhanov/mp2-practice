#include "ScanTable.h"
#include "HashTable.h"
#include "SortTable.h"
#include "Table.h"
#include "polinom.h"
#include <string>;
using namespace std;
#define SS <int,string>

#define ZZ <Polinom,string>
int main() {

	
	SortTable SS A;
	A.Insert(11, "1");
	A.Insert(9, "2");
	A.Insert(8, "3");
	A.Insert(7, "1777");
	A.Insert(6, "16688");
	A.Insert(5, "6");
	A.Insert(4, "7");
	A.Insert(3, "8");
	A.Insert(200, "9");
	cout << A<<endl;

	A.SortData();
	cout << A;

	SortTable ZZ Poltable;

	Polinom p1;
	p1.str_to_poly("x+y");
	Poltable.Insert(p1, "x+y");
	Polinom p2;
	p2.str_to_poly("2x+z^2");
	Poltable.Insert(p2, "2x+z^2");
	Polinom p3;
	Poltable.Insert((p2 + p1), "2x+z^2+x+y");
	cout << Poltable;

	HashTable ZZ Pol;
	Pol.Insert(p1, "x+y");
	return 0;
}
