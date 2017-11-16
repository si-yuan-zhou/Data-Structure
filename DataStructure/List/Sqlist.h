//顺序表
template<class T>
class Sqlist{
private:
	T *elem;//表首地址
	int length;//表长
	int listsize;//表容量
public:
	Sqlist(int m);//构造函数，创建容量为m的空表
	~Sqlist();//析构函数
	void CreateList(int n);//创建具有n个元素的线性表
	void Insert(int n,T e);//在第i个位置插入元素
	T Delete(int i);//删除第i个元素
	T GetElem(int n);//获得第i个元素
	int Locate(T e);//找到元素e并返回元素所在的位置
	void Clear();//清空表
	int Empty();//判断表是否为空
	int Full();//判断表是否为空
	int Length();//計算表長度
	void ListDisp();//输出表的内容
};
template<class T>
Sqlist<T>::Sqlist(int m){
	elem=new T[m];//创建容量为m的空表
	length=0;//初始化表的长度为0
	listsize=m;//表的容量为m
}
template<class T>
Sqlist<T>::~Sqlist(){
	delete [] elem;
	length=0;
	listsize=0;
}
template<class T>
void Sqlist<T>::CreateList(int n){/*创建长度为n的顺序列表*/
	if(n>listsize) throw "arguments error";
	cout<<"Please input "<<n<<"numbers in turns"<<endl;
	for(int i=1;i<=n;i++)
		cin>>elem[i-1];
	length=n;
	
}
template<class T>
void Sqlist<T>::Insert(int i,T e){/*在位置i出插入元素e，如果不能插入，返回错误信息*/
	if(length>=listsize) throw"The list has been filled";
	if(i<1||i>length+1) throw"The place you insert is illegal";
	for(int j=length;j>=i;j--)
		elem[j]=elem[j-1];/*将位置i处后的元素以此向后挪*/
	elem[i-1]=e;
	length++;
}
template<class T>
T Sqlist<T>::Delete(int i){/*删除位置i处的元素*/
	T x;
	if(length==0) throw"The list is Empty";
	if(i<1||i>length+1) throw"The place you delete is illegal";
	x=elem[i-1];
	for(int j=i;j<length;j++)
		elem[j-1]=elem[j];
	length--;
	return x;	
}
template<class T>
int Sqlist<T>::Locate(T e){/*查找元素e的位置*/
	for(int i=0;i<length;i++){
		if(elem[i]==e) return i+1;
		return 0;
	}
}
template<class T>
void Sqlist<T>::Clear(){
	length=0;
}
template<class T>
T Sqlist<T>::GetElem(int i){/*获取位置i处的元素*/
	T e;
	if(i<1||i>length) throw"The place is illegal";
	e=elem[i-1];
	return e;
}
template<class T>
int Sqlist<T>::Empty(){/*判断表是否为空*/
	if(length==0)
		return 1;
	else
		return 0;
}
template<class T>
int Sqlist<T>::Full(){
	if(length==listsize)
		return 1;
	else 
		return 0;
}
template<class T>
int Sqlist<T>::Length(){
	return length;
}
template<class T>
void Sqlist<T>::ListDisp(){
	for(int i=0;i<length;i++){
		cout<<i+1<<"\t";
		cout<<elem[i]<<endl;
	}
}
