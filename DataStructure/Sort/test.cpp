#include <iostream>
using namespace std;

#include "DataDefinition.h"
#include "SelectSort.h"

//void InsertSort(int L[]){
//	for(int i = 2;i <= 10; ++i){
//		int j;
//		if(L[i] <= L[i-1]) {	//the former is bigger than the current one
//			L[0] = L[i];		//复制为哨兵
//			L[i] = L[i-1];		
//			for(j = i-2;L[0] <= L[j]; --j){
//				L[j+1] = L[j];	//记录后移
//			}//endfor
//			L[j+1] = L[0];	//插入到正确的位置
//		}//endif
//	}//endfor
//}

//void ShellInsert(int L[],int dk){
//	//dk is the increment(两个元素的位置差)
//	for(int i = dk+1;i <= 10; ++i){
//		if(L[i] <= L[i-dk]) {
//			L[0] = L[i];
//			int j;
//			for(j = i-dk;j > 0 && L[0] <= L[j];j-=dk){
//				L[j+dk] = L[j];
//			}//endfor
//			L[j+dk] = L[0];
//		}//endif
//	}//endfor
//}
//void ShellSort(int L[],int dlta[],int t){
//	//按照增量序列dl[0]~dl[t-1]对顺序表L作希尔排序
//	//dkta[]是增量表，t是要使用的增量个数
//	for(int k = 0;k < t; ++k){
//		ShellInsert(L,dlta[k]);
//	}//endfor
//}

//void BInsertSort(int L[]){
//	int high,low,m;
//	for(int i = 2;i <= 10 ; ++i){
//		L[0] = L[i];	//将L[i]暂存到L[0]
//		low = 1;
//		high = i-1;
//		while(low <= high){
//			m = (low + high)/2;
//			if (L[0] <= L[m]) {
//				high = m - 1;	//插入低半区
//			} else {
//				low = m + 1;	//插入高半区
//			}
//		}//endwhile
//		//while退出时high<low,j-1位置是待插元素
//		for(int j = i-1;j >= high+1; --j){
//			L[j+1] = L[j];//记录后移
//		}//endfor
//		L[high+1] = L[0];//插入
//	}//endfor
//}

//数据表类定义
//const int SIZE = 100;		//静态链表最大容量
//const int MAXINT = 10000;	//最大整数
//
//template <class T>
//struct StaListNode{
//	T data;		//记录项
//	int next;	//指针项
//};
//template <class T>
//class StaticList {
//	public:
//		StaListNode<T> node[SIZE];
//		int curlen;	//链表实际长度
//		StaticList();
//		//~StaticList();
//};
//template <class T>
//StaticList<T>::StaticList(){
//	cout << "创建静态链表"<<endl;
//	cout << "请输入静态链表的实际长度："<<endl;
//	cin  >>curlen;
//	cout << "请输入各结点数量："<<endl;
//	node[0].data = MAXINT;
//	node[0].next = 0;
//	for(int i = 1;i <= curlen; ++i){
//		node[i].next = 0;
//		cin >> node[i].data;
//	}//endfor
//}
//template <class T>
//void StaListInsertSort(){
//	StaticList<T> sl;
//	int min,max;
//	sl.node[0].next = 1;	//把第一个元素视为最小的
//	sl.node[1].next = 0;	//初始化形成只有头结点的循环链表
//	max = min = 1;
//
//	for(int i = 2;i <= sl.curlen; ++i){
//		//找到最小值并插入正确位置
//		if(sl.node[i].data <= sl.node[min].data) {
//			sl.node[0].next = i;	//首元素的next是最小值的位置
//			//当前元素插入到最小的的前面
//			sl.node[i].next  = min;
//			min = i;				//min <-curPosition
//		}//endif
//
//		//找到最大值并插入正确位置
//		if(sl.node[i].data >= sl.node[max].data) {
//			sl.node[i].next = 0;	//最大元素的next是0
//			sl.node[max].next = i;	//把当前元素插入到最大元素后
//			max = i;				//max <-curPosition
//		}//endif
//
//		if(sl.node[i].data < sl.node[max].data && sl.node[i].data > sl.node[min].data) {
//			int index1 = min,index2;
//			while(sl.node[i].data >= sl.node[index1].data){
//				//从最小值开始向后遍历(升序)找到插入位置
//				index2 = index1;
//				index1 = sl.node[index1].next;
//			}//endwhile
//			//index1是插入位置的下一个位置，插在第index2元素后
//			sl.node[i].next = index1;
//			sl.node[index2].next = i;
//		}//endif
//	}//endfor
//	
//	cout <<"表插入排序结果如下："<<endl;
//	T index = sl.node[0].next;
//	while(index != 0){//最大值的next是0
//		cout << sl.node[index].data <<"\t";
//		index = sl.node[index].next;
//	}//endwhile
//	cout<<endl;
//}
//int Partition(int L[],int low,int high){
//	/*
//	 交换顺序表L中的子[low][high]中的记录，枢轴记录到位，并返回其所在位置，
//	 此时在它之前（后）的记录均不大（小）于它
//	 */
//	int  pivo;//枢轴
//	L[0] = L[low];	//用子表的第一个记录作枢轴记录
//	pivo = L[low];
//
//	while(low < high){		//从表的两端交替向中间扫描
//
//		while(low < high && L[high] >= pivo){
//			--high;
//		}//endwhile
//		L[low] = L[high];//将比枢轴小的移动至低端此元素参与小于枢轴的比较
//
//		while(low < high && L[low] <= pivo){
//			++low;
//		}//endwhile
//		L[high] = L[low];//将比枢轴大的记录移至高端
//
//	}//endwhile
//	L[low] = L[0];	//枢轴记录到位
//	return low;				//返回枢轴位置
//}
//void QSort(int L[],int low,int high){
//	int mid;//接受枢轴位置
//	if(low < high) {//if low equals high which means all elements had been traversed
//		mid = Partition(L,low,high);
//		QSort(L,low,mid-1);		//对低子表排序
//		QSort(L,mid+1,high);	//对高子表排序
//	}//endif
//}

