#ifndef __DATADEF__
#define __DATADEF__

//顺序表的定义与实现
template <class T>
struct SqList{
	T *key;		//keyword
	int length;	//char length
};
template <class T>
void CreateSqList(SqList<T> &sl){
	//创建排序表
	int n;
	cout <<"创建顺序表"<<endl<<"请输入顺序表的长度"<<endl;
	cin >>n;
	sl.length = n;
	sl.key = new T[sl.length+1];
	cout <<"请输入数据："<<endl;
	for(int i = 1;i <= sl.length; ++i){
		//一共length个元素，从1开始，第0个元素作为哨兵，用于存放临时交换元素	
		cin >> sl.key[i];
	}//endfor
}
template <class T>
void OutPut(SqList<T> &L){
	for(int i = 1;i <= L.length; ++i){
		cout << L.key[i] << "\t";
	}//endfor
	cout << endl;
}

//数据表类定义
const int SIZE = 100;		//静态链表最大容量
const int MAXINT = 10000;	//最大整数

template <class T>
struct StaListNode{
	T data;		//记录项
	int next;	//指针项
};
template <class T>
class StaticList {
	public:
		StaListNode<T> node[SIZE];
		int curlen;	//链表实际长度
		StaticList();
		//~StaticList();
};
template <class T>
StaticList<T>::StaticList(){
	cout << "创建静态链表"<<endl;
	cout << "请输入静态链表的实际长度："<<endl;
	cin  >>curlen;
	cout << "请输入各结点数量："<<endl;
	node[0].data = MAXINT;
	node[0].next = 0;
	for(int i = 1;i <= curlen; ++i){
		node[i].next = 0;
		cin >> node[i].data;
	}//endfor
}

//树形选择排序
template <class T>
class TreeNode {
	public:
		T data;	//结点数据值
		int index;//树中位置
		int active;//是否继续比较
		TreeNode<T>& operator= (TreeNode<T>& treenode){
			this->data = treenode.data;
			this->index = treenode.index;
			this->active = treenode.active;
			return *this;
		}
};

template <class T>
void OutPut(T a[],int n){
	for(int i = 0;i < n; ++i){
		cout << a[i] <<"\t";
	}//endfor
	cout<<endl;
}
//链式基数排序
const int RADIX = 10;
//对于基数排序只能是int 元素类型
typedef int ArrType[RADIX];
ArrType f,e;

template <class T>
struct SLCell{
	T *keys;
	int next;
};
template <class T>
struct SLList{
	SLCell<T> *SList;
	int keynum;
	int recnum;
};
template <class T>
void OutPut(SLList<T> &SL){
	for(int i = SL.SList[0].next;i;i=SL.SList[i].next){
		for(int j = 1;j <= SL.keynum;j++){
			cout <<SL.SList[i].keys[j];
		}//endfor
		cout<<"\t";
	}//endfor
	cout<<endl;
}
#endif
