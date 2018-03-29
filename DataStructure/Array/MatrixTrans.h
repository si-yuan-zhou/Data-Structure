//稀疏矩阵：非零元素远远少余零的个数，且非零元素无序
//创建一个稀疏矩阵实则记录非零元素的位置和值信息即三元组
/*
	创建一个SMatrix含有矩阵的行列及非零元个数及指向数据的指针
	数据区含有由MNode节点组成的数组，每个节点含有数据的位置和值
*/
#ifndef __MatrixTran_H__
#define __MatrixTran_H__

typedef struct{
	int i,j;//行号和列号
	int e;//非零元
}MNode;//非零节点单元
typedef struct{
	int mu,nu,tu;//行数，列数，非零元素个数
	MNode *data;//三元组表
}SMatrix;//矩阵模型

SMatrix MCreate(int d[][3],int m,int n,int k){
	//d数组由k行
	SMatrix M = {m,n,k,NULL};//M是一个矩阵含有行数，列数，非零元素数和非零元素数据信息

	if(k != 0)//含有非零元素则需要创空间存储这些元素的信息
		M.data = new MNode[k];//创建k个非零元素（含有位置属性和值信息）

	for(int i = 0; i < k; i++){
		// d的每一行包含行号，列号，元素值,为k个元素赋相应属性（位置，data）
		M.data[i].i = d[i][0];
		M.data[i].j = d[i][1];
		M.data[i].e = d[i][2];
	}
	return M;
}
void MDisp(SMatrix M){
	MNode p;
	int i,j,k = 0;
	p = M.data[k];
	//p point to the data area,and data should be ordered
	for (i = 0; i < M.mu; ++i) {
		for (j = 0; j < M.nu; ++j) {
			//矩阵以行序为主序进行存储
			if(k < M.tu && i == p.i && j == p.j) {
			//k是非零元素的个数，需要小于tu,因为k从零开始,p.i==i&&p.j==j意为找到了非零元素的位置
				cout << '\t'<< p.e;
				k++;
				if(k<M.tu) p = M.data[k];//p point to the next element
			} else {
				cout<<'\t'<<0;
			}
		}//一行
		cout<<endl;
	}
}
void MatrixTrans(SMatrix A,SMatrix& B) {
	//A 为要转置的矩阵，B为转化后的矩阵，传的参数B是空矩阵只有大小和非零数的个数
	int col,k,p,q;
	int *num,*cpot;
	num = new int[B.mu];
	cpot = new int[B.mu];

	if(B.tu){//非零元素必须有，否则转置无意义
		//num数组记录第col列元素个数
		for(col = 0;col < A.nu;++col){
			num[col] = 0;
		}
		for (k = 0; k < A.tu; ++k) {
			//每列含非零元素的个数
			++num[A.data[k].j];
		}

		//数组cpot存储M每列第一个非零元素转置后在数据区的位置
		cpot[0]=0;
		for (col=1;col<A.nu;++col) {
			//col列第一个非零元素的位置（data中的位置）= 上一列第一个非零元位置 + 上一列第一个非零元个数
			cpot[col] = cpot[col-1] + num[col-1];
		}
		
		for (p = 0; p < A.tu; ++p) {
			col=A.data[p].j;//获取A中data区域元素的列
			q=cpot[col];//获取对应列在B中的位置
			B.data[q].i=A.data[p].j;
			B.data[q].j=A.data[p].i;
			B.data[q].e=A.data[p].e;
			++cpot[col];//同一列可能有多个元素，自动指向B中下一个位置，
			//当遇到col相同的元素时，就可对同列的下一个元素操作
		} 
	} else {
		cout << "no non-zero element";
	}
	delete[] num;
	delete[] cpot;
}

#endif