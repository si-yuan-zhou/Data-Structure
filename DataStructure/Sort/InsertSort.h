#ifndef __INSERTSORT__
#define __INSERTSORT__
#include "DataDefinition.h"

//直接插入排序
/*在要排序的一组数中，假定前n-1个数已经排好序，现在将第n个数插到前面的有序数列中，
  使这n个数也是排好顺序的。如此反复循环，直到全部排好顺序*/
/*
   Input:  Unsort list
   Output: Sorted list
   1.traverse from 2 to end of List
		1.1 if current element is smaller than the former
		1.2 L.key[0] <- current Element
		1.3 put the former one back one step
		1.4 put back these which is bigger than current element -L.key[0]-
			before L.key[i-1] successively 
		1.5 put L.key[0] to correct place

 */
template <class T>
void InsertSort(SqList<T> &L){
	for(int i = 2;i <= L.length; ++i){
		int j;
		if(L.key[i] <= L.key[i-1]) {	//the former is bigger than the current one
			L.key[0] = L.key[i];		//复制为哨兵
			L.key[i] = L.key[i-1];		
			for(j = i-2;L.key[0] <= L.key[j]; --j){
				L.key[j+1] = L.key[j];	//记录后移
			}//endfor
			L.key[j+1] = L.key[0];	//插入到正确的位置
		}//endif
	}//endfor
}

//折半插入排序
/*在直接插入排序中是把当前元素与前n个有序元素比较，判断应该插入的位置，
如果前面的有序序列较长时，逐一比较会特别浪费时间，而折半插入排序在查找插入位置时可以节省大量时间*/
/*
	Input:Unsort list
	Output:Sorted list
	1.i from 2 to L's tail
		1.1 L.key[0] <- current element
		1.2 find region satisfied to insert(high < low, right now)
		1.3 put from high+1 to i-1 back one step
		1.4 L.key[high+1] <- L.key[0]
 */
template <class T>
void BInsertSort(SqList<T> &L){
	int high,low,m;
	for(int i = 2;i <= L.length ; ++i){
		L.key[0] = L.key[i];	//将L.key[i]暂存到L.key[0]
		low = 1;
		high = i-1;
		while(low <= high){
			m = (low + high)/2;
			if (L.key[0] <= L.key[m]) {
				high = m - 1;	//插入低半区
			} else {
				low = m + 1;	//插入高半区
			}
		}//endwhile
		//while退出时high<low,j-1位置是待插元素
		for(int j = i-1;j >= high+1; --j){
			L.key[j+1] = L.key[j];//记录后移
		}//endfor
		L.key[high+1] = L.key[0];//插入
	}//endfor
}

//表插入排序
//表插入排序是使用静态链表进行插入排序, 每次插入修改指针项, 通过指针项的链接顺序, 使静态链表有序
/*
	1.先将首元素设为最小元素，第一个元素设为最大元素
	2.1.如果当前元素小于最小元素则插入最小元素之前
	2.2.如果当前元素大于最大元素则插入最大元素之后
	2.3.如果当前元素介于最小与最大元素之间
		2.3.1从表最小元素开始向后遍历找到应该插入的位置
 */
template <class T>
void StaListInsertSort(){
	StaticList<T> sl;
	int min,max;
	sl.node[0].next = 1;	//把第一个元素视为最小的
	sl.node[1].next = 0;	//初始化形成只有头结点的循环链表
	max = min = 1;

	for(int i = 2;i <= sl.curlen; ++i){
		//找到最小值并插入正确位置
		if(sl.node[i].data <= sl.node[min].data) {
			sl.node[0].next = i;	//首元素的next是最小值的位置
			sl.node[i].next = min;  //当前元素插入到最小的的前面
			min = i;				//min <-curPosition
		}//endif

		//找到最大值并插入正确位置
		if(sl.node[i].data >= sl.node[max].data) {
			sl.node[i].next = 0;	//最大元素的next是0
			sl.node[max].next = i;	//把当前元素插入到最大元素后
			max = i;				//max <-curPosition
		}//endif

		if(sl.node[i].data < sl.node[max].data && sl.node[i].data > sl.node[min].data) {
			int index1 = min,index2;
			while(sl.node[i].data >= sl.node[index1].data){
				//从最小值开始向后遍历(升序)找到插入位置
				index2 = index1;
				index1 = sl.node[index1].next;
			}//endwhile
			//index1是插入位置的下一个位置，插在第index2元素后
			sl.node[i].next = index1;
			sl.node[index2].next = i;
		}//endif
	}//endfor
	
	cout <<"表插入排序结果如下："<<endl;
	T index = sl.node[0].next;
	while(index != 0){//最大值的next是0
		cout << sl.node[index].data <<"\t";
		index = sl.node[index].next;
	}//endwhile
	cout<<endl;
}

//希尔排序
/*在要排序的一组数中，根据某一增量分为若干子序列，并对子序列分别进行直接插入排序。
然后逐渐将增量减小,并重复上述过程。直至增量为1,此时数据序列基本有序,最后进行插入排序*/
/*
	Input: Unsort list and increment
	Output:Sorted list
	1.increment from dk to L's tail
		1.1 if current element is smeller than the former one in subsquence
		1.2 store current element in L.key[0]
		1.3 do directInsertSort to current subsequence to make it ordered
 */

template <class T>
void ShellInsert(SqList<T> &L,int dk){
	//dk is the increment(两个元素的位置差)
	for(int i = dk+1;i <= L.length; ++i){
		if(L.key[i] <= L.key[i-dk]) {//比较两端的元素
			L.key[0] = L.key[i];
			int j;
			/*
			   每次减dk是因为子序列中的元素之间间隔为dk
			   对子序列中的元素进行直接插入排序，直接插入排序前n个元素已经有序

			   在前n个有序的序列中从后向前找到第一个大于当前元素的元素
			   与当前元素交换实现子序列的内部直接插入排序
			 */
			for(j = i-dk;j > 0 && L.key[0] <= L.key[j];j-=dk){
				L.key[j+dk] = L.key[j];
			}//endfor
			//此处的j+dk是因为在执行完for循环后还会 j-=dk在判断，所以退出是就多减可了dk
			L.key[j+dk] = L.key[0];
		}//endif
	}//endfor
}

template <class T>
void ShellSort(SqList<T> &L,int dlta[],int t){
	//按照增量序列dl[0]~dl[t-1]对顺序表L作希尔排序
	//dkta[]是增量表，t是要使用的增量个数
	for(int k = 0;k < t; ++k){
		ShellInsert(L,dlta[k]);
	}//endfor
}
#endif
