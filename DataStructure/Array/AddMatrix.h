typedef struct MNode {
	int i,j;//行号，列号
	int e;//非零元素
	MNode *next;//指向同行下一个节点
}MNode,*MLink;
typedef struct 
{
	int mu,nu,tu;//行数，列数，非零元素个数
	MLink *rops;//存放各行链表的头指针
}LMatrix;
int cmp(int a,int b) {//列号比较
	if(a<b) return -1;
	else if(a==b) return 0;
	else return 1;
}
void NodeCopy(MNode *s,MNode *x) {//节点复制
	s->e = x->e;
	s->i = x->i;
	s->j = x->j;
}
void AddNode(MNode *lp,MNode *lq,MNode *s) {
	MNode *p;
	p=new MNode;
	NodeCopy(p,s);
	p->next=NULL;
	if(lp==NULL) {
		lp=p;
		lq=p;
	} else {
		lq->next=p;
		lq=p;
	}
}
LMatrix MAdd(LMatrix ma,LMatrix mb) {
	LMatrix mc;
	MNode *pa,*pb,*pc;//分别指向被加数，加数和矩阵行向量的首元节点
	MNode *s;
	int i,sum;
	int m,n;//行数，列数
	int flag=1;
	m=ma.mu;
	n=ma.nu;
	mc.mu=m;
	mc.nu=n;
	mc.tu=0;
	mc.rops=NULL;
	if(mc.rops)delete[] mc.rops;
	mc.rops=new MLink[m];
	for (i = 0; i < m; ++i)
	{
		mc.rops[i]=NULL;//c行指针向量初始化
	}
	for (i = 0; i < m; ++i)
	{
		pa=ma.rops[i];
		pb=mb.rops[i];
		pc=mc.rops[i];
		while(pa && pb){//被加矩阵，加矩阵行链不空
			flag=1;
			switch(cmp(pa->j,pb->j)){//列数比较
				case -1:
					s=new MNode;
					NodeCopy(s,pa);
					s->next=NULL;
					pa=pa->next;
					break;
				case 0:
					sum = pa->e+pb->e;
					if(sum==0) flag=0;
					else{
						s=new MNode;
						NodeCopy(s,pa);
						s->e=sum;
						s->next=NULL;
					}
					pa = pa->next;
					pb = pb->next;//pa pb后移
					break;
				case 1:
					s=new MNode;
					NodeCopy(s,pb);//复制pb所指的节点
					pb=pb->next;//pb后移
					s->next=NULL;
					break;
			}//end switch
			if(flag){
				mc.tu++;
				AddNode(mc.rops[i],pc,s);
			}
		}//end while
		if(pa){
			while(pa){
				NodeCopy(s,pa);
				pa=pa->next;
				AddNode(mc.rops[i],pc,s);
			}
		}
		if(pb){
			while(pb){
				NodeCopy(s,pb);
				pb=pb->next;
				AddNode(mc.rops[i],pc,s);
			}//while
		}//if(pb)
	}//for
	return mc;
}
void MDisp(LMatrix a){
	MNode *p;
	int i,j,c=0;
	for (i = 0; i < a.mu; ++i)
	{
		p=a.rops[i];
		for (j = 0; j < a.nu; ++j)
		{
			if(p==NULL)
				cout<<'\t'<<c;
			else if(j<p->j)
				cout<<'\t'<<c;
			else{
				cout<<'\t'<<p->e;
				p=p->next;
			}
		}
		cout<<endl;
	}
}
LMatrix MCreate(int d[][3],int m,int n,int k) {
	LMatrix M={m,n,k,NULL};
	int i,r1,r2;
	MNode *s,*p;//工作指针
	if(M.rops) delete[] M.rops;
	M.rops=new MLink[m];
	for (i = 0; i < m; ++i)
	{
		M.rops[i]=NULL;
	}
	r1=m;
	p=M.rops[r1];
	for (i = 0; i < k; ++i)//扫描非零元 数组
	{
		s=new MNode;
		s->i = d[i][0];
		s->j = d[i][1];
		s->e = d[i][2];
		r2 = s->i;//非零元 所在行
		if(r2!=r1){//创建链表第1个节点
			M.rops[r2]=s;
			s->next=NULL;
			p=s;
			r1=r2;
		} else {//创建链表非首元节点
			s->next=p->next;
			p->next=s;
			p=s;
		}
	}
		return M;
}
