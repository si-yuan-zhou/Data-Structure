 //循环队列
template <class T>
class CirQueue{
private:
	T *base;//存储空间基址
	int front;//队头指针
	int rear;//队尾指针
	int queuesize;//队容量
public:
	CirQueue(int m);
	~CirQueue();
	void EnQueue(T x);//元素x入队
	T DeQueue();//队顶元素出队
	T GetHead();//取队顶元素
	T GetLast();//缺队尾元素
	int QueueEmpty();//判断队空
	int QueueFull(); //判断对满
	void ClearQueue();//清空队
	void Pointer();//返回队头，队尾位置
	void QueueTranverse();//遍历队，输出队的元素
};
template <class T>
CirQueue<T>::CirQueue(int m){
	base=new T[m];
	if (base==NULL){
		cout<<"Queue create failed!";
		exit(0);
	}
	front =rear=0;
	queuesize = m;
}
template <class T>
CirQueue<T>::~CirQueue(){
	delete[] base;
	rear=0;
	front=0;
	queuesize=0;
}
template <class T>
void CirQueue<T>::EnQueue(T x){//入队
	if ((rear+1)%queuesize==front) throw "Full!";
	base[rear]=x;
	rear=(rear+1)%queuesize;//rear指向待插入的位置（此时还没有值）
}
template <class T>
T CirQueue<T>::DeQueue(){//出队
	T x;
	if(front==rear) throw "No element";
	x=base[front];//front为要删除的
	front=(front+1)%queuesize;//front 指向待删除的位置
	return x;
}
template <class T>
T CirQueue<T>::GetHead(){
	T x;
	if(front==rear) throw "No element";
	x=base[front];
	return x;
}
template <class T>
T CirQueue<T>::GetLast(){
	T x;
	if(front==rear) throw "No element";
	x=base[rear-1];
	return x;
}
template <class T>
int CirQueue<T>::QueueEmpty(){
	if(front==rear)
		return 1;
	else
		return 0;
}
template <class T>
int CirQueue<T>::QueueFull(){
	if((rear+1)%queuesize==front)//必须判断rear前是否未被使用
		return 1;
	else
		return 0;
}
template <class T>
void CirQueue<T>::ClearQueue(){
	front=rear=0;
}
template <class T>
void CirQueue<T>::Pointer(){//返回队首尾位置
	cout<<"front="<<front<<endl;
	cout<<"rear="<<rear<<endl;
}
template <class T>
void CirQueue<T>::QueueTranverse(){//遍历输出
	int i=front;
	while(i!=rear){
		cout<<base[i]<<'\t';
		i=(i+1)%queuesize;
	}
	cout<<endl;
}
