#ifndef __SqStack_H__
#define __SqStack_H__

//Sequence Stack
template <class T>
class SqStack
{
private:
	T *base;
	int top;
	int stacksize;
public:
	SqStack(int m);
	~SqStack();
	void Push(T x);
	T Pop();
	T GetTop();
	int StackEmpty();
	void ClearStack();
	void StcakTop();//return top pointer||where is top
	void StackTranverse();//display elements in Stack
};
#endif

template <class T>
SqStack<T>::SqStack(int m) {
	base = new T[m];//base remains the first address of array
	if (base == NULL) {
		cout <<"Stack is not been created!";
		exit(1);
	}
	stacksize = m;
	top = -1;
}
template <class T>
SqStack<T>::~SqStack() {
	delete[] base;
	top = 0;
	stacksize = 0;
}
template <class T>
void SqStack<T>::Push(T x) {
	if (top == stacksize - 1) {
		throw "Stack is full!";
	}
	top++;
	base[top] = x;
}
template <class T>
T SqStack<T>::Pop() {
	if (top == -1) throw "Stack is empty!";
	T x=base[top--];
	return x;
}
template <class T>
T SqStack<T>::GetTop() {
	if (top == -1) throw "Stack is empty!";
	return base[top];
}
template <class T>
int SqStack<T>::StackEmpty() {
	if (top == -1)
		return 1;
	else
		return 0;
}
template <class T>
void SqStack<T>::ClearStack() {
	top = -1;
}
template <class T>
void SqStack<T>:: StcakTop() {
	cout<<"Stack top is at "<<top<<endl;
}
template <class T>
void SqStack<T>::StackTranverse() {
	int i = top;
	while (i >= 0) {
		cout << base[i--]<<'\t';
	}
	cout<<endl;
}
