#ifndef __BSTSEARCH__
#define __BSTSEARCH__

template <class T>
struct Node{
	T key;
	/*other data can be added*/
};
template <class T>
struct BTree{
	Node<T> data;
	BTree<T> *lchild;
	BTree<T> *rchild;
};
template <class T>
class BSTree {
	public:
		int len;
		Node<T> *ST;
		BTree<T> *t;	//root pointer
		BTree<T> *f;	//subtree's root's pointer
		BTree<T> *p;	//point to the last element in find_path
		
		BSTree();
		~BSTree();
		void SearchBST(BTree<T> *t,T key);	//binary sorted tree search
		void InsertBST(BTree<T> *(&t),Node<T> e);//*(&t) means that it can change t's direction,t is not formal parameter
		int DeleteBST(BTree<T> *(&t),T key);
		int Delete(BTree<T> *(&p));
		void DeleteElem(T key);			//delete element in chart
		void InDisplay(BTree<T> *t);	//InOrder Traverse BSTree
		void Display();
};
const int maxsize = 20;
#endif
template <class T>
BSTree<T>::BSTree(){
	ST = new Node<T>[maxsize];
	len = 0;
	t = NULL;
}
template <class T>
BSTree<T>::~BSTree(){
	delete[] ST;
	delete t;
	len = 0;
}
template <class T>
void BSTree<T>::SearchBST(BTree<T> *t,T key){
	if (t == NULL || key == t->data.key) {
		if (t == NULL) {
			cout<<"Not find"<<endl;
		} else {
			cout<<key<<" has been found!"<<endl;
		}
	} else if(key < t->data.key){
		SearchBST(t->lchild,key);
	} else {
		SearchBST(t->rchild,key);
	}
}
template <class T>
void BSTree<T>::InsertBST(BTree<T> *(&t),Node<T> e){
	ST[len] = e;//len < maxsize,用数组ST进行物理上的顺序存储
	len++;
	p = t;

	//用指针进行逻辑上的存储
	//查找插入位置
	while(p){
		if(p->data.key == e.key) {
			cout<<e.key<<" has exited"<<endl;
			return;
		}//endif
		f = p;
		if (e.key < p->data.key) {
			p = p->lchild;
		} else {
			p = p->rchild;
		}
	}

	//插入结点
	p = new BTree<T>;
	p->data = e;
	p->lchild = p->rchild = NULL;
	if (t == NULL) {
		t = p;//由于使用*(&t)所以对t的改变在函数结束后不会取消
	} else {
		if (e.key < f->data.key) {
			f->lchild = p;
		} else {
			f->rchild = p;
		}
	}
}
template <class T>
int BSTree<T>::DeleteBST(BTree<T> *(&t),T key){
	//delete element 
	if (!t) {
		cout<<"BTree is empty!"<<endl;
		return -1;//false
	} else {
		if (key == t->data.key) {
			return Delete(t);
		} else if(key < t->data.key){
			return DeleteBST(t->lchild,key);
		} else {
			return DeleteBST(t->rchild,key);
		}
	}
}
template <class T>
int BSTree<T>::Delete(BTree<T> *(&p)){
	//delete node
	//删除一个结点后树还是二叉搜索树(左小于右)
	BTree<T> *q,*s;
	if (!p->rchild) {		//has no rightSubTree
		q = p;
		p = p->lchild;		//参数*(&p)表示p是个位置，不是工作指针
		/*例如2的右子结点是3，3的右子节点是3，p指向3，
		  2的下一个结点是p，把p指向4，则2的下一个结点是4，删除原来p所指位置
		 */
		delete q;
	} else if(!p->lchild){	//has no leftSubTree
		q = p;
		p = p->rchild;
		delete q;
	} else {				//左右子树都存在,在左子树中找
		q = p;
		s = p->lchild;
		while(s->rchild){
			q = s;			
			s = s->rchild;	//while结束后s是右子树的最右叶节点
		}//转左，向右走到尽头,左子树中最大的
		p->data = s->data;	//s是p按照中序遍历顺序的前驱，把最大值覆盖p原先的值
		//处理完s的右子树后，处理s的左子树
		if (q != p) {
			q->rchild = s->lchild;
		} else {
			/*p现在的值就是s原先的值，所以如果q==p,则s->lchild.data必小于p即小于q，所以链接在q的左边*/
			q->lchild = s->lchild;
		}
		delete s;
	}
	return 1;//true
}
template <class T>
void BSTree<T>::DeleteElem(T key){
	//delete StaticTable element
	//for(int i = 0;i < len && ST[i].key != key; ++i){
	//	if(i < len) {
	//		for(int j = i+1;j < len; ++j){
	//			ST[i] = ST[j];
	//		}//endfor
	//		len--;
	//	}//
	//}//endfor
	int i = 0;
	while(i < len){
		if(ST[i].key == key){
			for(int j = i+1;j < len; ++j){
				ST[j-1] = ST[j];
			}//endfor
			len--;
			break;
		} else {
			i++;
		}
	}//endwhile
}
template <class T>
void BSTree<T>::InDisplay(BTree<T> *t){
	if(t != NULL) {
		InDisplay(t->lchild);
		cout<<t->data.key<<"   ";
		InDisplay(t->rchild);
	}//endif
}
template <class T>
void BSTree<T>::Display(){
	cout<<"Keyword is :"<<endl;
	for(int i = 0;i < len; ++i){
		cout<<ST[i].key<<" ";
	}//endfor
	cout<<endl;
}
