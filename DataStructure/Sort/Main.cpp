#include <iostream>
using namespace std;

#include "ExchangeSort.h"
#include "InsertSort.h"
#include "MergeSort.h"
#include "RadixSort.h"
#include "SelectSort.h"
int main(int argc, char* argv[]){
	int file,choice1,choice2,choice3,choice4,choice5;
	SqList<int> sl;

	cout<<"**Menu**"<<endl;
	cout<<"0退出程序"<<endl;
	cout<<"1插入排序"<<endl;
	cout<<"2快速排序"<<endl;
	cout<<"3选择排序"<<endl;
	cout<<"4归并排序"<<endl;
	cout<<"5基数排序"<<endl;
	cout<<"请选择主菜单：";
	cin>>file;
	while(file != 0){
		switch(file){
			case 1:
				cout<<"*插入排序*"<<endl
					<<"0退出插入排序"<<endl
					<<"1直接插入排序"<<endl
					<<"2折半插入排序"<<endl
					<<"3表插入排序　"<<endl
					<<"4希尔排序　　"<<endl;
				cout<<"请选择插入排序方法:";
				cin >>choice1;
				while(choice1 != 0){
					switch(choice1){
						case 1://直接插入排序
							CreateSqList(sl);
							InsertSort(sl);
							cout<<"直接插入排序结果如下:"<<endl;
							OutPut(sl);
							delete sl.key;
							break;
						case 2://折半插入排序
							CreateSqList(sl);
							BInsertSort(sl);
							cout<<"折半插入排序结果如下:"<<endl;
							OutPut(sl);
							break;
						case 3://表插入排序
							StaListInsertSort<int>();
							break;
						case 4://希尔排序
							int *p,n;
							cout<<"请输入增量个数:"<<endl;
							cin>>n;
							p = new int[n];
							cout<<"请输入增量的值:"<<endl;
							for(int i = 0;i < n; ++i){
								cin>>p[i];
							}//endfor
							CreateSqList(sl);
							ShellSort(sl,p,n);
							cout<<"哈希排序结果如下:"<<endl;
							OutPut(sl);
							delete p;
							break;
					}//endswitch
					cout<<"*插入排序*"<<endl
						<<"0退出插入排序"<<endl
						<<"1直接插入排序"<<endl
						<<"2折半插入排序"<<endl
						<<"3表插入排序　"<<endl
						<<"4希尔排序　　"<<endl;
					cout<<"请选择插入排序方法:";
					cin >>choice1;
				}//endwhile
				break;
			case 2:
				cout<<"**快速排序**"<<endl
					<<"0退出"<<endl
					<<"1冒泡排序"<<endl
					<<"2快速排序"<<endl;
				cout<<"请选择快速排序方式:";
				cin>>choice2;
				while(choice2 != 0){
					switch(choice2){
						case 1://冒泡排序
							CreateSqList(sl);
							BubbleSort(sl);
							cout<<"冒泡排序结果如下:"<<endl;
							OutPut(sl);
							delete sl.key;
							break;
						case 2://快速排序
							CreateSqList(sl);
							QuickSort(sl);
							cout<<"快速排序结果如下:"<<endl;
							OutPut(sl);
							break;
						default:break;
					}//endswitch
					cout<<"**快速排序**"<<endl
						<<"0退出"<<endl
						<<"1冒泡排序"<<endl
						<<"2快速排序"<<endl;
					cout<<"请选择快速排序方式:";
					cin>>choice2;
				}//endwhile
				break;
			case 3:
				cout<<"**选择排序**"<<endl
					<<"0退出"<<endl
					<<"1简单选择排序"<<endl
					<<"2树形选择排序"<<endl
					<<"3堆排序"<<endl;
				cout<<"请选择选择排序方式:";
				cin>>choice3;
				while(choice3 != 0){
					switch(choice3){
						case 1://简单排序
							CreateSqList(sl);
							SelectSort(sl);
							cout<<"简单排序结果如下:"<<endl;
							OutPut(sl);
							delete sl.key;
							break;
						case 2://树形排序
							int *date,n;
							cout<<"请输入数据个数:"<<endl;
							cin>>n;
							date = new int[n];
							cout<<"请输入数据:"<<endl;
							for(int i = 0;i < n; ++i){
								cin>>date[i];
							}//endfor
							TreeSort(date,n);
							cout<<"树形选择排序结果如下:"<<endl;
							OutPut(date,n);
							delete date;
							break;
						case 3://堆排序
							CreateSqList(sl);
							HeapSort(sl);
							cout<<"堆排序结果如下:"<<endl;
							OutPut(sl);
							delete sl.key;
							break;
					}//endswitch
				cout<<"**选择排序**"<<endl
					<<"0退出"<<endl
					<<"1简单选择排序"<<endl
					<<"2树形选择排序"<<endl
					<<"3堆排序"<<endl;
				cout<<"请选择选择排序方式:";
				cin>>choice3;
				}//endwhile
				break;
			case 4:
				cout<<"**归并排序**"<<endl
					<<"0退出"<<endl
					<<"1归并排序"<<endl;
				cout<<"请选择操作方式:";
				cin>>choice4;
				while(choice4 != 0){
					switch(choice4){
						case 1://归并排序
							CreateSqList(sl);
							MergeSort(sl);
							cout<<"归并排序结果如下:"<<endl;
							OutPut(sl);
							delete sl.key;
							break;
					}//endswitch
				cout<<"**归并排序**"<<endl
					<<"0退出"<<endl
					<<"1归并排序"<<endl;
				cout<<"请选择操作方式:";
				cin>>choice4;
				}//endwhile
				break;
			case 5:
				cout<<"**基数排序**"<<endl
					<<"0退出"<<endl
					<<"1链式基数排序"<<endl;
				cout<<"请选择基数排序方式:";
				cin>>choice5;
				while(choice5 != 0){
					switch(choice5){
						case 1:
							SLList<int> SL;
							InitSLList(SL);
							RadixSort(SL);
							cout<<"链式基数排序结果如下:"<<endl;
							OutPut(SL);
							RelList(SL);
							break;
					}//endswitch
				cout<<"**基数排序**"<<endl
					<<"0退出"<<endl
					<<"1链式基数排序"<<endl;
				cout<<"请选择基数排序方式:";
				cin>>choice5;
				}//endwhile
				break;
		}//endswitch
	cout<<"**Menu**"<<endl;
	cout<<"0退出程序"<<endl;
	cout<<"1插入排序"<<endl;
	cout<<"2快速排序"<<endl;
	cout<<"3选择排序"<<endl;
	cout<<"4归并排序"<<endl;
	cout<<"5基数排序"<<endl;
	cout<<"请选择主菜单：";
	cin>>file;
	}//endwhile
	cout<<"Bye-bye!"<<endl;
	return 0;
}
