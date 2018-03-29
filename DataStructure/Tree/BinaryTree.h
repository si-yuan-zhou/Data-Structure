#ifndef __BinartTree_H__
#define __BinartTree_H__

template <class T>
struct BTNode{
	T data;
	BTNode *lchild;
	BTNode *rchild;
};
template <class T>
class BinaryTree
{
	BTNode<T> *BT;			//point to root node
	public:
		BinaryTree(){BT = NULL;}
		~BinaryTree(){clear(BT);}
		void ClearBTree(){clear(BT);BT = NULL;}//destory a binarytree
		void CreateBTree(T end);//create a binary tree, end is the flag of empty area
		bool IsEmpty();			//judge wheather binarytree is empty
		int BTreeDepth();		//caculate the depth of BTree
		bool RootValue(T &e);	//if BTree is not empty, e is the value of root node and return true otherwise false
		BTNode<T>* GetRoot();	//return root pointer if BTree is not empty,otherwise false
		bool Assign(T e,T value);//change value is e in BTree into value
		T GetParent(T e);			//return e's parent node
		T GetLeftChild(T e);	//get e's left child
		T GetRightChild(T e);
		T GetLeftSibling(T e);	//get the left sibling
		T GetRightSibling(T e);
		T rightsibling(BTNode<T> *p,T e);
		T leftsibling(BTNode<T> *p,T e);
		bool InsertChild(BTNode<T> *p,BTNode<T> *c,int RL);//insert
		bool DeleteChild(BTNode<T> *p,int RL);
		void PreTraBTree();		//preorder traverse BTree recursion algorithm(先序遍历递归算法)
		void InTraBTree();		//inorder traverse recursion algorithm(中序遍历递归算法)
		void PostTraBTree();	//postorder traverse recursion algorithm(后序遍历递归算法)
		void LevelTraBTree();	//traverse BTree level by level
		void PreTraBTree_N();	//previous traverse BTree non-recursion algorithm(先序遍历递归算法)
		void InTraBTree_N();	//inorder traverse non-recursion algorithm(中序遍历递归算法)
		int LeafCount();		//count the number of leaf node
		BTNode<T>* SearchNode(T e);//return a pointer point to e
		void DisplayBTreeShape(BTNode<T> *p,int level = 1);
};
#endif

