#ifndef __Tree_H__
#define __Tree_H__
#include "../Queue/LinkQueue.h"
#include <cstring> 
#include <cstdio> 
#define MAX_TREE_SIZE 20

template <typename T>
struct PTNode {
	T data;
	int parent;						//postion of parent
};
template <typename T>
struct PTree {
	PTNode<T> nodes[MAX_TREE_SIZE];	//nodes array
	int n;							//nodes count
};
//队列中的元素数据类型
template <class T>
struct QElemType{
	int num;
	T name;
	//char name;
};
template <typename T>
class CTree
{
	PTree<T> Tree;					//One has n nodes be consisited of a data area and parent's place and count area recording nodes' count 
public:
	CTree(){Tree.n = 0;};
	bool CreateTree(T end);			//Create a tree
	void ClearTree();				//Clear a tree
	bool IsEmpty();					//Judge a tree whether is empty
	int TreeDepth();				//Return tree's depth
	T Root();						//Return tree root
	T Value(int i);					//Return value of node and i is order number
	bool Assign(T e,T value);		//Change e to value
	T parent(T e);					//Return e's parent
	T LeftChild(T e);   			//Return non-leaf node's most left child's value
	T RightSibling(T e);			//Return right sibling's value if e has right sibling
	void Print();					//Print tree
	bool InsertChild(T p,int i,PTree<T> c);
	void DeleteChild(T p,int i);
	void TraverseTree();
	PTree<T> GetTree(){return Tree;}
};
#endif	
template <typename T>
bool CTree<T>::CreateTree(T end) {
	/*
		Describe  : Create A tree that a node has n subnodes
		Return    : true
		Parameters:
		 ArgName  | TypeName | Meaning
			 end  : T        | symnol of end
	*/
	LinkQueue<QElemType<T> > Q;
	QElemType<T> p, q;
	int i = 0, j, len;
	T c[MAX_TREE_SIZE];				//Store child nodes temporarily
	
	cout << "Please input root node: "; 
	cin  >> Tree.nodes[0].data;		//Root node's order number is 0

	if (Tree.nodes[0].data != end){
		Tree.nodes[0].parent = -1;	//Root has no parent
		q.name = Tree.nodes[0].data;
		q.num = 0;					//Order number
		i++;
		Q.EnQueue(q);				//Root node enter queue
		
		while(i < MAX_TREE_SIZE && Q.QueueEmpty() != 1){ //Array is not full and Queue is not empty
			q = Q.DeQueue();
			cout << "Please input node " << q.name << "'s all children without space:(if has no child input "<<end<<")";
			//T just can be char or input 0~9,without space
			//Please remember to optimize and c can not only be regard as string or char*
			cin >> c;
			len = strlen(c);
			
			if (c[0] == end)
				continue;
			for(j = 0; j < len; ++j) {
				//store all nodes in c as q's all subchildren

				//store in tree
				Tree.nodes[i].data = c[j];
				Tree.nodes[i].parent = q.num;
				//store in queue
				p.name = c[j];
				p.num = i;
				Q.EnQueue(p);		//put current node's all children into queue successively
				i++;				//i's size represent the count of the whole tree's nodes
			}
		}
		if (i > MAX_TREE_SIZE) {
			cout << "Overflow!" <<endl;
			exit(-1);
		}
		Tree.n = i;					//Maybe a part of nodes would not be stored
	} else {						//Tree is empty
		Tree.n = 0;
	}
	return true;
}
template <class T>
void CTree<T>::ClearTree(){
	/*
		Describe  : set Tree's node count as 0
		Return    : None
		Parameters:
		 ArgName  | TypeName | Meaning
			  None
	*/
	Tree.n = 0;
}
template <class T>
bool CTree<T>::IsEmpty(){
	/*
		Describe  : Judge whether Tree is empty
		Return    : true if tree is empty or false otherwise
		Parameters:
		 ArgName  | TypeName | Meaning
			 None
	*/
	if (Tree.n == 0) {
		return true;
	} else {
		return false;
	}
}
template <class T>
int CTree<T>::TreeDepth(){
	/*
		Describe  : Traverse all nodes upward to root and get the largest path
		Return    : depth
		Parameters:
		 ArgName  | TypeName | Meaning
			 None
	*/
	int k,m,def,max = 0;
	for(k = 0;k < Tree.n; ++k){
		def = 1;
		m = Tree.nodes[k].parent;
		while(m != -1){
			m = Tree.nodes[m].parent;//find root node along parent node
			def++;
		}
		if (max < def) {
			max = def;
		}
	}
	return max;
}
template <class T>
T CTree<T>::Root(){
	/*
		Describe  : Get root node value
		Return    : node's data
		Parameters:
		 ArgName  | TypeName | Meaning
			 None
	*/
	if (Tree.n == 0) {
		return 0;
	} else {
		return Tree.nodes[0].data;
	}
}
template <class T>
T CTree<T>::Value(int i){
	/*
		Describe  : get the value of number i node
		Return    : node's value
		Parameters:
		 ArgName  | TypeName | Meaning
			 i    : int      | position
	*/
	if (i < Tree.n) {
		return Tree.nodes[i].data;
	} else {
		return 0;
	}
}
template <class T>
bool CTree<T>::Assign(T cur_e,T value){
	/*
		Describe  : find node whose value is cur_e and change it to value
		Return    : true if operate successfully or false if tree is empty
		Parameters:
		 ArgName  | TypeName | Meaning
		   cur_e  : T        | value of node needed to be changed
		   value  : T        | new value
	*/
	if (Tree.n == 0) return false;
	for(int i = 0;i <Tree.n ; ++i){
		if (Tree.nodes[i].data == cur_e) {
			Tree.nodes[i].data = value;
			return true;
		}
	}
	return false;
}
template <class T>
T CTree<T>::parent(T cur_e){
	/*
		Describe  : find parent node of node whose value is cur_e
		Return    : parent node's value
		Parameters:
		 ArgName  | TypeName | Meaning
		   cur_e  : T        | value of node needed to find
	*/
	for(int i = 0;i < Tree.n; ++i){
		if (Tree.nodes[i].data == cur_e) 
			return Tree.nodes[Tree.nodes[i].parent].data;	
	}
	return 0;
}
template <class T>
T CTree<T>::LeftChild(T cur_e){
	/*
		Describe  : find far left child node whose parent node's value is cur_e.
					Find parent node according child node whose parent's value is cur_e 
		Return    : data
		Parameters:
		 ArgName  | TypeName | Meaning
			cur_e : T        | parent's value
	*/
	for(int i = 0;i < Tree.n; ++i){
		if (Tree.nodes[Tree.nodes[i].parent].data == cur_e)
			return Tree.nodes[i].data;
	}
	return 0;
}
template <class T>
T CTree<T>::RightSibling(T cur_e){
	/*
		Describe  : find a node's rightsibling
		Return    : data
		Parameters:
		 ArgName  | TypeName | Meaning
			cur_e : T        | value
	*/
	for(int i = 0;i < Tree.n; ++i){
		if (Tree.nodes[i].data == cur_e) {
			//find no node matched before finding cur_e
			break;
		}
		if (Tree.nodes[i].parent == Tree.nodes[i+1].parent) {
			//all nodes are stored in level order and from left to right
			//so just find a node has same parent with its next node
			return Tree.nodes[i+1].data;
		}
	}
	return 0;
}
template <class T>
void CTree<T>::Print(){
	/*
		Describe  : print vlaue of number i and correponding parent
		Return    : none
		Parameters:
		 ArgName  | TypeName | Meaning
			none
	*/
	cout << "Node count is :" << Tree.n <<endl;
	cout << "Nodes\tParents"  <<endl;
	for(int i = 0;i < Tree.n; ++i){
		cout << Value(i) <<'\t';
		if (Tree.nodes[i].parent >= 0) {
			cout << Value(Tree.nodes[i].parent) <<" ";
		}
		cout << endl;
	}
}
template <class T>
bool CTree<T>::InsertChild(T p,int i,PTree<T> c){
	/*
		Describe  : inset c into position i
		Return    : true if operate successfully or false otherwise
		Parameters:
		 ArgName  | TypeName | Meaning
			   p  : T        | value of parent node of position which is to be inserted
			   i  : int      | insert Position
			   c  : PTNode<T>| subtree need to be inserted
	*/
	int j,k,len,f = 1,n = 0;
	PTNode<T> t;
	if (IsEmpty() != true) {//tree is not empty
		for(j = 0;j < Tree.n; ++j){
			if (Tree.nodes[j].data == p) {
				break;//j is p's position
			} 
		}
		len = j+1;
		if (i > 1) {
			for(k = j+1;k < Tree.n; ++k){
				//在剩下的节点中找到父节点位置为j的所有节点并判断位置是否在i前
				if (Tree.nodes[k].parent == j) {
					n++;
					if(n == i-1) {
						//找到插入位置的前一个位置
						break;
					}//endif
				}
			}
			len = k + 1;
			//len may be MAX_TREE_SIZE or the position to be inserted
		}	
		if(len < Tree.n) {
			//position to be insterted has been found
			for(k = Tree.n - 1;k >= len; --k){
				//put back Tree's number len to last node c.n steps
				Tree.nodes[k+c.n] = Tree.nodes[k];
				if(Tree.nodes[k].parent >= len) {
					//Tree.nodes[k] is subtree of node in insertPostion place
					//在位置len 之后的节点都要向后移动c.n次，下面的语句只是改变了当前节点的parent属性
					//并没有改变父节点的位置，而父节点的位置的改变由上面的复制语句来执行
					Tree.nodes[k+c.n].parent += c.n;
				}//endif
			}//endfor
		}//endif
		for(k = 0;k < c.n; ++k){
			//将c树插入位置len后
			Tree.nodes[len+k].data = c.nodes[k].data;
			//由于ｃ树的根节点插在len处所以其所有子节点的parent属性都加len
			Tree.nodes[len+k].parent = c.nodes[k].parent + len;
		}//endfor
		//设置ｃ树的根节点的parent属性为j即要插入位置的父节点的位置
		Tree.nodes[len].parent = j;
		//改变树的节点数
		Tree.n += c.n;
		while(f){
			//将节点仍按层排序，因为获取的len使插入的位置可能是父节点p的子节点或者p的下一个位置
			//所以需要重新排序
			f = 0;
			for(j = len;j < Tree.n-1; ++j){
				//在改动的这部分节点中排序
				if(Tree.nodes[j].parent > Tree.nodes[j+1].parent) {
					//节点j与节点j+1的父节点的在按层排序中只可能是相同或Pj < Pj+1
					t = Tree.nodes[j];
					//把位置错误（未排序）的节点获取到然后交换位置
					Tree.nodes[j] = Tree.nodes[j+1];
					Tree.nodes[j+1] = t;
					f = 1;
					for(k = j;k < Tree.n; ++k){
						if(Tree.nodes[k].parent == j) {
							//由于j节点已经交换过，所以把父节点为j的节点的parent属性都加１，j+1节点的子节点的parent属性减一
							Tree.nodes[k].parent++;
						} else if(Tree.nodes[k].parent == j+1) {
							Tree.nodes[k].parent--;
						}//endif
					}//endfor
				}//endif
			}//endfor
		}//endwhile
		return true;
	}else{
		return false;
	}
}
int deleted[MAX_TREE_SIZE+1];
template <typename T>
void CTree<T>::DeleteChild(T p,int i) {
/*
	Describe: delete subtree whose parent node is p and position is i 
	Result: None
	Parameters: TypeName: Meaning
		    p : T       : parent node of position to be delete
			i : int     : order of root node of subtree to be deleted
*/
	//initial contation: tree exist, p is the node of tree,1<=i<=p degree of nodes
	//Consequence: delete the ith subtree of p
	int j,k,n = 0;
	LinkQueue<QElemType<T> > q;
	QElemType<T> pq,qq;
	//initilize deleted array
	for(j = 0;j < Tree.n;++j){
		deleted[j] = 0;
	}
	pq.name = 'a';//a表示次节点不可用
	for(j = 0;j < Tree.n; ++j){
		if(Tree.nodes[j].data == p)
			//j is p's position
			break;
	}
	for(k = j+1;k < Tree.n;++k){
		if(Tree.nodes[k].parent == j){
			n++;
			if(n == i)
				break;
		}
		//k 是p的第ｉ个子树的序号
	}
	//将要删除的节点设置为１
	if(k < Tree.n){
		n = 0;
		pq.num = k;
		deleted[k] = 1;
		//n代表队列q中的元素个数
		n++;
		//将删除的节点入队
		q.EnQueue(pq);
		while(!q.QueueEmpty()){
			qq = q.DeQueue();
			for(j = qq.num+1; j < Tree.n;++j){
				//在删除节点的后面查找该节点的所有子树
				if(Tree.nodes[j].parent == qq.num){
					pq.num = j;
					deleted[j] = 1;//1表示删除
					n++;
					q.EnQueue(pq);
				}
			}
		}
	}
	for(j = 0;j < Tree.n;++j){
		if(deleted[j] == 1){
			for(k = j+1;k <= Tree.n;++k){
				//将k之后的节点向前移一位覆盖节点k
				deleted[k-1] = deleted[k];
				Tree.nodes[k-1] = Tree.nodes[k];
				
				//按层排序
				//由于deleted数组中的节点都是要删除的节点所以可以直接用后面覆盖前面的
				//由于deleted已经删除了，所以Tree中的节点也要对应删除，此时可能造成树的结构关系变化
				//节点Tree.nodes[k]把节点Tree.nodes[k-1]覆盖点但对应两个节点的父节点不一定相同
				//Tree.nodes[k].parent > j 表示删除后节点换层（第i层第一个节点换到i-1层最后一个节点）
				if(Tree.nodes[k].parent > j)
					Tree.nodes[k-1].parent--;
			}
			//j--因为deleted已经删除了一个节点
			j--;
	    }
		Tree.n -= n;//n为待删除节点数
	}
}
template <typename T>
void CTree<T>::TraverseTree(){
	/*
		Describe  : level Traverse for all nodes are stored in level order
		Return    : none
		Parameters:
		 ArgName  | TypeName | Meaning
			 none
	*/
	cout << "Level Traverse: " << endl;
	for (int i = 0; i < Tree.n; ++i)
	{
		cout << Tree.nodes[i].data << "->";
	}
}
