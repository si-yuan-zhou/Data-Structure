#ifndef __SELECTSORT__
#define __SELECTSORT__
#include "DataDefinition.h"

//简单选择排序
template <class T>
int SelectMinKey(SqList<T> &L,int n){
	//选择最小树
	int min = n;
	T minkey;
	minkey = L.key[n];
	for(int i = n+1;i <= L.length; ++i){
		if(L.key[i] < minkey) {
			minkey = L.key[i];
			min = i;
		}//endif
	}//endfor
	return min;
}

template <class T>
void SelectSort(SqList<T> &L){
	int j;
	T t;
	for(int i = 1;i < L.length; ++i){
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
	int j;
	if (i % 2 == 0) {
		tree[(i-1)/2] = tree[i-1];//当i为偶数时和左结点比较
	} else {
		tree[(i-1)/2] = tree[i+1];//当i为奇数时和右结点比较
	}
	i = (i-1)/2;
	while(i){
		if (i%2 == 0) {
			j = i - 1;
		} else {
			j = i + 1;
		}

		if (!tree[i].active || !tree[j].active) {
			if (tree[i].active) {
				tree[(i-1)/2] = tree[i];
			} else {
				tree[(i-1)/2] = tree[j];
			}
		} else {
			if (tree[i].data < tree[j].data) {
				tree[(i-1)/2] = tree[i];
			} else {
				tree[(i-1)/2] = tree[j];
			}
		}
		i = (i-1)/2;
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
	//满二叉树的叶子结点总数
	for(int i = 1;i < 100; ++i){
		if (Power(i-1) < n && n < Power(i)) {
			return Power(i);
		} else if(Power(i-1) == n){
			return Power(i-1);
		}
	}//endfor
}

template <class T>
void TreeSort(T a[],int n){
	//本排序算法方法只适合满二叉树
	TreeNode<T> *tree;
	int bottomSize = LeapNum(n);	//树底层结点个数，此处必须满足满二叉树
	int size = 2*bottomSize - 1;		//树中结点总数
	int externalIndex = bottomSize - 1;	//开始比较的结点位置
	tree = new TreeNode<T>[size];
	int j = 0;
	for(int i = externalIndex;i < size; ++i){
		tree[i].index = i;
		if (j < n) {
			tree[i].active = 1;
			tree[i].data = a[j++];
		} else {
			tree[i].active = 0;
		}
	}//endfor
	i = externalIndex;
	while(i){
		//比较找到最小结点
		j = i;
		while(j < 2*i){
			if(!tree[j+1].active || tree[j].data <= tree[j+1].data) {
				if(!tree[j+1].active && !tree[j].active) {
					tree[(j-1)/2].active = 0;//其孩子结点都是额外结点，不可访问
				}//endif
				tree[(j-1)/2] = tree[j];//较小结点赋值给其双亲结点
			} else {
				tree[(j-1)/2] = tree[j+1];
			}
			i = (i-1)/2;
		}//endwhile
	}//endwhile
	for(i = 0;i < n-1; ++i){			//处理前n-1个结点
		a[i] = tree[0].data;
		tree[tree[0].index].active = 0;	//不在参加比较
		ChangeTree(tree,tree[0].index);	//修改树结构
	}//endfor
	a[n-1] = tree[0].data;				//处理数值最大的结点
}

//堆排序
template <class T>
void HeapAdjust(SqList<T> &L,int s,int m){
	//对顺序表做查找，从值最大的孩子结点向下筛选，找到最大值
	T rc = L.key[s];
	for(int j = 2*s;j <= m;j *= 2){
		if(j < m && L.key[j] <= L.key[j+1]) {
			//找到值相对较大的孩子结点，并依次向下筛选
			j++;
		}//endif
		if(rc > L.key[j]) break;//如果rc最大则退出while
		L.key[s] = L.key[j];	//最大值赋值
		s = j;					//交换位置
	}//endfor
	L.key[s] = rc;
}

template <class T>
void HeapSort(SqList<T> &L){
	//对顺序表L进行堆排序
	T value;
	for(int i = L.length/2;i > 0;i--){
		//把L.key[1...L.length]调整为大顶堆
		HeapAdjust(L,i,L.length);
	}//endfor
	for(i = L.length;i > 1; --i){
		value = L.key[1];
		L.key[1] = L.key[i];
		L.key[i] = value;
		HeapAdjust(L,1,i-1);//将L.key[1...i-1]重新调整为大顶堆
	}//endfor
}
#endif
