#ifndef __MERGESORT__
#define __MERGESORT__
#include "DataDefinition.h"
//归并排序
template <class T>
void Merge(T *SR,T *TR,int i,int m,int n){
	//将有序的SR[i...m]和SR[m+1...n]归并为有序的TR[i...n]
	int j,k;
	for(j=m+1,k=i;i <= m && j<=n;++k){
		//将SR中的记录由大到小并入TR
		if (SR[i] <= SR[j]) {
			TR[k] = SR[i++];
		} else {
			TR[k] = SR[j++];
		}
	}//endfor
	//SR[i...m] and SR[m+1...n] maybe have not the same length, 
	//so add the rest at TR's tail
	if (i <= m) {
		for(int a = i;a <= m; ++a){
			TR[k++] = SR[a];
		}//endfor
	} else if(j <= n){
		for(int b = j;b <= n; ++b){
			TR[k++] = SR[b];
		}//endfor
	}
}

template <class T>
void MSort(T *SR,T *TR1,int s,int t){
	T TR2[100];
	int m;
	//将SR[s...t]归并排序为TR[s...t]
	if (s == t) {
		//将数组元素分割成单个元素，然后递归回退再排序上一步分割的两部分
		//递归过程是先分割(递)和合并(归)，排序左边的部分，然后是右边的，
		//部分有序，且有序　部分不断变长
		TR1[s] = SR[s];
	} else {
		m = (s+t)/2;			//将SR[s...t]平分为SR[s..m]和SR[m+1...t]
		MSort(SR,TR2,s,m);		//归并地将SR[s..m]归并为有序的TR2[s...m]
		MSort(SR,TR2,m+1,t);	//归并地将SR[m+1..t]归并为TR2[m+1..m]
		Merge(TR2,TR1,s,m,t);	//将TR2[s..m]和TR2[m+1..t]归并到TR1[s...t]
	}
}

template <class T>
void MergeSort(SqList<T> &L){
	MSort(L.key,L.key,1,L.length);
}

#endif
