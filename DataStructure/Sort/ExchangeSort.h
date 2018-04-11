#ifndef __CHANGESORT__
#define __CHANGESORT__
#include "DataDefinition.h"

//冒泡排序
template <class T>
void BubbleSort(SqList<T> &L){
	//非降序排序
	T t;
	for(int i = 1;i < L.length; ++i){
		//there will be a larger element floating up with i's increament each time
		//so i just need increase L.length-1 times
		for(int j = 1;j <= L.length - i; ++j){
			//j's range will decrease one each time
			//compare adjacent two elements within the rest
			if(L.key[j] > L.key[j+1]) {
				t = L.key[j];
				L.key[j] = L.key[j+1];
				L.key[j+1] = t;
			}//endif
		}//endfor
	}//endfor
}

//快速排序
template <class T>
int Partition(SqList<T> &L,int low,int high){
	/*
	　１．先从后向前分别与枢轴比较，交换，
	　２．然后从前向后分别与枢轴比较，交换
	由于整个过程lwo一直在增加，high一直在减少，所以low<high保证所有元素都与此次所选的枢轴进行了比较,
	当low>=high此时在枢轴之前（后）的记录均不大（小）于它，（函数返回枢轴其所在位置）

	 但是其他元素之前的相对关系没有确定，只是确地了其他元素与此次选定的枢轴之间的关系
	 所以要对枢轴左右的元素递归使用此方法
	 */
	T pivotkey;//枢轴
	L.key[0] = L.key[low];	//用子表的第一个记录作枢轴记录
	pivotkey = L.key[low];

	while(low < high){		//从表的两端交替向中间扫描

		while(low < high && L.key[high] >= pivotkey){
			--high;
		}//endwhile
		L.key[low] = L.key[high];//将比枢轴小的移动至低端此元素参与小于枢轴的比较

		while(low < high && L.key[low] <= pivotkey){
			++low;
		}//endwhile
		L.key[high] = L.key[low];//将比枢轴大的记录移至高端

	}//endwhile
	L.key[low] = L.key[0];	//枢轴记录到位
	return low;				//返回枢轴位置
}
template <class T>
void QSort(SqList<T> &L,int low,int high){
	int mid;//接受枢轴位置
	if(low < high) {//if low equals high which means all elements had been traversed
		mid = Partition(L,low,high);
		QSort(L,low,mid-1);		//对低子表排序
		QSort(L,mid+1,high);	//对高子表排序
	}//endif
}
template <class T>
void QuickSort(SqList<T> &L){
	QSort(L,1,L.length);
}

#endif
