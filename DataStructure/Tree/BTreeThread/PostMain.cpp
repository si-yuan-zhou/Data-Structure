#include <iostream>
using namespace std;
#include "PostThreading.h"
int main(int argc, char* argv[]){
	PostThreadBTree<char> PT;
	int op;
	do{
		cout << "-------- Menu ------------" << endl;
		cout << "--1:Create Ternary Tree   " << endl;
		cout << "--2:Cerate PostThreadBTree" << endl;
		cout << "--3:TraverseTree          " << endl;
		cout << "--4:Exit                  " << endl;
		cout << "Please choose: [ ]";
		cout << "\b\b";
		cin  >> op;
		switch(op){
			case 1:
				cout <<"Input nodes in Preorder and '#' means null";
				PT.CreateBTree('#');
				break;
			case 2:
				PT.PostThreading();
				break;
			case 3:
				PT.TraverseTree();
				break;
			case 4:
				cout <<"Bye-bye!"<<endl;
				break;
			default:
				cout <<"error!"<<endl;
				break;
		}//endswitch
	}while(op != 4);
	return 0;
}
