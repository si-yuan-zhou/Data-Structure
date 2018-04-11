#ifndef __RADIXSORT__
#define __RADIXSORT__
#include "DataDefinition.h"

template <class T>
void InitSLList(SLList<T> &SL){
	//创建静态链表
	cout<<"建立静态链表"<<endl<<"请输入数据个数："<<endl;
	cin >>SL.recnum;
	SL.SList = new SLCell<T>[SL.recnum+1];
	cout<<"请输入关键字项数"<<endl;
	cin >>SL.keynum;
	for(int i = 1;i <= SL.recnum; ++i){
		SL.SList[i].keys = new T[SL.keynum+1];
	}//endfor
	SL.SList[0].next = 1;
	cout<<"请输入数据"<<endl;
	for(i = 1;i <= SL.recnum; ++i){
		cout<<"请输入第"<<i<<"个数据"<<endl;
		for(int j = 1;j <= SL.keynum; j++){
			cin>>SL.SList[i].keys[j];
		}//endfor
		if (i != SL.recnum) {
			SL.SList[i].next = i+1;
		} else {
			SL.SList[i].next = 0;
		}
	}//endfor
}

template <class T>
void RelList(SLList<T> &SL){
	for(int i = 1;i < SL.recnum; ++i){
		delete SL.SList[i].keys;
	}//endfor
	delete SL.SList;
}

template <class T>
void Distribute(SLCell<T> *r,int i,ArrType &f,ArrType &e){
	//按第i个关键字keys[i]建立RADIX个子表，使同一子表中记录的keys[i]相同
	//f[0..RADIX]和e[0..RADIX]分别指向各个子表中第一个和最后一个记录
	int j;
	for(j = 0;j < RADIX; ++j){
		f[j] = 0;
	}//endfor
	for(int a = r[0].next;a;a = r[a].next){
		j = r[a].keys[i];
		if (!f[i]) {
			f[j] = a;
		} else {
			r[e[j]].next = a;
		}
		e[j] = a;
	}
}
template <class T>
void Collect(SLCell<T>*r,int i,ArrType &f,ArrType &e){
	//按keys[i]自小到大将f[0...RADIX]所指各个子表依次链接成一个链表
	int j;
	for(j=0;!f[j];++j);//找第一个非空子表
	r[0].next = f[j];	//r[0].next指向第一个非空子表中的第一个结点
	int t = e[j];
	while(j < RADIX){
		for(j++;j<RADIX-1 && !f[j];j++);//找下一个非空子表
		if(f[j]){
			r[t].next = f[j];
			t = e[j];	//链接两个非空子表
		}
	}//endwhile
	r[t].next = 0;		//t指向最后一个非空子表中的左后一个结点
}
template <class T>
void RadixSort(SLList<T> &SL){
	//对Ｌ做基数排序，使得Ｌ按关键字自小到大有序
	for(int i = SL.keynum;i>=1;i--){//按最高位优先依次对各关键字进行分配和收集
		Distribute(SL.SList,i,f,e);//第i趟分配
		Collect(SL.SList,i,f,e);	//第i趟收集
	}//endfor
}
#endif
