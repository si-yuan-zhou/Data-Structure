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
		Node<T> *ST;
		int len;
		BTree<T> *t;	//root pointer
		BTree<T> *f;	//root's father node pointer
		BTree<T> *p;	//point to the last element in find_path
		
		BSTree();
		~BSTree();
		void SearchBST(BTree<T> *t,T key);	//binary sorted tree search
		void InsertBST(BTree<T> *(&t),Node<T> e);
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
		if (key == t->data.key) {
			cout<<key<<" has been gotten!"<<endl;
		} else {
			cout<<"Not find"<<endl;
		}
	} else if(key < t->data.key){
		SearchBST(t->lchild,key);
	} else {
		SearchBST(t->rchild,key);
	}
}
template <class T>
void BSTree<T>::InsertBST(BTree<T> *(&t),Node<T> e){
	ST[len] = e;
	len++;
	p = t;
	while(p){
		if(p->data.key == e.key) {
			cout<<e.key<<" has exited"<<endl;
		}//endif
		f = p;
		if (e.key < p->data.key) {
			p = p->lchild;
		} else {
			p = p->rchild;
		}
		p = new BTree<T>;
		p->data = e;
		p->lchild = p->rchild = NULL;
		if (t == NULL) {
			t = p;
		} else {
			if (e.key < f->data.key) {
				f->lchild = p;
			} else {
				f->rchild = p;
			}
		}
	}//endwhile
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
	BTree<T> *q,*s;
	if (!p->rchild) {		//has no rightSubTree
		q = p;
		p = p->lchild;
		delete q;
	} else if(!p->lchild){	//has no leftSubTree
		q = p;
		p = p->rchild;
		delete q;
	} else {
		q = p;
		s = p->lchild;
		while(s->rchild){
			q = s;
			s = s->rchild;
		}//endwhile
		p->data = s->data;
		if (q != p) {
			q->rchild = s->lchild;
		} else {
			q->lchild = s->lchild;
		}
		delete s;
	}
	return 1;//true
}
template <class T>
void BSTree<T>::DeleteElem(T key){
	//delete StaticChart element
	for(int i = 0;i < len && ST[i].key != key; ++i){
		if(i < len) {
			for(int j = i+1;j < len; ++j){
				ST[i] = ST[j];
			}//endfor
			len--;
		}//
	}//endfor
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
