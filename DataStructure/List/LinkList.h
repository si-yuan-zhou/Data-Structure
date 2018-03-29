#ifndef __LinkList_H__
#define __LinkList_H__

// 单链表，左后一个节点指向NUll
//HEAD->NODE1->NODE2->……->NODE$->NULL
template<class T>
struct Node{//表节点含有数据域和指向下 一个节点的指针
	T data;
	Node<T> *next;
};
template<class T>
class LinkList
{
private:
	Node<T> *Head;//链表头指针
public:
	LinkList();//构造函数，创建空表
	~LinkList();//析构函数，删除表
	void CreateList(int n);//创建具有n个节点的线性表
	void Insert(int i,T e);//在表的第i个位置插入节点e
	T Delete(int i);//删除第i个元素
	T GetElem(int i);//获取第i个元素的值
	int Locate(T e);//查询元素e所在位置
	T prior(T e);//返回e的前驱
	int Empty();//判断表是否为空
	int Length();//测标的长度
	void ListDisplay();//输出表中的元素
};
#endif

template<class T>
LinkList<T>::LinkList(){
	Head=new Node<T>;//头指针为引导指针，不计算在链表数中
	Head->next=NULL;
}
template<class T>
LinkList<T>::~LinkList(){
	Node<T> *p;
	while(Head){/*每次头节点后移，然后删除头节点，*/
		p=Head;
		Head=Head->next;
		delete p;
	}
	Head=NULL;
}
template<class T>
void LinkList<T>::CreateList(int n){
	Node<T> *p,*s;//创建两个工作指针
	p=Head;
	cout<<"Please Input"<<n<<"datas in turns"<<endl;
	for(int i=1;i<=n;i++){
		s=new Node<T>;//创建新的节点
		cin>>s->data;
		s->next=p->next;//新节点指向当前链表结尾所指向的位置（NULL）
		p->next=s;//当前链表结尾的节点指向新的节点，新节点加入
		p=s;//工作指针指向新加入的节点
	}
}
template<class T>
void LinkList<T>::Insert(int i,T e){//插入到i节点的前面
	int j=0;//创建计数器
	Node<T> *p;//创建工作指针
	p=Head;
	while(p && j<i-1){/*定位到i节点的前面，j=i-1,p向后移动j次，如果p指向NULL即链表结束或者定位到i节点前则返回*/
		p=p->next;
		j++;//满足条件时j=i-1,p向后移动j次
	}
	if(!p||j>i-1) throw"The place you input is wrong";//p指向null或者在i后面则报错;(此处判断是因为上一个while语句跳出条件有多个)
	//i<0或i>表长
	else{
		Node<T> *s;
		s=new Node<T>;
		s->data=e;
		s->next=p->next;
		p->next=s;
	}
}
template<class T>
T LinkList<T>::Delete(int i){
	T x;
	int j=0;//创建计数器
	Node<T> *p,*q;//创建工作指针
	p=Head;
	while(p->next && j<i-1){
	/*p定位到i节点的前驱，j=i-1,p向后移动j次，如果p的下一个指向NULL即链表结束（一定要定位到要操作的元素的前驱，
	因为有next指针可以访问到其后的所有元素，而无法访问到前面的元素）或者定位到i节点前则返回*/
		p=p->next;
		j++;//满足条件时j=i-1,p向后移动j次
	}
	if(!p->next||j>i-1) throw"The place you input is wrong";//p->next指向null或者在i后面则报错
	else{
		q=p->next;//保留要删除的元素
		p->next=q->next;//要删除的节点的前驱的next指针指向待删除节点的后继
		x=q->data;
		delete q;
		return x;
	}
}
template<class T>
int LinkList<T>::Locate(T e){
	int j=1;//计数器
	Node<T> *p;
	p=Head->next;//p指向首节点
	while(p&&p->data!=e){
		/*查找元素e，如果p指向null或者找到e则跳出*/
		p=p->next;
		j++;
	}
	if(p==NULL){
	 //cout<<"no element";
	 return 0;
	}else{
		return j;
	}

}
template<class T>
T LinkList<T>::GetElem(int i){
	int j=1;//计数器
	Node<T> *p;
	p=Head->next;//p指向首节点
	while(p&&j<i){
		/*查找元素e，如果p指向null或者j=i则跳出*/
		p=p->next;
		j++;
	}
	if(!p||j>i){
	 throw"place error";
	}else{
		return p->data;
	}

}
template<class T>
int LinkList<T>::Empty(){
	if(Head->next==NULL)
		return 1;
	else
		return 0;
}
template<class T>
T LinkList<T>::prior(T e){//返回元素的前驱值
	Node<T> *q,*p;
	p=Head;
	q=p->next;
	while(q&&q->data!=e){//如果q指向null或者q的data为e则退出，
		p=q;
		q=q->next;
	}
	if(p==Head)throw"no prior";
	else if(q==NULL) throw"no element e";
	else return p->data;
}
template<class T>
int LinkList<T>::Length(){
	int length=0;
	Node<T> *p;
	p=Head;
	while(p->next){
		length++;
		p=p->next;
	}
	return length;
}
template<class T>
void LinkList<T>::ListDisplay(){
	Node<T> *p;
	int i=0;
	p=Head->next;
	while(p){
		cout<<i<<'\t';
		cout<<p->data<<endl;
		i++;
		p=p->next;
	}
}
