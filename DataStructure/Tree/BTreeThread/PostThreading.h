//后序线索二叉树采用三叉链表存储结构
#ifndef __POSTTHREADING_H__
#define __POSTTHREADING_H__
template <class T>
struct TTTNode{
	T data;
	int lflag;
	int rflag;
	TTTNode<T> *pre;
	TTTNode<T> *lchild;
	TTTNode<T> *rchild;
};
template <class T>
class PostThreadBTree {
	TTTNode<T> * BT;					//三叉链表根节点指针
	public:
		PostThreadBTree(){BT = NULL;}	
		void CreateBTree(T end);		//创建三叉链表
		void PostThreading();		//线索化三叉链表
		void TraverseTree();			//遍历后序线索三叉链表
};
#endif
template <class T>
static int create(TTTNode<T> *p,int k,T end){
	//根据k的值将新创建的Q添加在p后面，然后创建Q的子树
	TTTNode<T> *Q;//三叉链表节点
	T x;
	cin >> x;
	if(x != end) {
		Q = new TTTNode<T>;
		Q->data = x;
		Q->lchild = NULL;
		Q->rchild = NULL;
		Q->lflag  = 0;
		Q->rflag  = 0;
		Q->pre = p;

		if(k == 1) p->lchild = Q;
		if(k == 2) p->rchild = Q;

		create(Q,1,end);
		create(Q,2,end);
	}//endif
	return 0;
}
template <class T>
void PostThreadBTree<T>::CreateBTree(T end){
	TTTNode<T> *p;
	T x;
	cin >> x;
	if(x == end) {
		return;
	}//endif
	p = new TTTNode<T>;
	p->data = x;
	p->pre = NULL;
	p->lchild = NULL;
	p->rchild = NULL;
	p->lflag  = 0;
	p->rflag  = 0;
	BT = p;

	create(p,1,end);
	create(p,2,end);
}
template <class T>
static int Thread(TTTNode<T>*p,TTTNode<T>**h){
	//h一般是p的右兄弟或者左孩子，h在函数调用是值为null,
	//填空链域是从深度最深的右叶结点或左叶结点(此时没有右叶结点)
	if(p) {
		Thread(p->lchild,h);
		Thread(p->rchild,h);
		//若上次访问的结点右指针为空，则将当前访问的结点序号填入，并置右标志域为１
		if(*h != NULL && (*h)->rchild == NULL) {
			(*h)->rchild = p;
			(*h)->rflag  = 1;
		}//endif
		//若上次访问的结点左指针为空，则将当前访问的结点序号填入，并置左标志域为１
		if(*h != NULL && p->lchild == NULL) {
			p->lchild = (*h);
			p->lflag  = 1;
		}//endif
		*h = p;//记住当前访问的结点
	}//endif
	return 0;
}
template <class T>
void PostThreadBTree<T>::PostThreading(){
	TTTNode<T> *p = BT,*q = NULL;
	Thread(p,&q);
}
template <class T>
void PostThreadBTree<T>::TraverseTree(){
	//按照后序显示左右结点
	TTTNode<T> *p,*h;
	if(BT == NULL) return;
	h = BT;
	while(h->lchild != NULL || h->rflag == 0 && h->rchild != NULL){
		//找到整棵树的最左叶节点
		//如果左孩子存在则指向左子树，如果有右子树且不为空则指向右子树
		if (h->lchild != NULL) {
			h = h->lchild;
		} else {
			h = h->rchild;
		}
	}//endwhile
	//按后序遍历找第一个结点
	cout << h->data << "->";
	while(h->pre != NULL){//h->pre == NULL的只有根节点,后序遍历最后一个是根节点
		if(h->rflag != 0) {//没有右子树就指向线索化后的下一个结点
			h = h->rchild;
		} else {
			p = h->pre;
			if ((p->rchild == h)||(p->lchild == h) && ((p->rflag != 0) || (p->rchild == NULL))) {
				//对于没有空域的结点，如果当前结点是其前驱结点的右子树则直接是工作指针h指向其前驱结点
				//如果当前结点是其前驱结点的左孩子，且前驱结点没有右子树～(如果有右子树则找右子树的最左叶结点)
				//或者前驱结点不存在～
				h = p;
			} else {
				//在右子树中找下一个结点
				h = p->rchild;
				while(((h->lflag == 0) && (h->lchild != NULL)) || ((h->rflag == 0) && (h->rchild != NULL))){
					//只要当前结点有左右子树就向下遍历
					if ((h->lflag == 0) && (h->lchild != NULL)) {
						//遍历左子树
						h = h->lchild;
					} else {
						h = h->rchild;
					}
				}//endwhile
			}
		}
		cout << h->data <<"->";
	}//endwhile
	cout << "NULL" <<endl;
}
