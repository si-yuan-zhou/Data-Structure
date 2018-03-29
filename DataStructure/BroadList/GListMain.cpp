#include <iostream>
#include <string>
using namespace std;
#include "BroadList.h"

int main(int argc, char const *argv[])
{
	GLists<char> *stulists,*stulistsHead,*stulistsTail;
	string str = "(a,b,(a,b))";
	stulists = new GLists<char>(str);//生成str表示的广义表
	cout << "The initial BroadList is:" <<endl;
	stulists->Print();
	system("cls");
	int choice;
	do{
		cout << "1- Display the BroadList" <<endl;
		cout << "2- Caculate the Length  " <<endl;
		cout << "3- Caculate the Depth   " <<endl;
		cout << "4- Caculate the HeadNode" <<endl;
		cout << "5- Caculate the TailNode" <<endl;
		cout << "6- Create a BroadList   " <<endl;
		cout << "7- Exit" <<endl;
		cout << "Please chose: ";
		cin >> choice;
		switch(choice){
			case 1:
				stulists->Print();
				system("pause");
				break;
			case 2:
				cout << endl << "The Length of BroadList:";
				cout << stulists->Length() << endl;
				system("pause");
				break;
			case 3:
				cout << endl << "The Depth of BroadList:";
				cout << stulists->DepthGList() << endl;
				system("pause");
				break;
			case 4:
				stulistsHead = stulists->Head();
				cout << endl <<"The HeadNode is:";
				stulistsHead->Print();
				system("pause");
				break;
			case 5:
				stulistsTail = stulists->Tail();
				cout << endl <<"The TailNode is:";
				stulistsTail->Print();
				system("pause");
				break;
			case 6:
				cout << "Please input BroadList:";
				cin >> str;
				stulists = new GLists<char>(str);
				cout << "The BroadList constructed:";
				stulists->Print();
				system("pause");
				break;
			case 7:
				exit(0);
				break;
			default:
				cout << "Invalid choice!";
				break;
		}
	}while(choice != 7);

	return 0;
}
