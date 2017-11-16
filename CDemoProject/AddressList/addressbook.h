/*
FileName:addresslist.h
Content:Data structure,fileinclude,functiondefine,global varibles
*/ 
#ifndef _ADLH
	#define _ADLH
	//避免文件多重包含
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	
	//data structure
	struct AddressBook{
		char szName[20];//name
		char szMobil[15];//mobilphone number
		char szTel[15];//telphone number
		struct AddressBook *next;	
	}; 
	typedef struct AddressBook ADDRESSBOOK;
	typedef struct AddressBook* PADDRESSBOOK;
	
	//Menu Choice
	char *szpMenu[]={
		"1.创建",
		"2.显示",
		"3.查询",
		"4.修改",
		"5.添加",
		"6.删除",
		"7.退出" 
	};
	
	//主菜单选择码定义
	#define CREATEADDRESSBOOK 0 
	#define SHOWADDRESSBOOK   1
	#define QUERYADDRESSBOOK  2
	#define MODIFYADDRESSBOOK 3
	#define APPENDADDRESSBOOK 4
	#define DELETEADDRESSBOOK 5
	#define EXITADDRESSBOOK   6
	
	//FUNCTION DEFINE
	int SelMenuItem(void);
	int CreateAddressBook(PADDRESSBOOK);
	int ReadData(PADDRESSBOOK,FILE *);
	PADDRESSBOOK ShowItemOfBook(PADDRESSBOOK);
	PADDRESSBOOK QueryByName(PADDRESSBOOK,char*);
	PADDRESSBOOK ModifyItem(PADDRESSBOOK,char*);
	PADDRESSBOOK AppendItem(PADDRESSBOOK);
	PADDRESSBOOK DeleteItem(PADDRESSBOOK,char*);
#endif
