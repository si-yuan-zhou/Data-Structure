#include <iostream>
using namespace std;
#include "DataDefinition.h"
#include "RadixSort.h"

int main(int argc, char* argv[]){
	SLList<int> SL;
	InitSLList(SL);
	RadixSort(SL);
	cout<<"链式基数排序结果如下:"<<endl;
	OutPut(SL);
	RelList(SL);
	return 0;
}
