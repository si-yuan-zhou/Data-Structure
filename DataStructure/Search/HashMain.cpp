#include <iostream>
using namespace std;
#include "HashSearch.h"

int main(int argc, char* argv[]){
	int m,key,s=0;
	ElemType<int> e;
	HashSearch<int> a;
	do{
		cout<<"---1.Create Search Table--"<<endl
			<<"---2.Insert"<<endl
			<<"---3.Search"<<endl
			<<"---4.Display"<<endl
			<<"---5.Exit"<<endl
			<<"Please choose: [ ]";
		cout<<"\b\b";
		cin >>m;
		switch(m){
			case 1:
				cout<<"Please input Integer whose size is bigger than 5"<<endl;
				cin>>m;
				a.InitHashTable(m);
				cout<<"Input datas successively, -1 ends"<<endl;
				a.Insert(e);
				break;
			case 2:
				cout<<"Input a element: ";
				cin >>e.key;
				a.Insert(e);
				break;
			case 3:
				cout<<"Input keyword needed to be searched: ";
				cin >>key;
				if (a.Search(key,s)) {
					cout<<"Find it!"<<endl;
				} else {
					cout<<"No element!"<<endl;
				}
				break;
			case 4:
				a.Display();
				break;
			case 5:
				cout<<"END!"<<endl;
				break;
		}//endswitch
	}while(m != 5);
	return 0;
}
