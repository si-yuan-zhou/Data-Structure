typedef struct {
	int i,j;
	int e;
}MNode;
typedef struct {
	int mu,nu,tu;
	MNode* data;
}SMatrix;
SMatrix MCreate(int d[][3],int m,int n,int k) {
	SMatrix M = {m,n,k,NULL};
	if (k != 0) {
		M.data = new MNode[k]; 
	}
	for (int i = 0; i < k; ++i) {
		M.data[i].i = d[i][0];
		M.data[i].j = d[i][1];
		M.data[i].e = d[i][2];
	}
	return M;
}
void MDisp(SMatrix &M){
	MNode p;
	int k = 0,c = 0;
	p = M.data[k];
	for (int i = 0; i < M.mu; ++i) {
	 	for (int j = 0; j < M.nu; ++j) {
	 		if (k < M.tu && i == p.i && j == p.j) {
	 			cout << '\t' << p.e;
	 			k++;
	 			if(k < M.tu)
	 				p = M.data[k];
	 		} else {
	 			cout << '\t' << c;
	 		}
	 	}
	 	cout << endl;
	 } 
}
SMatrix MMul(SMatrix ma,SMatrix mb) {
	SMatrix mc;
	int m1,n1,k1,m2,n2,k2;
	int *num,*rpot,*ctemp;
	int i,j,k,r,t,p,q;

	m1 = ma.mu;
	n1 = ma.nu;
	k1 = ma.tu;

	m2 = mb.mu;
	n2 = mb.nu;
	k2 = mb.tu;

	mc.mu = m1;
	mc.nu = n2;
	r = m1 * n2;
	mc.data = new MNode[r];
	num = new int[m2];
	for(i = 0;i < m2;++i) {
		num[i] = 0;//各行非零元素个数计数器初始化
	}
	rpot = new int[m2+1];
	rpot[0] = 0;
	for(i = 0;i < k2;++i){
		k = mb.data[i].i;
		num[k]++;//计算B阵个各行非零元素个数
	}
	for(i = 1;i <= m2;++i){
		//计算B各行首个非零元在三元组表表中的位置
		rpot[i] = rpot[i-1] + num[i-1];//前一行的第一个非零元素位置加该行非零元素的个数
		//rpot数组存储每行第一个非零元素在data中的位置
	}
	ctemp = new int[n2];
	r = 0;//C的非零元个数
	p = 0;//A的三元组位置指针
	for(i = 0;i < m1;++i) {
		for(j = 0; j < n2;++j)
			ctemp[j] = 0;//累加器初始化

		while(ma.data[p].i == i) {//找到数据区data中的所有该行元素
			k = ma.data[p].j;
			if(k < m2)
				t = rpot[k+1];//确定B中第K行的非零元素在B中的三元组表中的位置（k+1）是因为rpot的第0个元素为0
			else
				t = mb.tu + 1;//如果A中的该元素在B中对应的元素的行超过B的行，则B的非零元素加一
			for(q = rpot[k];q < t;++q) {//rpot[k] 到 t 的长度表示B中第K行的非零元素数
				j = mb.data[q].j;
				ctemp[j] += ma.data[p].e * mb.data[q].e;
				/*
					用A中某行某列的元素与B中对应行的所有列元素相乘
					（因为在A中的每个元素只会与B中每列中对应行的元素相乘）
					然后存储在ctemp数组中，ctemp存储B每列与A对应行的乘积和（所以ctemp的长度是B的列数）
					举例：A的第一行第一列的元素与B的第一行的每个元素相乘（因为A[0,0]只会与B的每列的第一个元素相乘）
					，把与B中的每列的乘积存储在对应的ctemp[i]中，ctemp[i]表示B中该列A与B对应元素运算后的结果
					（一次运算只表示B中一行中各列的结果，然后在外侧循环中A换行，ctmp也换行，结果加上该列的上一行的结果
					，最终的结果就是B中该列的结果），
				*/	
			}
			p++;
		}
		for(j = 0;j < n2;++j){
			if(ctemp[j] != 0) {
				r++;
				mc.data[r-1].i = i;
				mc.data[r-1].j = j;
				mc.data[r-1].e = ctemp[j]; 
			}
		}
	}
	mc.tu = r;
	return mc;
}