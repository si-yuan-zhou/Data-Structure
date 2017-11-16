#include<iostream>
#include<cstdio>
using namespace std;
#include "MatrixTrans.h"
int main(){
    SMatrix ma,mb;
	int m=4,n=6,k=6;
	int da[6][3]={{0,2,11},{0,4,12},{1,3,12},{2,1,31},{2,3,32},{3,0,41}};
	ma=MCreate(da,m,n,k);//¥¥Ω®æÿ’Û
	cout<<"Ma="<<endl;
	MDisp(ma);
	mb.mu=ma.nu;
	mb.nu=ma.mu;
	mb.tu=ma.tu;
	mb.data=new MNode[ma.tu];
	MatrixTrans(ma,mb);
	cout<<"Mb="<<endl;
	MDisp(mb); 
	return 0;
} 
