#include <iostream>
using namespace std;
#include "StaticSearch.h"

int main(int argc, char* argv[]){
	int choice,n,k;
	StaticSearch<int> a;
	int key;
	do{
		cout<<"---1.Create StaticChart--------"<<endl
			<<"---2.Sequential Search --------"<<endl
			<<"---3.Binary Search Un-Recursive"<<endl
			<<"---4.Binary Search Recursive---"<<endl
			<<"---5.Output            --------"<<endl
			<<"---6.Exit"<<endl
			<<"Please choose: [ ]";
		cout<<"\b\b";
		cin >> choice;
		switch(choice){
			case 1:
				cout<<"Please input length of StaticChart"<<endl;
				cin >>n;
				a.Create(n);
				break;
			case 2:
				cout<<"Please input keyword you want to search: ";
				cin >>key;
				a.endSearch(key);
				break;
			case 3:
				a.AscendSort();
				cout<<"Please input keyword you want to search: ";
				cin >>key;
				k = a.R_BiSearch(key);
				if (k == -1) {
					cout<<"No Element!"<<endl;
				} else {
					cout<<"Get it at "<<k+1<<endl;
				}
				break;
			case 4:
				a.AscendSort();
				cout<<"Please input keyword you want to search: ";
				cin >>key;
				a.UR_BiSearch(key);
				break;
			case 5:
				a.Display();
				break;
			case 6:
				cout <<"Operate End!"<<endl;
				break;
			default:
				cout <<"Illegal input, Please input again";
				break;
		}//endswitch
	}while(choice != 6);
	return 0;
}
