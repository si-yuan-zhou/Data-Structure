#ifndef __PRETHREADING_H_
#define __PRETHREADING_H_
#include "Base.h"
template <typename T>
class PreThreading: public CThread<T>
{
	bool IsThreaded;//是否已经线索化
	public:
		PreThreading(){IsThreaded = false;}
		void PreThreadBTree();//生成先序线索二叉树
		void PreThread(BTNode<T> *p,BTNode<T> **h);//先序线索
		void PreThreadTraverse();//遍历先序线索二叉树
		void ShowPreTree();//显示线索化后的信息
};
#endif
template <typename T>
void PreThreading<T>::PreThreadBTree(){
	BTNode<T> *bt,*q = NULL;//生成先序线索二叉链表
	bt = this->BT;
	PreThread(bt,&q);
}
template <typename T>
void PreThreading<T>::PreThreadTraverse(){
	//线索二叉树的遍历与二叉树的遍历无异，只是二叉树是递归或者用栈来遍历，
	//线索～是借助flag判断是否有子树来决定是否遍历或停止
	if (IsThreaded == false)
	{
		cout << "Please PreThread first"<<endl;
		return;
	}
	if(this->BT == NULL)
		return;

	cout << "PreThreadTraverse: ";
	cout << this->BT->data <<" ";
	BTNode<T> *p;
	p = this->BT->lchild;//along left subtree
	while(p != NULL){
		cout << p->data << " ";
		while(p->lflag == 0){//lflag == 0代表有左子树
			p = p->lchild;
			cout << p->data << " ";
		}
		p = p->rchild;
	}
	cout << endl;
}
template <class T>
void PreThreading<T>::PreThread(BTNode<T> *bt,BTNode<T> **pre){
	/*
	   先序线索是把树中所有空指针域填上该节点的前驱和后继信息(前驱和后继信息按照遍历方式生成)
	也就是说，按照先序遍历的方式遍历每一个节点，如果当前节点的左(右)孩子不存在就应该让本应该
	指向左(右)孩子的指针域指向当前节点的前驱(后继)，这样每一个节点都还有其对应的前驱和后继的
	信息，之后在想访问一个结点的前驱和后继信息是就不用在遍历整棵树了，直接查找该节点的信息即可	*/

	/*
	 对于先序遍历，是先遍历左子树一直到最左下的节点，然后在遍历最左下边的右子树，一次向根节点回退，
	 所以在填写空链域的时候是先填写lchild == NULL的结点的前驱信息，此时指针仍需向下遍历判断是否还可以继续
	 遍历，所以此时不能填写当前节点的右空链域信息，当遍历到NULL时，开始回退遍历上一个结点的右子树，
	 对于最左下的节点来说就是curP指向NULL,Pre指向最左下的节点，此时无法继续向左遍历，递归回退到Pre的右子树
	 此时curP指向最左下的节点的右子树的根节点，Pre指向最左下的节点，所以对于最左下的节点的rchild的信息由Pre来
	 更改(Pre就是最左下的节点)
	 也就是说对于同一个节点，其前驱和后继的信息不是在同一次遍历是确定的
	 */

	//bt代表当前节点，pre代表上次访问的结点
	//pre必须是指针的指针，因为pre是形参，在参数列表中声明的没有分配空间
	//所以用pre给变量赋值时有可能会出错(段错误),
	//要想pre所指空间得到分配，必须让分配的空间的地址是指针pre的地址(用赋值实现)
	BTNode<T> *p,*q;
	if(bt != NULL) {
		p = bt->lchild;
		q = bt->rchild;

		if((*pre != NULL) && (p == NULL)) {
			//lflag == 1,lchild指向该节点的前驱
			//lflag == 0,lchild指向该节点左子树
			//若当前访问的节点的左指针为空，则将上次访问的节点赋给左指针域，幷置标志域
			bt->lchild = *pre;
			bt->lflag = 1;
		}//endif
		if((*pre != NULL) && ((*pre)->rchild == NULL)) {
			//rflag == 1,rchild指向该节点的后继
			//rflag == 1,rchild指向该节点右子树　
			//若上次访问的节点的右指针为空，
		
			(*pre)->rchild = bt;//则将访问的节点指针赋值给当前节点的右指针域
			(*pre)->rflag = 1;//幷置标志域为1
		}//endif

		*pre = bt;
		PreThread(p,pre);//访问左子树
		PreThread(q,pre);//访问右子树
	}//endif

	IsThreaded = true;
}
template <class T>
void PreThreading<T>::ShowPreTree(){
	//只显示flag为1的节点
	if(IsThreaded == false) {
		cout << "Please PreThreading" <<endl;
		return;
	}//endif
	if(this->BT == NULL) {
		return;
	}//endif

	cout << "Result after PreThreading: "<<endl;
	if(this->BT->lflag == 1) {
		cout << "Value: "<<this->BT->data <<"'s prior node is "<< this->BT->lchild->data <<endl;
	}//endif
	if(this->BT->rflag == 1) {
		cout << "Value: "<<this->BT->data <<"'s next  node is "<< this->BT->rchild->data <<endl;
	}//endif

	BTNode<T> *p;
	p = this->BT->lchild;//along left subtree
	if(p == NULL) {
		p = this->BT->rchild;
	}//endif
	while(p != NULL){
		if(p->lflag == 1) {
			cout << "Value: " <<p->data <<"'s prior node is "<< p->lchild->data <<endl;
		}//endif
		if(p->rflag == 1) {
			cout << "Value: "<<p->data <<"'s next node is "<< p->rchild->data <<endl;
		}//endif

		while(p->lflag == 0){
			p = p->lchild;

			if(p->lflag == 1) {
				cout << "Value: "<<p->data <<"'s prior node is "<< p->lchild->data <<endl;
			}//endif
			if(p->rflag == 1) {
				cout << "Value: "<<p->data <<"'s next node is "<< p->rchild->data <<endl;
			}//endif
		}//endwhile
		p = p->rchild;
	}//endwhile
}
