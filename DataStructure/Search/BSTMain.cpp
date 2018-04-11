#include <iostream>
using namespace std;
#include "BinSortTreeSearch.h"

int main(int argc, char* argv[]){
	int m,l,i;
	BSTree<int> a;
	do{
		cout<<"---BST Base Operation---"<<endl
			<<"---1.Create SearchChart-"<<endl
			<<"---2.Insert Element     "<<endl
			<<"---3.Delete Element     "<<endl
			<<"---4.Search Element     "<<endl
			<<"---5.InOrdTraverse Print"<<endl
			<<"---6.Print SearchChart--"<<endl
			<<"---7.Exit"<<endl
			<<"Please choose:[ ]";
		cout<<"\b\b";
		cin >>m;
		Node<int> e;
		int key;
		switch(m){
			case 1:
				cout<<"Input the count of element needed to be inserted"<<endl;
				cin >>l;
				cout<<"Please input "<<l<<"element(s)"<<endl;
				for(i = 0;i < l; ++i){
					cin >>e.key;
					a.InsertBST(a.t,e);
				}//endfor
				break;
			case 2:
				cout<<"Input data needed to be inserted"<<endl;
				cin >>e.key;
				a.InsertBST(a.t,e);
				break;
			case 3:
				cout<<"Input elelment needed to be deleted: ";
				cin >>key;
				a.DeleteBST(a.t,key);
				a.DeleteElem(key);
				break;
			case 4:
				cout<<"Input element needed to search: ";
				cin >>key;
				a.SearchBST(a.t,key);
				break;
			case 5:
				cout<<"After Inorder Traverse.."<<endl;
				a.InDisplay(a.t);
				cout<<endl;
				break;
			case 6:
				cout<<"Display BSTree:"<<endl;
				a.Display();
				cout<<endl;
				break;
			case 7:
				cout<<"Operation end!"<<endl;
				break;
			default:
				cout<<"Input error!"<<endl;
				break;
		}//endswitch
	}while(m != 7);
	return 0;
}
