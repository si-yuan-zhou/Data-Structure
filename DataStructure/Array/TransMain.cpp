#include<iostream>
using namespace std;
#include "MatrixTrans.h"

int main(int argc, char const *argv[])
{
	SMatrix ma,mb;
	int m1 = 4,n1 = 6,k1 = 6;
	int da[6][3] = {{0,2,11},{0,4,12},{1,3,22},{2,1,31},{2,3,32},{3,0,41}};

	ma = MCreate(da,m1,n1,k1);
	cout << "ma = " << endl;
	MDisp(ma);

	mb.mu = ma.nu;
	mb.nu = ma.mu;
	mb.tu = ma.tu;
	mb.data = new MNode[ma.tu];
	MatrixTrans(ma,mb);
	cout <<"mb = " << endl;
	MDisp(mb);
	
	return 0;
}