//归并排序
//void Merge(int SR[],int TR[],int i,int m,int n){
//	//将有序的SR[i...m]和SR[m+1...n]归并为有序的TR[i...n]
//	int j,k;
//	for(j=m+1,k=i;i <= m && j<=n;++k){
//		//将SR中的记录由大到小并入TR
//		if (SR[i] <= SR[j]) {
//			TR[k] = SR[i++];
//		} else {
//			TR[k] = SR[j++];
//		}
//	}//endfor
//	//SR[i...m] and SR[m+1...n] maybe have not the same length, 
//	//so add the rest at TR's tail
//	if (i <= m) {
//		for(int a = i;a <= m; ++a){
//			TR[k++] = SR[a];
//		}//endfor
//	} else if(j <= n){
//		for(int b = j;b <= n; ++b){
//			TR[k++] = SR[b];
//		}//endfor
//	}
//}
//
//void MSort(int SR[],int TR1[],int s,int t){
//	int TR2[100];
//	int m;
//	//将SR[s...t]归并排序为TR[s...t]
//	if (s == t) {
//		//将数组元素分割成单个元素，然后递归回退再排序上一步分割的两部分
//		//递归过程是先分割(递)和合并(归)，排序左边的部分，然后是右边的，
//		//部分有序，且有序　部分不断变长
//		TR1[s] = SR[s];
//	} else {
//		m = (s+t)/2;			//将SR[s...t]平分为SR[s..m]和SR[m+1...t]
//		MSort(SR,TR2,s,m);		//归并地将SR[s..m]归并为有序的TR2[s...m]
//		MSort(SR,TR2,m+1,t);	//归并地将SR[m+1..t]归并为TR2[m+1..m]
//		Merge(TR2,TR1,s,m,t);	//将TR2[s..m]和TR2[m+1..t]归并到TR1[s...t]
//	}
//}
//
//void MergeSort(int L[]){
//	MSort(L,L,1,9);
//}

//int SelectMinKey(int L[],int n){
//	//选择最小数，从n开始
//	int min = n;
//	int mi;
//	mi = L[n];
//	for(int i = n+1;i <= 9; ++i){
//		if(L[i] < mi) {
//			mi = L[i];	//get minimum value
//			min = i;			//get minimum position
//		}//endif
//	}//endfor
//	return min;
//}
//
//void SelectSort(int L[]){
//	int j;
//	int t;
//	for(int i = 1;i <= 9; ++i){
//		j = SelectMinKey(L,i);
//		//在L[i]~L[9]中选择最小的记录并将其地址赋值给j
//		if(i != j) {
//			t = L[i];
//			L[i] = L[j];
//			L[j] = t;
//		}//endif
//	}//endfor
//}


//void HeapAdjust(int L[],int s,int m){
//	//对顺序表做查找，从值最大的孩子结点向下筛选，找到最大值
//	//每次只对一个元素rc进行操作，使其所在子树满足堆的定义
//	//把s到m的元素进行调整
//
//	int rc = L[s];
//	for(int j = 2*s;j <= m;j *= 2){
//		//2*s是L[s]的左子结点，每次乘2就找到左孩子的左孩子
//
//		//找到s结点的最大的子结点
//		if(j < m && L[j] <= L[j+1]) {
//			//j<m是判断的元素在所有元素内，因为只有m个元素
//			//L[j] <= L[j+1]是找到子节点中最大的	
//			j++;
//		}//endif
//
//		//L[j]是rc子结点中最大的
//		if(rc > L[j]) break;//如果rc最大则退出while
//
//		L[s] = L[j];	//子节点比父节点大，将子节点放在父节点的位置
//		s = j;					//s是rc目前的位置
//	}//endfor
//	L[s] = rc;				//把rc放在正确的位置
//}
//
//void HeapSort(int L[]){
//	//对顺序表L进行堆排序
//	int value;
//
//	//初始化堆，将待排序序列构造成堆
//	for(int i = 9/2;i > 0;i--){
//		//调整所有非叶子节点
//		//9/2是初始堆的最后一个非叶子结点
//		HeapAdjust(L,i,9);
//	}//endfor
//
//	for(i = 9;i > 1; --i){
//		//数列中最后一个元素与第一个元素交换
//		value = L[1];
//		L[1] = L[i];
//		L[i] = value;
//
//		//待排序序列数量减一，有序的数在原始数列尾部
//		HeapAdjust(L,1,i-1);//将L[1...i-1]重新调整为大顶堆
//	}//endfor
//}

int main(int argc, char* argv[]){
	int a[10] = {0,4,7,3,9,12,10,6,2,5};
	//InsertSort(a);
	//BInsertSort(a);
	//StaListInsertSort<int>();
	//QSort(a,1,9);
	//MergeSort(a);
	//SelectSort(a);
	//HeapSort(a);
	cout<<"Tree Sort"<<endl;
	TreeSort<int>(a,10);
	cout<<"Result"<<endl;
	OutPut<int>(a,10);
	
	//int a2[11] = {0,4,7,3,9,12,10,6,2,5,1};
	//int d[5]={5,4,3,2,1};
	//ShellSort(a2,d,5);
	
	//for(int i = 1;i <= 9; ++i){
	//	cout <<a[i]<<" ";
	//}//endfor
	return 0;
}
