//求解强连通分量的函数没有实现
#include <iostream>
#include <string>
using namespace std;
#include "../../CreateGraph/OrthogonalList.h"

void opshow(){
	cout <<"1.创建有向图(采用十字链表存储)"<<endl;
	cout <<"2.求图强连通分量"<<endl;
	cout <<"3.退出"<<endl;
	cout <<"Please choose: ";
}
int main(int argc, char* argv[]){
	OLGraph<string> g;
	int opkind;
	opshow();
	cin >> opkind;
	while(opkind > 0&&opkind < 4){
		switch(opkind){
			case 1:
				g.CreateGraph();
				g.Display();
				cout <<endl;
				break;
			case 2:
				g.Get_SGraph();
				cout <<endl;
				break;
			case 3:
				g.DestroyGraph();
				cout << "Bye"<<endl;
				break;
		}
		opshow();
		cin >> opkind;
	}//endwhile
	return 0;
}
