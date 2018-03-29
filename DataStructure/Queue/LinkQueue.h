#ifndef __LinkQueue_H__
#define __LinkQueue_H__

 //链队
template <typename T>
struct Node{
	T data;
	Node<T> *next;
};
template <typename T>
class LinkQueue{
private:
	Node<T> *front;//指向头节点即front->next指向头节点
	Node<T> *rear;
public:
	LinkQueue();
	~LinkQueue();
	void EnQueue(T x);//入队
	T DeQueue();//出队
	T GetHead();//取队首元素
	T GetLast();//取队尾元素
	int QueueEmpty();
	void ClearQueue();
	void QueueTranverse();//遍历 
};
#endif

template <typename T>
LinkQueue<T>::LinkQueue(){
	front=new Node<T>;
	front->next=NULL;
	rear=front;
}
template <typename T>
LinkQueue<T>::~LinkQueue(){
	Node<T> *p;
	while(front!=NULL){
		p=front;
		front=front->next;
		delete p;
	}
}
template <typename T>
void LinkQueue<T>::EnQueue(T x){
	Node<T> *s;
	s=new Node<T>;
	s->data=x;
	s->next=rear->next;
	rear->next=s;
	rear=s;
	if(front->next==NULL){//创建的是第一个节点
		front->next=s;//是头指针的next指向第一个节点
	}
}
template <typename T>
T LinkQueue<T>::DeQueue(){
	T x;
	Node<T> *p;
	if(rear==front) throw "Empty";
	p=front->next;
	x=p->data;
	front->next=p->next;
	if(p->next==NULL) rear=front;
	delete p;
	return x;
}
template <typename T>
T LinkQueue<T>::GetHead(){
	T  x;
	if(rear==front) throw "Empty!";
	x=front->next->data;
	return x;
}
template <typename T>
T LinkQueue<T>::GetLast(){
	if(rear==front) throw "Empty!";
	return rear->data;
}
template <typename T>
void LinkQueue<T>::ClearQueue(){
	Node<T> *p;
	p=front->next;
	while(p){
		front->next=p->next;
		delete p;
		p=front->next;
	}
	rear=front;
}
template <typename T>
int LinkQueue<T>::QueueEmpty(){
	if (rear==front)
		return 1;
	else
		return 0;
}
template <typename T>
void LinkQueue<T>::QueueTranverse(){
	Node<T> *p;
	p=front->next;
	while(p){
		front->next=p->next;
		cout<<p->data<<'\t';
		p=front->next;
	}
	cout<<endl;
}
