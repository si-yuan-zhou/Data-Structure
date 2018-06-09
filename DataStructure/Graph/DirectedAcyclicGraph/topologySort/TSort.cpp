#include <iostream>
#include <string>
using namespace std;
#include "SqStack.h"
#include "topologySort.h"

void opshow(){
	cout << "1.创建图(邻接表存储)"<<endl;
	cout << "2.拓扑排序"<<endl;
	cout << "3.退出"<<endl;
	cout << "Please choose: ";
}
int main(int argc, char* argv[]){
	int opkind;
	ALGraph<string> g;
	opshow();
	cin >> opkind;
	while(opkind > 0&&opkind < 4){
		if(opkind == 1){
			g.CreateGraph();
			g.Display();
		} else if(opkind == 2){
			g.TopologicalSort();
		} else {
			cout << "Bye"<<endl;
			g.DestroyGraph();
			break;
		}
		opshow();
		cin >> opkind;
	}//endwhile
	return 0;
}
