#ifndef __BASE_H__
#define __BASE_H__
template <class T>
struct BTNode{
	T data;
	int lflag;
	int rflag;
	BTNode<T> *lchild;
	BTNode<T> *rchild;
};
template <class T>
class CThread{
	public:
		BTNode<T> *BT;
		CThread(){BT = NULL;}
		~CThread();
		void DeleteNode(){Clear(BT,0);}
		void Clear(BTNode<T>*bt,int flag);
		void CreateBTree(T end);
		void create(BTNode<T> *p,int flag,T end);
		BTNode<T>* GetRoot(){return BT;}
};
#endif
template <class T>
CThread<T>::~CThread(){
	DeleteNode();
	BT = NULL;
}
template <class T>
void CThread<T>::create(BTNode<T> *p,int flag,T end){
	//flag为1时创建左子树，2时创建右子树
	BTNode<T> *q;
	T x;
	cin >> x;
	if(x != end) {
		//create a node
		q = new BTNode<T>;
		q->data = x;
		q->lchild = NULL;
		q->rchild = NULL;
		q->rflag = 0;	//rflag为0指向右孩子，为1指向后继
		q->lflag = 0;	//lflag为0指向左孩子，为1指向前驱
	
		if(flag == 1) {
			p->lchild = q;
		}//endif
		if(flag == 2) {
			p->rchild = q;
		}//endif
		
		create(q,1,end);
		create(q,1,end);
	}//endif
}
template <class T>
void CThread<T>::CreateBTree(T end){
	cout <<"Please input node in Preorder,-1 equals end:"<<endl;
	BTNode<T> *p;
	T x;
	cin >> x;
	if(x != end) {
		//创建头结点
		p = new BTNode<T>;
		p->data = x;
		p->lchild = NULL;
		p->rchild = NULL;
		p->lflag = 0;
		p->rflag = 0;
		BT = p;
		//创建剩余的结点
		create(p,1,end);
		create(p,2,end);
	}//endif
}
template <class T>
void CThread<T>::Clear(BTNode<T> *bt,int flag){
	if(bt && flag != 1) {
		//函数的意义是删除结点的左树或右子树，且子树存在即flag !=1
		//删除是按照后序遍历顺序删除，flag==1代表没有左或右子树
		Clear(bt->lchild,bt->lflag);
		Clear(bt->rchild,bt->rflag);
		cout << bt->data << " :release pointer"<< bt <<"'s space"<<endl;
		delete bt;
	}//endif
}
