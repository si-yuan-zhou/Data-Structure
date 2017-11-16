#include<iostream>
#include<cstdio>
#include<string.h>
using namespace std;
#include "AString.h"
int main(){
	int len;
	char *str=new char[len+1];
	cout<<"Please input initialization Object size:";
	cin>>len;
	cout<<"\nPlease  input String Object(no empty string):";
	cin>>str;
	AString string(len);
	string = str;
	int tag = 0;
	while(1){
		cout<<"1--Delete"<<endl
			<<"2--Insert"<<endl
			<<"3--Connect"<<endl
			<<"4--CutString"<<endl
			<<"5--String Compare"<<endl
			<<"6--Output String Object"<<endl
			<<"7--Clear Object"<<endl
			<<"8--Voluation"<<endl
			<<"9--Exit"<<endl
			<<"\nPlease input the number of operation:";
			cin>>tag;
			switch(tag){
				case 1:
					{
						int index,length;
						cout<<"Please input start position for deletion:";
						cin>>index;
						cout<<"\nPlease input the length for delection:";
						cin>>length;
						string.Remove(index,length);
						cout<<"\nString after deleteing:";
						string.Output();
						break;
					}
				case 2:
					{
						int index;
						char *input=new char[defaultSize];
						cout<<"\nPlease input String:";
						cin>>input;
						cout<<"\nPlease input insert position:";
						cin>>index;
						string.Insert(index,input);
						cout<<"\nString Object after instering:";
						string.Output();
						delete[] input;
						break;
					}
				case 3:
					{
						char *value=new char[defaultSize+1];
						cout<<"\nPlease input string for connection:";
						cin>>value;
						AString astr=value;
						string+=astr;
						cout<<"\nString Object after connection:";
						string.Output();
						delete[] value; 
						break;
					}
				case 4:
					{
						int len,i;
						AString subs;
						cout<<"\nPlease input length to cut:";
						cin>>len;
						cout<<"\nPlease input start position:";
						cin>>i;
						string.SubString(subs,i,len);
						cout<<"\nString after cutting:";
						subs.Output();
						break;
					}
				case 5:
					{
						char *value=new char[128];
						cout<<"\nPlease input string for comparing:";
						cin>>value;
						cout<<"\nAfter comparing:";
						string.Output();
						if(string>value) cout<<">";
						if(string==value) cout<<"=";
						if(string<value) cout<<"<";
						cout<<value<<endl;
						break;
					}
				case 6:
					cout<<"\nCurrent String is:";
					string.Output();
					break;
				case 7:
					string.Clear();
					cout<<"\nString is Empty\n";
					break;
				case 8:
					{
						char *str=new char[128];
						cout<<"\nPlease input string for volution:";
						cin>>str;
						string=str;
						cout<<"\nString after volution:";
						string.Output();
						break;
					}
				case 9:
					cout<<"Bye-bye";
					return 0;
					break;
				default:
					cout<<"Error,Choose again!";
					break;
			} //switch
	}//end of while
}
 
