#ifndef __DCLinkList_H__
#define __DCLinkList_H__

//创建双循环链表
template<class T>
struct Node{
	T data;
	Node<T> *next;
	Node<T> *prior;
};
template<class T>
class DCLinkList
{
private:
	Node<T> *Head;
public:
	DCLinkList();
	~DCLinkList();
	void CreateList(int n);//创建具有n个节点的双循环链表
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
DCLinkList<T>::DCLinkList(){
	Head=new Node<T>;
	Head->next=Head;
	Head->prior=Head;
}
template<class T>
DCLinkList<T>::~DCLinkList(){
	Node<T> *p,*q;
	q=Head;
	while(q->next!=Head) q=q->next;
	while(Head!=Head->next){
		p=Head;
		Head=Head->next;
		q->next=Head;
		Head->prior=q;
		delete p;
	}
	Head=NULL;
}
template<class T>
void DCLinkList<T>::CreateList(int n){
	/*新节点的前驱指针指向当前的尾节点；新节点的后继指针指向Head，当前的尾节点的后继指针指向新节点，Head的前驱指针指向新节点，工作指针后移*/       
	Node<T> *p;
	p=Head;
	cout<<"Please input these"<<n<<" data"<<endl;
	for(int i=0;i<n;i++){
		Node<T> *s;
		s=new Node<T>;
		cin>>s->data;
		s->next=p->next;//1
		p->next=s;//2
		s->prior=p;//3
		Head->prior=s;//4,此四句顺序可打乱
		p=s;
	}
}
template<class T>
void DCLinkList<T>::Insert(int i,T e){
	Node<T> *p,*q;
	p=Head;
	int j=0;
	while(p->next!=Head&&j<i-1){//定位到i的前驱
		p=p->next;
		j++;
	}
	if(p->next==Head||j>i-1) throw"place error";//j>i-1表示在i之前，p-》next=Head表示已经将链表遍历结束
	else{
		q=p->next;
		Node<T> *s;
		s=new Node<T>;
		s->data=e;
		s->prior=p;//新节点的前驱是q当前所在，后继是q
		s->next=q;
		p->next=s;
		q->prior=s;
	}
}
template<class T>
T DCLinkList<T>::Delete(int i){
	T x;
	Node<T> *p,*q;
	p=Head;
	int j=0;
	while(p->next!=Head&&j<i-1){//定位到i的前驱
		p=p->next;
		j++;
	}
	if(p->next==Head||j>i-1) throw"place error";//j>i-1表示在i之前，p-》next=Head表示已经将链表遍历结束
	else{
		q=p->next;
		p->next=q->next;
		q->next->prior=p;
		x=q->data;
		delete q;
		return x;
	}
}
template<class T>
int DCLinkList<T>::Locate(T e){
	Node<T> *p;
	p=Head->next;
	int j=0;
	while(p!=Head&&p->data!=e){
		p=p->next;
		j++;
	}
	if(p==Head) throw"no element";
	else return j;
}
template<class T>
T DCLinkList<T>::GetElem(int i){
	Node<T> *p;
	p=Head->next;
	int j=1;
	while(p!=Head&&j<i){//定位到i
		p=p->next;
		j++;
	}
	if(p==Head||j>i) throw"place error";
	else return p->data;
}
template<class T>
int DCLinkList<T>::Empty(){
	if(Head->next==Head) return 1;
	else return 0;
}
template<class T>
T DCLinkList<T>::prior(T e){
	Node<T> *p,*q;
	p=Head->next;
	q=Head;
	while(p!=Head&&p->data!=e){
		q=p;
		p=p->next;
		
	}
	if(p==Head) throw"no element";
	else if(q==Head) return p->prior->data;
	else return q->data;
}
template<class T>
int DCLinkList<T>::Length(){
	int len=0;
	Node<T> *p;
	p=Head;
	while(p->next!=Head){//p=head时len=0，p-》head，len=length
		len++;
		p=p->next;
	}
	return len;
}
template<class T>
void DCLinkList<T>::ListDisplay(){
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
