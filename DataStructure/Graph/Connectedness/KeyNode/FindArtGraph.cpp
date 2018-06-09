#include <iostream>
#include <string>
using namespace std;

#include "keyNode.h"

void opshow(){
	cout <<"1.创建图(邻接表存储)"<<endl;
	cout <<"2.关结点和重连通分量"<<endl;
	cout <<"3.Exit"<<endl;
	cout <<"Please choose:";
}
int main(int argc, char* argv[]){
	ATGraph<string> g;
	int opkind;
	opshow();
	cin >> opkind;
	while(opkind > 0&&opkind < 4){
		if (opkind == 1) {
			g.CreateGraph();
			g.Display();
		} else if(opkind == 2){
			g.FindArcticul();
			if(flg = false)
				cout <<"Has not Articul"<<endl;
			cout <<"此时各顶点计算所得visited和low的函数值如下："<<endl
			cout <<"i\tatgraph.vertexs[i].data\t visited[i]\t low[i]"<<endl;
			for(int i = 0;i < g.atgraph.vexNum;++i){
				cout <<i<<'\t'<<g.atgraph.vertexs[i].data<<"\t\t\t"<<g.visited[i]<<"\t\t"<<g.low[i]<<endl;
			}
		} else {
			g.DestoryGraph();
			cout <<"Bye!"<<endl;
		}
		opshow();
		cin >> opkind;
	}//endwhile
	return 0;
}
