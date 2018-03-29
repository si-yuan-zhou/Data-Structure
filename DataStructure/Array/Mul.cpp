#include <iostream>
using namespace std;
#include "MulMatrix.h"

int main(int argc, char const *argv[])
{
	SMatrix ma,mb,mc;
	int m1 = 3,n1 = 4,k1 = 4;//被乘矩阵
	int m2 = 4,n2 = 2,k2 = 4;//乘数矩阵
	int da[4][3] = {{0,0,3},{0,3,7},{1,3,-1},{2,1,2}};
	int db[4][3] = {{0,1,1},{1,0,2},{2,0,3},{2,1,4}};

	ma = MCreate(da,m1,n1,k1);
	cout << "ma=" << endl;
	MDisp(ma);

	mb = MCreate(db,m2,n2,k2);
	cout << "mb=" << endl;
	MDisp(mb);

	if(ma.nu != mb.mu) {
		cout << "矩阵维度不对，无法运算"<< endl;
		exit(1);
	}
	if(ma.tu == 0 || mb.tu == 0) {
		cout << "c is empty"<< endl;
		exit(1);
	}
	mc = MMul(ma,mb);
	cout << "ma * mb =" << endl;
	MDisp(mc);
	return 0;
}
