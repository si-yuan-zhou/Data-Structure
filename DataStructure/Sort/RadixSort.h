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
	cin >>SL.keynum;							//关键字的位数，也是基的个数
	
	//创建基，SL.SList[i]是输入第i个数，SList[i].key[j]是第i个数的第j位
	for(int i = 1;i <= SL.recnum; ++i){
		//为每个数创建keynum位，因为下标j从１开始，所以创建keynum+1个元素的数组
		SL.SList[i].keys = new T[SL.keynum+1];	//创建一个桶(基)，以i为基底
	}//endfor

	//输入数据
	SL.SList[0].next = 1;
	for(int i = 1;i <= SL.recnum; ++i){

		cout<<"请输入第"<<i<<"个数据  ";
		for(int j = 1;j <= SL.keynum; j++){
			//输入数字的每一位
			cin>>SL.SList[i].keys[j];
		}//endfor

		//连接各个基底
		if (i != SL.recnum) {
			SL.SList[i].next = i+1;
		} else {
			SL.SList[i].next = 0;
		}
	}//endfor
}

template <class T>
void RelList(SLList<T> &SL){
	//Release distributed space
	for(int i = 1;i <= SL.recnum; ++i){
		delete SL.SList[i].keys;
	}//endfor
	delete SL.SList;
}

template <class T>
void Distribute(SLCell<T> *r,int i,ArrType &f,ArrType &e){
	//按第i个关键字s[i]建立RADIX个子表，使同一子表中记录的keys[i]相同
	//f[0..RADIX]和e[0..RADIX]分别指向各个子表中第一个和最后一个记录
	
	int j;
	//初始化RADIX个基底
	for(j = 0;j < RADIX; ++j){
		f[j] = 0;
	}//endfor

	for(int a = r[0].next;a;a = r[a].next){
		//r[0].next is the first radix,the last's next is 0

		//r[i] 是一个数，按照第i位进行分配,j是数r[a]的第i位的值
		j = r[a].keys[i];

		if(!f[j]){					//如果基数为j的桶为空，则将这个数的序号放进桶中，否则就添加在原始链的后面
			f[j] = a;				//这一步只代表该基底有数，且存放链表的首地址，原序列中的第a个数
		} else {
			r[e[j]].next = a;		//把原待排序数字序列中基底为j的最后一个数的下一个元素是当前元素a
		}
		e[j] = a;					//e记录基为j的桶中最后放入的数在原序列中的序号
	}
}
template <class T>
void Collect(SLCell<T>*r,int i,ArrType &f,ArrType &e){
	//按keys[i]自小到大将f[0...RADIX]所指各个子表依次链接成一个链表
	int j;
	for(j=0;!f[j];++j);				//找第一个非空子表，（非空桶）j是桶的编号
	r[0].next = f[j];				//r[0].next指向第一个非空子表中的第一个结点

	int t = e[j];					//基数为j的桶最后放入的数序号
	while(j < RADIX){
		for(j++;j<RADIX-1 && !f[j];j++);//找下一个非空子表
		if(f[j]){
			r[t].next = f[j];		//链接两个非空子表
			t = e[j];				//记录当前基底的最后一个数的序号，方便与下一个非空桶链接
		}
	}//endwhile
	r[t].next = 0;					//t指向最后一个非空子表中的左后一个结点
}
template <class T>
void RadixSort(SLList<T> &SL){
	//对Ｌ做基数排序，使得Ｌ按关键字自小到大有序
	for(int i = SL.keynum;i>=1;i--){//按最高位优先依次对各位进行分配和收集
		Distribute(SL.SList,i,f,e);	//第i趟分配，按照第i位分配
		Collect(SL.SList,i,f,e);	//第i趟收集
	}//endfor
}
#endif
