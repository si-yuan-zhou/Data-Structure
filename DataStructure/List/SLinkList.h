#ifndef __SLinkList_H__
#define __SLinkList_H__

//静态链表；通过整型指数器表示各与元素的逻辑关系
//每一个节点的cur是其下一个节点在该数组中的实际序号
template<class T>
class SLinkList
{
private:
	struct Tcomp{
		T data;
		int cur;
	};
	Tcomp *sls;//存储数据的以为数组
	int av;//备用链表表头;av存储可以进行实际操作的节点当前位置
	//av只能向后移动或者指向其他位置，av只在已经分配好的空间上移动，创建和插入操作时，操作只在其后的进行
	//不会影响初始化或者clear后创建的但为使用的节点；而删除操作将av移动到删除的节点位置（此处为可用节点，可进行插入）
	//且将这些节点相连，不会影响实际空间中未操作的位置
	//构造函数创建的是物理存储空间，相连后由av进行查找，av此时指向物理空间的首部
	//创建链表函数在已经分配的物理空间上创建逻辑链表，每次操作的是物理上相连的节点因为每次av只向后移动一次
	//创建完成后av指向物理空间中未被使用的首部（即已经被使用的空间的尾部的下一个位置）；再次进行插入操作时，
	//首先判断av==-1，即物理空间是否含有，若有则在av当前位置即未被使用的空间的首部进行操作与其前面的链表进行逻辑上的相连
	//删除操作则将av指向被删除的节点，表示此节点可用，且将这些节点连接在了一起，保证在下次插入的节点数大于删除的节点数是可以正确找到位置
	int sl;//静态链表表头
	int maxlen;//链表可能的最大长度
public:
	SLinkList(int maxsz=100);//创建长度为maxsz的空表
	~SLinkList();//删除表空间
	void CreateList(int n);//创建具有n个节点的链表
	void Insert(int i,T e);//在表的第i个位置插入节点e
	T Delete(int i);//删除第i个元素
	T GetElem(int i);//获取第i个元素的值
	int Locate(T e);//查询元素e所在位置
	int Empty();//判断表是否为空
	int Full();//测表满
	int Length();//测标的长度
	void Clear();//清空表
	void ListDisplay();//输出表中的元素	
};
#endif

template <class T>
SLinkList<T>::SLinkList(int maxsz):maxlen(maxsz ) {//初始化列表初始化成员变量
	//将分配的空间连成一个备用链表，表头由av指向，链尾由-1表示
	sls = new Tcomp[maxlen];//创建存储数据的空间
	sl = -1;//静态链表为空，sl表示静态表物理位置，-1代表表头为表尾的位置，即空表
	for (int i=0;i<maxlen;i++) {
		sls[i].cur=i+1;
	}
	sls[maxlen-1].cur = -1;//创建了一个未初始化的静态表
	av = 0;//创建好已有相对位置关系的静态表后，av=0，表示物理位置为0的节点，在后期操作中又来
	//遍历静态表示使用，相当于工作指针
}
template <class T>
SLinkList<T>::~SLinkList() {
	delete[] sls;
}
template <class T>
void SLinkList<T>::CreateList(int n) {
	int value;
	if (n>maxlen) throw "Parameter illegal!";
	cout<<"Please input"<<n<<"numbers in turns:"<<endl;
	for(int i=0;i<n;i++) {
		cin>>value;
		Insert(i,value);//创建完之后av的值即为链表的节点数且av的值为最后一个节点的位置
	}
}
template <class T>
void SLinkList<T>::Insert(int i,T e) {
	int m,j=0,k;
	m=av;//m位当前操作节点的物理位置
	if(av==-1) {
		//av是工作指针，表示当前操作的节点
		throw "没有空间可以插入！";//av==-1表示实际的物理空间已经分配完毕，没有可用空间
	}
	av=sls[av].cur;//av指向下一个节点
	if (sl==-1) {
		sls[m].data=e;
		sls[m].cur=-1;
		sl=m;
	} else if (i==1) {
		sls[m].data=e;
		sls[m].cur=sl;
		sl=m;
	} else {
		k=sl;//工作指针（理解为指针）指向链表的头
		while (j<i-1&&k!=-1) {
			//k=-1表示已经达到表尾部
			j++;
			if (j<i-1)
				k=sls[k].cur;//k位位置i的前一个位置
		}
		if (j!=i-1) throw "位置异常！";
		sls[m].data=e;
		sls[m].cur=sls[k].cur;
		sls[k].cur=m;
	}
}
template <class T>
T SLinkList<T>::Delete(int i) {
	int m,j=0,k;
	if (sl==-1) throw "静态链表为空";
	else if (i==1) {
		m=sl;
		sl=sls[sl].cur;//使链表的表头指向下一个节点
		sls[m].cur=av;//av是实际意义上的工作指针，指向当前操作的节点，m是其在函数内部的替代
		av=m;
		return sls[m].data;
	} else {
		k=sl;
		while (j<i-1&&k!=-1) {
			j++;
			if (j<i-1) {
				k=sls[k].cur;
			}
		}
		if (j!=-1) throw "位置异常！";
		m=sls[k].cur;
		sls[k].cur=sls[m].cur;
		sls[m].cur=av;
		av=m;
		return sls[m].data;
	}
}
template <class T>
int SLinkList<T>::Locate (T e) {
	int k=sl,j=1;//k表示链表的头，j为计数器
	while (k!=-1 && sls[k].data !=e) {
		k=sls[k].cur;
		j++;
	}
	if (k == -1) return -1;
	else return j;
}
template <class T>
void SLinkList<T>::Clear() {
	sl = -1;
	for (int i = 0;i < maxlen; i++) {
		sls[i].cur = i + 1;
	}
	sls[maxlen-1].cur = -1;
	av = 0;
}
template <class T>
T SLinkList<T>:: GetElem (int i) {
	int k,j = 0;
	k = sl;
	while (j < i && k != -1) {
		j++;
		if (j < i) k=sls[k].cur;
	}
	if (j == i) return sls[k].data;//sls[j].data同义，k表示下一个节点的位置
	else throw "位置异常！";
}
template <class T>
int SLinkList<T>:: Empty() {
	if (sl == -1) 
		return 1;
	else 
		return 0;
}
template <class T>
int SLinkList<T>:: Full() {
	if (av == -1)
		return 1;
	else
		return 0;
}
template <class T>
int SLinkList<T>:: Length() {
	int k, len = 0;
	k = sl;
	while (k != -1) {
		len++;
		k =sls[k].cur;
	}
	return len;
}
template <class T>
void SLinkList<T>::ListDisplay() {
	int k,i = 1;
	k = sl;
	while (k != -1) {
		cout << i <<"\t";
		cout <<sls[k].data<<endl;
		k=sls[k].cur;
		i++;
	}
}
