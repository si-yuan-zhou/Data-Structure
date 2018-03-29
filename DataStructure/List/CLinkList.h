// 循环链表，最后一个节点指向head
//HEAD->NODE1->NODE2->NODE3->...->NODE->HEAD
#ifndef __ClinkList_H__
#define __ClinkList_H__

template<class T>
struct Node{//表节点含有数据域和指向下 一个节点的指针
	T data;
	Node *next;
};
template<class T>
class CLinkList
{
private:
	Node<T> *Head;//链表头指针
public:
	CLinkList();//构造函数，创建空表
	~CLinkList();//析构函数，删除表
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
CLinkList<T>::CLinkList(){
	Head=new Node<T>;//头指针为引导指针，不计算在链表数中
	Head->next=Head;
}
template<class T>
CLinkList<T>::~CLinkList(){
	Node<T> *p,*q;
	q=Head;
	while(q->next!=Head) q=q->next;//q指向尾节点
	while(Head!=Head->next){
		p=Head;//从节点开始删除，每次将工作指针指向待删除节点的next，然后让尾节点指向head
		Head=Head->next;
		q->next=Head;
		delete p;
	}
	Head=NULL;
}
template<class T>
void CLinkList<T>::CreateList(int n){
	Node<T> *p;
	p=Head;
	cout<<"Pelase input "<<n<<"datas in turns"<<endl;
	for(int i=0;i<n;i++){
		Node<T> *s;
		s=new Node<T>;
		cin>>s->data;
		s->next=p->next;/*Head->next==>Head,....->new_node->next==>p->next(Head),....->p->next==>new_node*/
		p->next=s;
		p=s;
	}
}
template<class T>
void CLinkList<T>::Insert(int i,T e){
	int j=0;//创建一个计数器
	Node<T> *p;
	p=Head;
	while(p->next!=Head&&j<i-1){//定位到插入点前，i必须大于1，该循环最多执行i-1次
		 p=p->next;
		 j++;
	}
	if(p->next==Head||j>i-1) throw"place error";//上面的while循环跳出的可能为p->next!=head但j=i-1（即定位到目标节点的前面）
	//或者是还没有找到i的前驱就已经遍历到尾节点了即p->next==head
	else{
		Node<T> *s;
		s=new Node<T>;
		s->data=e;
		s->next=p->next;
		p->next=s;
	}

}
template<class T>
T CLinkList<T>::Delete(int i){
	T x;
	int j=0;//创建一个计数器
	Node<T> *p,*q;
	p=Head;
	while(p->next!=Head&&j<i-1){//定位到插入点前驱节点
		 p=p->next;
		 j++;
	}
	if(p->next==Head||j>i-1) throw"place error";//上面的while循环跳出的可能为p->next!=head但j=i-1（即定位到目标节点的前面）
	//或者是还没有找到i的前驱就已经遍历到尾节点了即p->next==head,删除和插入等操作必须找到对应节点的前驱
	else{
		q=p->next;
		p->next=q->next;
		x=q->data;
		delete q;
		return x;
	}
}
template<class T>
int CLinkList<T>::Locate(T e){
	int j=1;
	Node<T> *p;
	p=Head->next;
	while(p!=Head&&p->data!=e){
		p=p->next;
		j++;
	}
	if(p==Head) return 0;
	else return j;
}
template<class T>
T CLinkList<T>::GetElem(int i){
	Node<T> *p;
	p=Head->next;
	int j=1;
	while(p!=Head&&j<i){
		p=p->next;
		j++;
	}
	if(p==Head||j>i)throw"no Element";
	else return p->data;
}
template<class T>
int CLinkList<T>::Empty(){
	if(Head==Head->next){
		return 1;
	}else{
		return 0;
	}
}
template<class T>
T CLinkList<T>::prior(T e){
	Node<T> *p,*q;
	q=Head;
	p=p->next;
	while(p!=Head&&p->data!=e){
		q=p;
		p=p->next;
	}
	if(p==Head) throw"no element";
	else if(q==Head) throw"the Head has no prior";
	else return q->data;
}
template<class T>
int CLinkList<T>::Length(){
	int len=1;
	Node<T> *p;
	p=Head->next;
	while(p!=Head){
		p=p->next;
		len++;
	}
	return len;
}
template<class T>
void CLinkList<T>::ListDisplay(){
	Node<T> *p;
	p=Head->next;
	int i=1;
	while(p!=Head){
		cout<<i<<"\t";
		cout<<p->data<<endl;
		p=p->next;
		i++;
	}
}
