#include <iostream>
using namespace std;
#include "PreThreading.h"
int main(int argc, char* argv[]){
	int op;
	PreThreading<int> Tr;//创建一个int模板类对象
	do{
		cout << "--------------Menu----------------" << endl;
		cout << "--*1:Create BTree                 " << endl;
		cout << "--*2:PreThread BTree              " << endl;
		cout << "--*3:PreThread BTree Traverse     " << endl;
		cout << "--*4:Display PreThread Information" << endl;
		cout << "--*5:Exit" << endl;
		cout << "Please choose [ ]";
		cout << "\b\b";
		cin  >> op;
		switch(op){
			case 1:
				if(Tr.GetRoot())
					Tr.DeleteNode();
				Tr.CreateBTree(-1);
				break;
			case 2:
				Tr.PreThreadBTree();
				cout << "Thread finished!" << endl;
				break;
			case 3:
				Tr.PreThreadTraverse();
				break;
			case 4:
				Tr.ShowPreTree();
				break;
			default:break;
		}//endswitch
	}while(op != 5);
	return 0;
}
