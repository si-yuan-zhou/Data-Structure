#ifndef __LinkStack_H__
#define __LinkStack_H__

//LinkStack no length property
template <class T>
struct Node{
	T data;
	Node<T> *next;//T can be ignored
};
template <class T>
class LinkStack
{
private:
	Node<T> *top;
public:
	LinkStack();
	~LinkStack();
	void Push(T x);
	T Pop();
	T GetTop();//Just display top element
	int StackEmpty();
	void ClearStack();
	void SatckTanverse();
};
#endif

template <class T>
LinkStack<T>::LinkStack() {
	top = NULL;
}
template <class T>
LinkStack<T>::~LinkStack() {
	Node<T> *p;
	while (top) {
		p = top;
		top = top->next;
		delete p;
	}
}
template <class T>
void LinkStack<T>::Push(T x) {
	Node<T> *p;
	p = new Node<T>;
	p->data = x;
	p->next = top;
	top = p;
}
template <class T>
T LinkStack<T>::Pop() {
	Node<T> *p;
	T x;
	if (top == NULL) throw "Stack has been empty!";
	x = top->data;
	p = top;
	top =top->next;
	delete p;
	return x;
}
template <class T>
T LinkStack<T>::GetTop() {
	if (top == NULL) throw "Stack has been empty!";
	return top->data;
}
template <class T>
void LinkStack<T>::ClearStack() {
	while (top) {
		Node<T> *p;
		p = top;
		top = top->next;
		delete p;
	}
}
template <class T>
int LinkStack<T>::StackEmpty() {
	if (top == NULL)
		return 1;
	else
		return 0;
}
template <class T>
void LinkStack<T>::SatckTanverse() {
	Node<T> *p;
	while(p) {
		cout<<p->data<<'\t';
		p =p->next;
	}
	cout<<endl;
}
