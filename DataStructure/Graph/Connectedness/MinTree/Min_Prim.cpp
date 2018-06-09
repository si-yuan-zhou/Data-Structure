#include <iostream>
#include <string>
using namespace std;
#include "Prim.h"

void opshow(){
	cout <<"1.无向图的创建(数组存储)"<<endl;
	cout <<"2.求最小生成树Prim"<<endl;
	cout <<"3.EXit"<<endl;
	cout <<"Pelase choose:";
}
int main(int argc, char* argv[]){
	MGraph<string> g;
	string u;
	int opkind;
	opshow();
	cin >> opkind;
	while(opkind > 0&&opkind < 4){
		switch(opkind){
			case 1:
				g.CreateUDN();
				g.Display();
				break;
			case 2:
				cout <<"Please enter the start node"<<endl;
				cin >> u;
				g.MinSpanTree_Prim(u);
				break;
			case 3:
				g.DestoryGraph();
				cout << "Bye"<<endl;
				break;
		}//endswitch
		opshow();
		cin >> opkind;
	}//endwhile
	return 0;
}
