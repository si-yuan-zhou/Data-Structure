#ifndef __SELECTSORT__
#define __SELECTSORT__
#include "DataDefinition.h"

//简单选择排序
template <class T>
int SelectMinKey(SqList<T> &L,int n){
	//选择最小数，从n开始
	int min = n;
	T minkey;
	minkey = L.key[n];
	for(int i = n+1;i <= L.length; ++i){
		if(L.key[i] < minkey) {
			minkey = L.key[i];	//get minimum value
			min = i;			//get minimum position
		}//endif
	}//endfor
	return min;
}

template <class T>
void SelectSort(SqList<T> &L){
	int j;
	T t;
	for(int i = 1;i <= L.length; ++i){
		j = SelectMinKey(L,i);
		//在L.key[i]~L.key[L.length]中选择最小的记录并将其地址赋值给j
		if(i != j) {
			t = L.key[i];
			L.key[i] = L.key[j];
			L.key[j] = t;
		}//endif
	}//endfor
}

//树形选择排序
template <class T>
void ChangeTree(TreeNode<T> *tree,int i){

	if (i % 2 == 0) {
		tree[(i-1)/2] = tree[i-1];	//当i为偶数时把左结点赋给父节点
	} else {
		tree[(i-1)/2] = tree[i+1];	//当i为奇数时把右结点比较父结点
	}

	int j;
	i = (i-1)/2;					//i指向已排序结点的父结点
	while(i){
		if (i % 2 == 0) {
			//i 是偶数代表i指向右孩子，所以j指向其前一个
			j = i - 1;
		} else {
			j = i + 1;
		}

		if (!tree[i].active || !tree[j].active) {
			//两个同级兄弟结点中有一个是可比较(未排序的)

			//tree[i]未排序
			if (tree[i].active) {
				//把tree[i]赋给其父结点
				tree[(i-1)/2] = tree[i];
			} else {
				tree[(i-1)/2] = tree[j];
			}
		} else {
			//两个结点都已有序，按照值的大小将小的赋给父结点
			if (tree[i].data < tree[j].data) {
				tree[(i-1)/2] = tree[i];
			} else {
				tree[(i-1)/2] = tree[j];
			}
		}
		i = (i-1)/2;//i指向上一层，这里只调整参数i位置所在的子树
	}//endwhile
}

int Power(int n){
	//计算2的n次方
	int result = 1;
	if (n >= 1) {
		for(int i = 1;i <= n; ++i){
			result *= 2;
		}//endfor
		return result;
	} else {
		return 1;
	}
}

int LeapNum(int n){
	//满二叉树的叶子结点总数(>=n)
	for(int i = 1;i < 100; ++i){
		//Power(i-1)是第i行结点的数量
		if (Power(i-1) < n && n < Power(i)) {
			//n大于i层的数量小于i+1层的结点数，返回结点数最大的层
			return Power(i);
		} else if(Power(i-1) == n){
			//返回结点等于n的层的结点数
			return Power(i-1);
		}
	}//endfor
}

template <class T>
void TreeSort(T a[],int n){

	int bottomSize = LeapNum(n);		//树底层结点个数，此处必须满足满二叉树
	int size = 2*bottomSize - 1;		//树中结点总数
	int externalIndex = bottomSize - 1;	//开始比较的结点位置,一共有externalIndex个内部结点

	TreeNode<T> *tree;
	tree = new TreeNode<T>[size];
	int i,j = 0;

	//将待排序结点放在树的后n个节点中
	//tree[]的后n个位置存放a[]的元素值
	for(i = externalIndex;i < size; ++i){
		tree[i].index = i;
		if (j < n) {//共有n个数
			tree[i].active = 1;
			tree[i].data = a[j++];
		} else {
			//将结点tree[i]赋值为无穷大，即已经比较过了
			tree[i].active = 0;
		}
	}//endfor

	//比较找到最小结点
	i = externalIndex;
	while(i){
		j = i;
		while(j < 2*i){
			//2*i is the last node in this layer, while statement traverse the whole layer
			
			if(!tree[j+1].active || tree[j].data <= tree[j+1].data) {
				//当前结点小于其右兄弟或者其右兄弟不必在比较

				if(!tree[j+1].active && !tree[j].active) {
					//tree[(j-1/2)] is the parent of tree[j] 

					tree[(j-1)/2].active = 0;	//这两个结点不用比较了
				}//endif
				tree[(j-1)/2] = tree[j];		//较小结点(leftNode)赋值给其双亲结点,结点包括index,data and active
			} else {
				tree[(j-1)/2] = tree[j+1];		//rightNode assign to parentNode
			}

			//每次比较两个结点
			j += 2;
		}//endwhile
		i = (i-1)/2;							//i point to the first element in parent layer
	}//整个树已经建立完成，根节点是最小的结点

	for(i = 0;i < n-1; ++i){			//处理前n-1个结点
		a[i] = tree[0].data;
		tree[tree[0].index].active = 0;	//树中子节点第tree[0].index不再参加比较
		ChangeTree(tree,tree[0].index);	//修改树结构
	}//endfor
	a[n-1] = tree[0].data;				//处理数值最大的结点
}

//堆排序
template <class T>
void HeapAdjust(SqList<T> &L,int s,int m){
	//对顺序表做查找，从值最大的孩子结点向下筛选，找到最大值
	//每次只对一个元素rc进行操作，使其所在子树满足堆的定义
	//把s到m的元素进行调整

	T rc = L.key[s];
	for(int j = 2*s;j <= m;j *= 2){
		//2*s是L.key[s]的左子结点，每次乘2就找到左孩子的左孩子

		//找到s结点的最大的子结点
		if(j < m && L.key[j] <= L.key[j+1]) {
			//j<m是判断的元素在所有元素内，因为只有m个元素
			//L.key[j] <= L.key[j+1]是找到子节点中最大的	
			j++;
		}//endif

		//L.key[j]是rc子结点中最大的
		if(rc > L.key[j]) break;//如果rc最大则退出while

		L.key[s] = L.key[j];	//子节点比父节点大，将子节点放在父节点的位置
		s = j;					//s是rc目前的位置
	}//endfor
	L.key[s] = rc;				//把rc放在正确的位置
}

template <class T>
void HeapSort(SqList<T> &L){
	//对顺序表L进行堆排序
	T value;

	//初始化堆，将待排序序列构造成堆
	for(int i = L.length/2;i > 0;i--){
		//调整所有非叶子节点
		//L.length/2是初始堆的最后一个非叶子结点
		HeapAdjust(L,i,L.length);
	}//endfor

	for(int i = L.length;i > 1; --i){
		//数列中最后一个元素与第一个元素交换
		value = L.key[1];
		L.key[1] = L.key[i];
		L.key[i] = value;

		//待排序序列数量减一，有序的数在原始数列尾部
		HeapAdjust(L,1,i-1);//将L.key[1...i-1]重新调整为大顶堆
	}//endfor
}
#endif
