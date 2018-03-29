#ifndef __INTHREADING_H__ 
#define __INTHREADING_H__
#include "Base.h"
template <class T>
class InThreading:public CThread<T>{
	bool IsThreaded;
	public:
		InThreading(){IsThreaded = false;}
		void InThreadBTree();
		void InThread(BTNode<T> *p,BTNode<T> **h);
		void InThreadTraverse();
		void ShowInTree();
};
#endif
template <class T>
void InThreading<T>::InThreadBTree(){
	BTNode<T> *p,*q = NULL;
	p = this->BT;
	InThread(p,&q);
}
template <class T>
void InThreading<T>::InThread(BTNode<T> *p,BTNode<T> **h){
	//先遍历到最左下的叶子节点，使其左孩子是最初调用时传进来的q,
	//在回退时将lchild为空的域指向刚才访问过的节点即该节点的前驱(这种节点p一般是右子树，h是子树根节点或者同根节点的最左叶结点，因为中序遍历最先遍历左子树，回退时才遍历右子树的最左下结点)
	//将上次的节点的rchild指向当前访问的结点，此时p一般是h的右子树最左叶节点

	//填空链域都发生在递归回退时，由于中序遍历的顺序，当前节点的rchild为空时，使rchild指向当前节点的父节点，如果当前节点lchild为空，则其lchild指向最初遍历有子树的那个节点
	if(p) {
		InThread(p->lchild,h);
		//若上次访问节点的右指针为空，则将当前访问的结点指针赋值给其右指针，并置标志位为１
		if((*h != NULL) && ((*h)->rchild == NULL)) {
			(*h)->rchild = p;
			(*h)->rflag = 1;
		}//endif
		//若当前访问的节点的左指针为空，则将上次访问的结点赋值给当前结点的左指针域
		if(p->lchild == NULL) {
			p->lchild = (*h);
			p->lflag = 1;
		}//endif
		*h = p;
		InThread(p->rchild,h);
	}//endif
	IsThreaded = true;
}
template <class T>
void InThreading<T>::InThreadTraverse(){
	if(IsThreaded == false) {
		cout << "Please Thread first!"<<endl;
		return;
	}//endif
	if(this->BT == NULL) {
		return;
	}//endif
	cout << "Traverse InThread BTree:";
	BTNode<T> *p;
	p = this->BT;
	while(p->lflag == 0){
		p = p->lchild;
	}//endwhile
	cout << p->data <<' ';
	while(p->rchild != NULL){//向后遍历
		//如果结点有右子树就遍历右子树，没有就回退遍历根节点
		if(p->rflag == 1) {
			//rflag == 1代表p没有右子树，此时中序线索化后rchild指向的是当前节点的父节点
			p = p->rchild;
		} else {
			//如果有右子树，则向下遍历
			p = p->rchild;
			while((p->lflag == 0) && (p->lchild != NULL)){
				//找到当前节点的最左叶子节点
				p = p->lchild;
			}//endwhile
		}
		cout << p->data <<" ";
	}//endwhile
	cout << endl;
}
template <class T>
void InThreading<T>::ShowInTree(){
	//只显示被填过的节点
	if(IsThreaded == false) {
		cout << "Please Thread first!" <<endl;
		return;
	}//endif
	cout << "After InThreading BTree:"<<endl;
	BTNode<T> *p;
	if(this->BT == NULL) {
		return;
	}//endif
	p = this->BT;
	while(p->lflag == 0){
		p = p->lchild;
	}//endwhile
	if(p->lflag == 1 && p->lchild) {
		cout << "Value: " << p->data << "'s prior node is: "<< p->lchild->data <<endl;
	}//endif
	if(p->rflag == 1 && p->rchild) {
		cout << "Value: " << p->data << "'s next  node is: "<< p->rchild->data <<endl;
	}//endif
	while(p->rchild != NULL){//向后遍历
		//找到下一个结点
		if(p->rflag == 1) {
			p = p->rchild;
		} else {
			p = p->rchild;
			while((p->lflag == 0) && (p->lchild != NULL)){
				p = p->lchild;
			}//endwhile
		}

		if(p->lflag == 1 && p->lchild) {
			cout << "Value: " << p->data << "'s prior node is: "<< p->lchild->data <<endl;
		}//endif
		if(p->rflag == 1 && p->rchild) {
			cout << "Value: " << p->data << "'s next  node is: "<< p->rchild->data <<endl;
		}//endif
	}//endwhile
}