template <class T>
static int clear(BTNode<T> *bt){
	/*
		Describe  : destory binary tree
		Return    : 0
		Parameters:
		 ArgName  | TypeName | Meaning
			 *bt  : BTNode<T>| the head node of BTree need to destory
	*/
	if(bt){
		clear(bt->lchild);//clear left subtree
		clear(bt->rchild);//clear right subtree
		delete bt;
	}
	return 0;
}
template <class T>
static int create(BTNode<T> *p,int k,T end) {
	/*
		Describe  : create binary subtree
		Return    : 0
		Parameters:
		 ArgName  | TypeName | Meaning
			 *p   : BTNode<T>| head node of subtree
			  k   : int      | a flag to judge create leftchild or rightchild
			end   : T        | represent empty pointer area
	*/
	BTNode<T> *q;
	T x;
	cin >> x;
	if (x != end){
		//input data in Preorder
		q = new BTNode<T>;
		q->data = x;
		q->lchild = NULL;
		q->rchild = NULL;
		if(k == 1) p->lchild = q;//q is left subtree
		if(k == 2) p->rchild = q;//q is right subtree
		create(q,1,end);//create left tree recursively
		create(q,2,end);//create right tree recursively
	}
	return 0;
}
template <class T>
void BinaryTree<T>::CreateBTree(T end){
	/*
		Describe  : create a BTree with data inputed in Preorder and end with end tag
		Return    : None
		Parameters:
		 ArgName  | TypeName | Meaning
			 end  : T        | flag of empty
	*/
	cout << "Please input data in Preorder to create a binary tree\n"
		 <<"-1 means has no subchild (e.g. leaf nodes's subchildren is -1):"<<endl;
	BTNode<T> *p;
	T x;
	cin >> x;				//input value of root node
	if (x == end) return;	//empty tree
	p = new BTNode<T>;
	if(!p){
		cout << "error" <<endl;
		exit(1);
	}
	p->data = x;
	p->lchild = NULL;
	p->rchild = NULL;
	BT = p;
	create(p,1,end);
	create(p,2,end);
}
template <class T>
bool BinaryTree<T>::IsEmpty(){
	/*
		Describe  : judge whether BTree is empty
		Return    : true if BT is NULL otherwise false
		Parameters:
		 ArgName  | TypeName | Meaning
			None  :          |
	*/
	if(BT == NULL) return true;
	return false;
}
template <class T>
static int Depth(BTNode<T> *p,int level,int &depth){
	/*
		Describe  : caculate depth of BTree and called by function BTreeDepth
		Return    : 0
		Parameters:
		 ArgName  | TypeName | Meaning
			*p 	  : BTNode<T>| root node
			level : int      | layer number of p
		   &depth : int      | record the depth of BTree which is needn't return
	*/
	if(level > depth) depth = level;				//depth is how many layers the BTree has
	if(p->lchild) Depth(p->lchild, level+1, depth);	//traverse subtree so level add one
	if(p->rchild) Depth(p->rchild, level+1, depth);
	return 0;
}
template <class T>
int BinaryTree<T>::BTreeDepth(){
	/*
		Describe  : caculate the depth of BTree recursively
		Return    : depth of BTree
		Parameters:
		 ArgName  | TypeName | Meaning
			None  :          |
	*/
	BTNode<T> *bt = BT;	//root node
	int depth = 0;
	if(bt)				//tree is not empty
		Depth(bt,1,depth);
	return depth;
}
template <class T>
bool BinaryTree<T>::RootValue(T &e){
	/*
		Describe  : return the value of rootnode 
		Return    : if BTree is not empty, return true otherwise return false
		Parameters:
		 ArgName  | TypeName | Meaning
			&e 	  : T        | value of root node
	*/
	if (BT != NULL) {	//judge whether BTree is empty
		e = BT->data;	//get rood node value
		return true;
	}
	return false;
}
template <class T>
BTNode<T>* BinaryTree<T>::GetRoot(){
	/*
		Describe  : return root node
		Return    : root node
		Parameters:
		 ArgName  | TypeName | Meaning
			None
	*/
	return BT;
}
template <class T>
bool BinaryTree<T>::Assign(T e, T value){
	/*
		Describe  : assign value to node e
		Return    : return true if operate successfully otherwise false
		Parameters:
		 ArgName  | TypeName | Meaning
			e 	  : T        | value of node needed to assign
			value : T        | value needed to be assign to e
	*/
	BTNode<T> *temp;
	temp = SearchNode(e);
	if(temp != NULL) {
		temp->data = value;
		return true;
	}
	return false;
}
template <class T>
T BinaryTree<T>::GetParent(T e){
	/*
		Describe  : acquire data of e's parent
		Return    : 0 if root node is null or e's parent node's data
		Parameters:
		 ArgName  | TypeName | Meaning
			 e 	  : T        | child node's value
	*/
	BTNode<T> *Queue[100],*p;
	int rear,front;
	rear = front = 0;
	if(BT) {
		Queue[rear++] = BT;								//Queue[0] is root node
		while (rear != front) {
			//level traverse
			//rear stores elements and front traverse Queue 
			p = Queue[front++];
			if (p->lchild && p->lchild->data == e || p->rchild && p->rchild->data == e)
				return p->data;
			else {
				if (p->lchild) Queue[rear++] = p->lchild;//store lchildnode
				if (p->rchild) Queue[rear++] = p->rchild;
			}
		}
	}
	return 0;
}
template <class T>
T BinaryTree<T>::GetRightChild(T e){
	/*
		Describe  : return root node data of e's right subtree
		Return    : 0 if p has no right child or p->rchild->data
		Parameters:
		 ArgName  | TypeName | Meaning
			e 	  : T        | node's value
	*/
	BTNode<T> *p = SearchNode(e);
	if (p->rchild) return p->rchild->data;
	cout <<"Node "<< e <<" has no right child"<<endl;
	return 0;
}
template <class T>
T BinaryTree<T>::GetLeftChild(T e){
	/*
		Describe  : return root node data of e's right subtree
		Return    : 0 if p has no left child or p->lchild->data
		Parameters:
		 ArgName  | TypeName | Meaning
			e 	  : T        | node's value
	*/
	BTNode<T> *p = SearchNode(e);
	if (p->lchild) return p->lchild->data;
	cout <<"Node "<< e <<" has no left child"<<endl;
	return 0;	
}
template <class T>
T BinaryTree<T>::GetLeftSibling(T e){
	/*
		Describe  : return left sibling's data
		Return    : 0 if BTree is empty or e's left sibling
		Parameters:
		 ArgName  | TypeName | Meaning
			e 	  : T        | node's value
	*/
	if (BT != NULL) return leftsibling(BT,e);
	else {
		cout << "empty BTree"<<endl;
		return 0;
	}
}
template <class T>
T BinaryTree<T>::leftsibling(BTNode<T> *p,T e){
	/*
		Describe  : return left sibling's data
		Return    : 0 if BTree is empty or e's left sibling
		Parameters:
		 ArgName  | TypeName | Meaning
		 	*p    | BTNode<T>| find e in subtree starting with p
			e 	  : T        | node's value
	*/
	T q;
	if (p == NULL) return 0;
	else {
		//traverse p's right subtree to find element which match e
		if (p->rchild) {
			if (p->rchild->data == e) {
				if (p->lchild)
					return p->lchild->data;
				else 
					return NULL;
			}
		}
		// traverse in left subtree since p->rchild is not exist
		q = leftsibling(p->lchild,e);
		if (q)
			return q;
		q = leftsibling(p->rchild,e);
		if (q)
			return q; 
	}
	return 0;
}
template <class T>
T  BinaryTree<T>::GetRightSibling(T e){
	/*
		Describe  : return right sibling's data
		Return    : 0 if BTree is empty or e's right sibling
		Parameters:
		 ArgName  | TypeName | Meaning
			e 	  : T        | node's value
	*/
	if (BT != NULL) return rightsibling(BT,e);
	else {
		cout << "empty BTree"<<endl;
		return 0;
	}
}
template <class T>
T BinaryTree<T>::rightsibling(BTNode<T> *p,T e){
	/*
		Describe  : return right sibling's data
		Return    : 0 if BTree is empty or e's right sibling
		Parameters:
		 ArgName  | TypeName | Meaning
		 	*p    | BTNode<T>| find e in subtree starting with p
			e 	  : T        | node's value
	*/
	BTNode<T> *q = SearchNode(e);
	BTNode<T> *pp;
	if (q) {
		pp = SearchNode(GetParent(e));
		if (pp) {
			if (pp->rchild)
				return pp->rchild->data;
			else
				return 0;
		} else
			return 0;
	}
	return 0;
}
template <class T>
bool BinaryTree<T>::InsertChild(BTNode<T> *p,BTNode<T> *c,int RL){
	/*
		Describe  : insert a child c to be p's left or right child tree and
				    the right or left partion of P become c's right child 
		Return    : true if operation has been cope otherwise false
		Parameters:
		 ArgName  | TypeName | Meaning
			*p 	  : BTNode<T>| position to be inserted
			*c 	  : BTNode<T>| new node
			RL 	  : int      | 0 insert left subtree, 1 insert right
	*/
	if (p) {
		if (RL == 0) {
			c->rchild = p->lchild;
			p->lchild = c;
		} else {
			c->rchild = p->rchild;
			p->rchild = c;
		}
		return true;
	}
	return false;
}
template <class T>
bool BinaryTree<T>::DeleteChild(BTNode<T> *p, int RL){
	/*
		Describe  : delete p's left or right subtree
		Return    : true if operation has been cope otherwise false
		Parameters:
		 ArgName  | TypeName | Meaning
			*p 	  : BTNode<T>| node
			RL 	  : int      | 0 left, 1 right
	*/
	if (p) {
		if (RL == 0) {
			clear(p->lchild);
			p->lchild = NULL;
		} else {
			clear(p->rchild);
			p->rchild = NULL;
		}
		return true;
	}
	return false;
}
template <class T>
static int PreTraverse(BTNode<T> *p){
	/*
		Describe  : preorder traverse subtree recursively
		Return    : 0
		Parameters:
		 ArgName  | TypeName | Meaning
			*p    : BTNode<T>| root node of subtree
	*/
	if (p != NULL) {
		cout << p->data <<" ";
		PreTraverse(p->lchild);
		PreTraverse(p->rchild);
	}
	return 0;
}
template <class T>
void BinaryTree<T>::PreTraBTree(){
    /*
		Describe  : preorder traverse BTree recursion algorithm(先序遍历递归算法)
		Return    : None
		Parameters:
		 ArgName  | TypeName | Meaning
			None  :
	*/
	cout << "Preorder traverse BTree:";
	BTNode<T> *p;
	p = BT;
	PreTraverse(p);
	cout << endl;
}
template <class T>
static int InTraverse(BTNode<T> *p){
	/*
		Describe  : Inorder traverse subtree recursively
		Return    : 0
		Parameters:
		 ArgName  | TypeName | Meaning
			*p    : BTNode<T>| root node of subtree
	*/
	if(p != NULL){
		InTraverse(p->lchild);
		cout <<p->data << " ";
		InTraverse(p->rchild);
	}
	return 0;
}
template <class T>
void BinaryTree<T>::InTraBTree(){
	/*
		Describe  : Inorder traverse BTree recursion algorithm(先序遍历递归算法)
		Return    : None
		Parameters:
		 ArgName  | TypeName | Meaning
			None  :
	*/
	cout << "Inorder traverse BTree:";
	BTNode<T> *p;
	p = BT;
	InTraverse(p);
	cout << endl;
}
template <class T>
static int PosTraverse(BTNode<T> *p){
    /*
		Describe  : PosTraverse subtree pointed by pointer p 
		Return    : 0
		Parameters:
		 ArgName  | TypeName | Meaning
			*p    : BTNode<T>| root node of subtree
	*/
	if (p != NULL) {
		PosTraverse(p->lchild);
		PosTraverse(p->rchild);
		cout << p->data << " ";
	}
	return 0;
}
template <class T>
void BinaryTree<T>::PostTraBTree(){
	/*
		Describe  : Postorder traverse BTree
		Return    : None
		Parameters:
		 ArgName  | TypeName | Meaning
			None  :
	*/
	cout << "PosTraverse BTree:";
	BTNode<T> *p;
	p = BT;
	PosTraverse(p);
	cout << endl;
}
template <class T>
void BinaryTree<T>::PreTraBTree_N(){
    /*
		Describe  : Preorder traverse BTree unrecursively
		Return    : None
		Parameters:
		 ArgName  | TypeName | Meaning
			None  :
	*/
	cout << "Preorder traverse BTree(not recursive)";
	BTNode<T> *Stack[200];
	int top = 0;
	BTNode<T> *p = BT;
	while (p || top) {
		//outside traverse the rest right children
		while (p) {
			/*
				inside while store rightchild and traverse leftchild continueously
			*/
			cout << p->data << " ";
			Stack[top++] = p->rchild;
			p = p->lchild;
		}
		if (top != 0) {
			p = Stack[--top];
		}
	}
}
template <class T>
void BinaryTree<T>::InTraBTree_N(){
    /*
		Describe  : Inorder traverse BTree unrecursively
		Return    : None
		Parameters:
		 ArgName  | TypeName | Meaning
			None  :
	*/
	cout << "Inorder traverse BTree(not recursive)";
	int top = 0;
	BTNode<T> *Stack[200];
	BTNode<T> *p = BT;
	while (p || top){
		while (p) {
			Stack[top++] = p;
			p = p->lchild;
		}
		if(top){
			p = Stack[--top];
			cout << p->data;
			p = p->rchild;
		}
	}
}
template <class T>
void BinaryTree<T>::LevelTraBTree(){
    /*
		Describe  : traverse BTree level by level by using Queue
		Return    : None
		Parameters:
		 ArgName  | TypeName | Meaning
			None  :
	*/
	BTNode<T> *Queue[100],*b;
	int front, rear;
	front = rear = 0;
	if(BT){
		Queue[rear++] = BT;
		while(front != rear) {
			b = Queue[front++];
			if (b)
				cout << b->data <<" ";
			if (b->lchild)
				Queue[rear++] = b->lchild;
			if (b->rchild)
				Queue[rear++] = b->rchild;
		}
	}
}
template <class T>
static int Leaf(BTNode<T> *p,int &count){
	/*
		Describe  : caculate the number of leaf of subtree pointed by p
		Return    : count of leaves
		Parameters:
		 ArgName  | TypeName | Meaning
			*p    : BTNode<T>| pointer which points to root node of subtree
			count : int      |static variable, the number of leaves
	*/
//	static int count = 0;
	if (p) {
		if (p->lchild == NULL && p->rchild == NULL)
			++count;
		Leaf(p->lchild,count);
		Leaf(p->rchild,count);
	}
	return count;
}
template <class T>
int BinaryTree<T>::LeafCount(){
	/*
		Describe  : caculate how many leaves are there
		Return    : None
		Parameters:
		 ArgName  | TypeName | Meaning
			None  :
	*/
	int count = 0;
	return Leaf(BT,count);
}
template <class T>
static BTNode<T>* search(BTNode<T> *bn,T e){
	/*
		Describe  : same meaning with function SerachNode
		Return    : pointer point to node that we searche
		Parameters:
		 ArgName  | TypeName | Meaning
			 *bn  : BTNode<T>| root node of subtree
			  e   : T        | value which need to search
	*/
	BTNode<T> *t;
	if(bn){
		if(bn->data == e) return bn;
		t = search(bn->lchild,e);//find in right subtree
		if (t) return t;
		t = search(bn->rchild,e);
		if (t) return t;
	}
	return NULL;
}
template <class T>
BTNode<T>* BinaryTree<T>::SearchNode(T e){
	/*
		Describe  : find a node whose value is e
		Return    : pointer point to node that we searche
		Parameters:
		 ArgName  | TypeName | Meaning
			e     : T        | value of node needed to be finded
	*/
	BTNode<T> *t;
	if(BT){
		if(BT->data == e) return BT;
		t = search(BT->lchild,e);//find in right subtree
		if (t) return t;
		t = search(BT->rchild,e);
		if (t) return t;
	}
	return NULL;
}
template <class T>
void BinaryTree<T>::DisplayBTreeShape(BTNode<T> *bt,int level){
	/*
		Describe  : turn 90 degree to left and display tree-shape algorithm
		Return    : None
		Parameters:
		 ArgName  | TypeName | Meaning
			*bt   : BTNode<T>| root of subtree
			level : int      | bt's layer number
	*/
	if(bt){
		DisplayBTreeShape(bt->rchild,level+1);//每向回归约一次就少一层，所以需要回车
		cout << endl;
		for (int i = 1; i < level; ++i)
			cout <<'\t';//print bt's level-1 columns
		cout << bt->data;
		DisplayBTreeShape(bt->lchild,level+1);
	}
}
