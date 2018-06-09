#include <iostream>
#include <string>
using namespace std;
#include "AdjGraphCon.h"

void opshow(){
	cout <<"1.创建无向图(图采用邻接表存储结构举例表示)"<<endl;
	cout <<"2.求生成树或森林/连通分量"<<endl;
	cout <<"3.退出"<<endl;
	cout <<"Please choose: ";
}
int main(int argc, char* argv[]){
	int opkind;
	ATGraph<string> g;
	CSTree<string> *t;
	opshow();
	cin >> opkind;
	while(opkind > 0 && opkind < 4){
		switch(opkind){
			case 1:
				cout <<"Please choose Undirected Graph:"<<endl;
				g.CreateGraph();
				g.Display();
				break;
			case 2:
				g.DFSForest(t);
				g.BTreetoForest(t);
				break;
			case 3:
				g.DestroyGraph();
				cout << "Bye-bye!"<<endl;
				break;
		}
		cout << endl;
		opshow();
		cin >> opkind;
	}//endwhile
	return 0;
}
