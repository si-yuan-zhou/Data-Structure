#include <iostream>
using namespace std;
#include "InThreading.h"
int main(int argc, char* argv[]){
	int op;
	InThreading<int>  Tr;
	do{
		cout <<"---------- Menu ------------"<<endl;
		cout <<"--1.Create Binary Link Tree "<<endl;
		cout <<"--2.InThreadBTree           "<<endl;
		cout <<"--3.Traverse InThreadBTree  "<<endl;
		cout <<"--4.Display InThreadBTree   "<<endl;
		cout <<"--5.Exit                    "<<endl;
		cout <<"----------------------------"<<endl;
		cout <<"Please choose:[ ]";
		cout <<"\b\b";
		cin  >> op;
		switch(op){
			case 1:
				if(Tr.GetRoot()) {
					Tr.DeleteNode();
				}//endif
				Tr.CreateBTree(-1);
				break;
			case 2:
				Tr.InThreadBTree();
				cout <<"Threading finished!"<<endl;
				break;
			case 3:
				Tr.InThreadTraverse();
				break;
			case 4:
				Tr.ShowInTree();
				break;
			case 5:
				cout <<"Bye-bye!"<<endl;
				break;
			default:break;
		}//endswitch
	}while(op != 5);
	return 0;
}
