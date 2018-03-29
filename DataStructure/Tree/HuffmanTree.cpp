//结点的带权路径长度为：从根结点到该结点之间的路径长度与该结点的权的乘积。
//树的带权路径长度规定为所有叶子结点的带权路径长度之和
#include <iostream>
#include <iomanip>
using namespace std;

template <class T>
struct HufNode{
	T weight;
	int prt;//指向父节点的指针域
	int lch;//左指针域
	int rch;//右指针域
};
template <class T>
class HuffmanTree {
	int ln;				//count of leaves
	HufNode<T> *BT;		//最优二叉树顺序存储空间的首地址
	public:
		HuffmanTree(){BT = NULL;}
		void createHuffmanTree(int n,T w[]);
		void select(HufNode<T>*p,int k,int *i,int *j);
		void PrintHuffmanTree();
};
template <class T>
void HuffmanTree<T>::createHuffmanTree(int n,T w[]){
/*
	Describe: Create a Huffman Tree
	Result: None
	Parameters: TypeName: Meaning
			n : int     : count of leaves
			w : T[]     | array stored leaves' weight 
*/
	//n is count of leaves and w is leaf's weight
	HufNode<T> *p;
	int k,i,j,m;
	ln = n;
	m = n*2 - 1;//整个树的结点数
	BT = new HufNode<T>[m];
	p = BT;

	//initialize
	for(k = 0;k < m; ++k){
		//因为所有节点存放在数组中，所以-1代表空指针
		//初始化所有节点的指针域(目前所有结点没有值)
		(p+k)->prt = -1;
		(p+k)->lch = -1;
		(p+k)->rch = -1;
	}//endfor

	//initialize leaves node's weight
	for(k = 0;k < n;++k){
		//只有前n-1个节点有权值
		(p+k)->weight = w[k];
	}

	//initialize the whole tree
	for(k = n;k < m;++k){
		//初始化剩下的结点(没有权值的结点),将找到的最小两结点连接成子树(其父节点不在为空)
		select(p,k,&i,&j);
		//select在当前剩余的孤立叶子结点中找到最小的结点i,j
		(p+i)->prt = k;
		(p+j)->prt = k;
		(p+k)->lch = i;
		(p+k)->rch = j;
		(p+k)->weight = (p+i)->weight + (p+j)->weight;
	}
}
template <class T>
void HuffmanTree<T>::select(HufNode<T> *p,int k,int *i,int *j){
/*
	Describe: 在前k-1个节点中找到权值最小的两个孤立结点i,j,如果没找到，i,j不变
	Result:   None
	Parameters: TypeName: Meaning
		   *p : HufNode | 存放结点数组的首地址
		    k : int     | 在前k-1个范围内找
			*i: int     | 最小的结点
			*j: int 　　| 次小的结点
*/
	//前k-1个结点中选择权值最小的两个根节点i,j
	T w;
	int n = 0;

	//找到权值最小的i
	while(n < k && (p+n)->prt != -1){
		//寻找父节点为空的结点，即仍然孤立的叶子结点
		//该段代码只是找到了前k-1个结点中第一个孤立的叶子结点
		n++;
	}
	w = (p+n)->weight;
	*i = n;

	while(n < k){
		//在找到的孤立叶子结点中找权值最小的结点
		if((((p+n)->weight) < w) && ((p+n)->prt == -1)) {
			*i = n;
			w = (p+n)->weight;
		}//endif
		n++;
	}//endwhile

	//找到权值最小的j(除i外)
	n = 0;
	while((n < k) && ((p+n)->prt != -1) || (n == (*i))){
		//n从０开始，在前k-1个结点中找到（除之前找到的i）孤立的叶子结点
		n++;
	}
	w = (p+n)->weight;
	*j = n;
	while(n < k){
		if(((p+n)->weight < w) && (n != (*i)) && ((p+n)->prt == -1)) {
			//在k-1个结点中找到权值最小且不为i的值
			*j = n;
			w = (p+n)->weight;
		}//endif
		n++;
	}//endwhile

	if((*i) > (*j)) {
		n = (*i);
		*i = *j;
		*j = n;
	}//endif
}
template <class T>
void HuffmanTree<T>::PrintHuffmanTree(){
	HufNode<T> *p;
	p = BT;
	cout << "k" << setw(10) <<"WEIGHT"<<setw(10)<<"PARENT"<<setw(10)<<"LEFTCHILD"<<setw(10)<<"RIGHTCHILD"<<endl;
	for(int k = 0;k < 2*ln-1; ++k){
		cout << k << setw(10) << (p+k)->weight << setw(10) << (p+k)->prt <<setw(10) <<(p+k)->lch << setw(10) << (p+k)->rch <<endl;
	}//endfor
}

int main(int argc, char* argv[]){
	int *w,op;
	HuffmanTree<int> b;
	do{
		cout <<"1-Input weight"<<endl;
		cout <<"2-Generate optimal BTree"<<endl;
		cout <<"3-Exit"<<endl;
		cout <<"Please choose:[ ]";
		cout <<"\b\b";
		cin  >>op;
		switch(op){
			case 1:
				cout <<"Please input count of nodes:";
				int sum;
				cin >> sum;
				w = new int[sum];
				cout <<"Please input weight successively:"<<endl;
				for(int i = 0;i < sum; ++i){
					cout << "Please input weight of number "<<i+1<<": ";
					cin  >>w[i];
				}//endfor
				break;
			case 2:
				b.createHuffmanTree(sum,w);
				b.PrintHuffmanTree();
				break;
			case 3:
				cout <<"Bye-bye"<<endl;
				break;
		}//endswitch
	}while(op != 3);
	return 0;
}
