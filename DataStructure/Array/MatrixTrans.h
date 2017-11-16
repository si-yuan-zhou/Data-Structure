//稀疏矩阵：非零元素远远少余零的个数，且非零元素无序
typedef struct MNode{
	int i,j;//行号和列号
	int e;//非零元
}MNode;//非零节点单元
typedef struct{
	int mu,nu,tu;//行数，列数，非零元素数
	MNode *data;//三元组表
}SMatrix;//矩阵模型
SMatrix MCreate(int d[][3],int m,int n,int k){
	SMatrix M={m,n,k,NULL};//M是一个矩阵含有行数，列数，非零元素数和非零元素数据信息
	if(k!=0)//含有非零元素则需要创空间存储这些元素的信息
		M.data=new MNode[k];//创建k个非零元素（含有位置属性和值信息）
	for(int i=0;i<k;i++){
		// d的每一行包含行号，列号，元素值,为k个元素赋相应属性（位置，data）
		M.data[i].i=d[i][0];
		M.data[i].j=d[i][1];
		M.data[i].e=d[i][2];
	}
	return M;
}
void MDisp(SMatrix a){
	MNode p;
	int i,j,k=0,c=0;
	p=a.data[k];
	for (int i = 0; i < a.mu; ++i) {
		for (int j = 0; j < a.nu; ++j) {
			if(k < a.tu && p.i == i && p.j == j) {
			//k是非零元素的个数，需要小于tu,因为k从零开始,p.i==i&&p.j==j意为找到了非零元素的位置
				cout << '\t'<<p.e;
				// k++;
				// if(k<a.tu) p=a.data[k];
				p=a.data[++k];
			} else {
				cout<<'\t'<<c;
			}
		}//一行
		cout<<endl;
	}
}
void MatrixTrans(SMatrix A,SMatrix B) {
	int col,k,p,q;
	int *num,*cpot;
	num=new int[B.nu];
	cpot=new int[B.nu];
	if(B.tu){//非零元素必须有否则转置无意义
		if(B.tu>=A.tu){
			for(col=0;col<A.tu;++col){//稀疏矩阵要满足B.nu>=A.tu
				num[col]=0;
			}
			for (k = 0; k < A.tu; ++k) {
				++num[A.data[k].j];
				//使num中所有非零元素的列号对应的值加一，即在num数组中，值为一的元素的下标为非零元素所在的列
			}
			cpot[0]=0;
			for(col=1;col<A.nu;++col) {
				cpot[col]=cpot[col-1]+num[col-1];
			}
			for (p = 0; p < A.tu; ++p)
			{
				col=A.data[p].j;
				q=cpot[col];
				B.data[q].i=A.data[p].j;
				B.data[q].j=A.data[p].i;
				B.data[q].e=A.data[p].e;
				++cpot[col];			
			}
		} else {
			int rows=A.mu;
			int cols=A.nu;
			//未完待续。。。
		}
	}
}
