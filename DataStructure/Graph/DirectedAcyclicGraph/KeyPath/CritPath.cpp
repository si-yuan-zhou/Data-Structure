#include <iostream>
#include <string>
using namespace std;
#include "CritPath.h"

void opshow(){
	cout << "1.创建有向图(采用邻接表存储)" << endl;
	cout << "2.求关键路径" << endl;
	cout << "3.退出" << endl;
	cout << "Please choose: ";
}
int main(int argc, char* argv[]){
	int opkind;
	ALGraph<string> g;
	opshow();
	cin >> opkind;
	while(opkind > 0 && opkind < 4){
		if (opkind == 1) {
			g.CreateGraph();
			g.Display();
		} else if(opkind == 2){
			g.CriticalPath();
		} else {
			g.DestroyGraph();
			break;
		}
		opshow();
		cin >> opkind;
	}//endwhile
	return 0;
}
