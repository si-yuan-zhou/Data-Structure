#include <iostream>
using namespace std;
#include "AddMatrix.h"

int main(int argc, char const *argv[])
{
	LMatrix ma,mb,mc;
	int da[5][3] = {{0,1,3},{1,1,2},{1,3,5},{3,0,9},{3,5,1}};
	int db[4][3] = {{0,2,7},{1,1,6},{1,3,-5},{2,1,4}};

	ma = MCreate(da,4,6,5);
	cout << "ma =" << endl;
	MDisp(ma);

	mb = MCreate(db,4,6,4);
	cout << "mb =" << endl;
	MDisp(mb);

	mc = MAdd(ma,mb);
	cout << "ma + mb = " << endl;
	MDisp(mc);

	return 0;
}
