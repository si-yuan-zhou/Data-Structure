#include<iostream>
#include<cstdio>
using namespace std;
#include<string.h>
#include "StringMatching.h"
int main(){
	char s[]="abcdef";
	StringMatching str(s);
	char T[]="def";
	int *next=new int[3];
	int pos=0;//retrieval position
	int choice,index;
	do{
		cout<<"1--Create Main String and Substring\n"
			<<"2--BF Matching\n"
			<<"3--Show Next\n"
			<<"4--KMP Matching\n"
			<<"5--Display\n"
			<<"6--Exit"<<endl;
		cout<<"Please input your choice:";
		cin>>choice;
		switch(choice){
			case 1:
				str.InputStr();
				cout<<"Please input substring:";
				cin>>T;
				next=new int[strlen(T)];//
				cout<<"Main string is: ";
				str.OutputStr();
				cout<<"\nSubstring is: ";
				cout<<T<<endl;
				break;
			case 2:
				index=str.IndexBF(T,pos);
				cout<<"Index is: "<<index<<endl;
				break;
			case 3:
				str.GetNext(T,next);
				for(int n=0;n<strlen(T);n++)
					cout<<next[n]<<'\t';
				cout<<endl;
				break;
			case 4:
				index=str.IndexKMP(T,next,pos);
				cout<<"Index is: "<<index<<endl;
				break;
			case 5:
				cout<<"Main string is:";
				str.OutputStr();
				cout<<"Substring is: ";
				cout<<T<<endl;
				break;
			case 6:
				cout<<"Bye-bye";
				break;
			default:
				break;
		}	
	}while(choice!=6);
	return 0;
} 
