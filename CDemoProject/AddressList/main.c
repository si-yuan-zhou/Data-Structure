//主程序
#include "addressbook.h"
#include "function.c"

void main(void){
	PADDRESSBOOK pHead=NULL;
	PADDRESSBOOK pTail=NULL; 
	PADDRESSBOOK pCurr=NULL;//链表的头，尾，当前指针 
	
	int iMenuId;
	int iExitFlag=0;
	int iNewFileFlag=0;//文件存在标志 
	int iNumOfItem=0;//记录节点数，存放于文件第一项 
	int i;
	
	char szTempBuf[20]={"\0"};
	FILE *fp;
	 
	fp=fopen("addressbook.txt","rb");
	if(fp==NULL){
		iNewFileFlag=1; 
	}else{
		pHead=(PADDRESSBOOK)malloc(sizeof(ADDRESSBOOK));
		pHead->next=NULL;
		iNumOfItem=ReadData(pHead,fp);
		fclose(fp);
	}
	
	do{
		system("cls");
		printf("***************************************\n");
		printf("***     欢迎使用通讯录管理系统      ***\n");
		printf("***     系统选项：		    ***\n");
		printf("***************************************\n");
		for(i=0;i<7;i++){
			printf("\t%s\n",szpMenu[i]);
		} 
		printf("      请选择： ");
		iMenuId=SelMenuItem();
		switch(iMenuId){
			case CREATEADDRESSBOOK:
				if(iNewFileFlag==0){
					system("cls");
					printf("****通讯录不存在，按任意键返回，选择选项****\n");
					getchar(); 
				}else{
					system("cls");
					printf("**************输入通讯录*****************\n");
					pHead=(PADDRESSBOOK)malloc(sizeof(ADDRESSBOOK));
					pHead->next=NULL;
					iNumOfItem=CreateAddressBook(pHead);
					iNewFileFlag=0; 
				}
				break;
				
			case SHOWADDRESSBOOK:
				if(iNewFileFlag==1){
					system("cls");
					printf("****通讯录不存在，按任意键返回！*****\n");
					getchar();
				}else{
					pCurr=pHead->next;
					system("cls");
					printf("姓    名     移动电话号码    固定电话号码\n");
					for(i=0;i<iNumOfItem;i++){
						ShowItemOfBook(pCurr);
						pCurr=pCurr->next; 
					}
					printf("按任意键返回！");
					getchar();
				}
				break;
			
			case QUERYADDRESSBOOK:
				if(iNewFileFlag==1){
					system("cls");
					printf("*****通讯录不存在，按任意键返回！*****\n");
					getchar();
					break;
				}else{
					pCurr=pHead->next;
					system("cls");
					printf("*********查询姓名：*************\n");
					printf("输入姓名：");
					gets(szTempBuf);
					pCurr=QueryByName(pCurr,szTempBuf);
					if(pCurr==NULL){
						printf("查无此人，按任意返回");
					}else{
						printf("姓名：%-s  移动电话号码：%-s  固定电话号码：%-s\n",pCurr->szName,pCurr->szMobil,pCurr->szTel);
						printf("按任意键返回！");	
					} 
				}
				getchar();
				break;
				
			case MODIFYADDRESSBOOK:
				if(iNewFileFlag==1){
					system("cls");
					printf("*****通讯录不存在，按任意键返回*****\n");
					getchar();
					break;
				}else{
					pCurr=pHead->next;
					system("cls");
					printf("************修改号码****************\n");
					printf("输入要修改的姓名：");
					gets(szTempBuf);
					pCurr=ModifyItem(pCurr,szTempBuf);
					if(pCurr==NULL){
						printf("通讯录无此人！");
					}//end of if	 
				}//end else
				printf("按任意键退出！");
				getchar();
				break;
			
			case APPENDADDRESSBOOK:
				if(iNewFileFlag==1){
					system("cls");
					printf("*****通讯录不存在，按任意键返回*****\n");
					getchar();
					break;
				}else{
					pCurr=pHead->next;
					system("cls");
					printf("************添加联系人****************\n");
					pTail=AppendItem(pCurr); 
					if(pTail==NULL){
						iNumOfItem++;
					}//end of if	 
				}//end else
				printf("按任意键退出！");
				getchar();
				break;
	
			case DELETEADDRESSBOOK:
				if(iNewFileFlag==1){
					system("cls");
					printf("*****通讯录不存在，按任意键返回*****\n");
					getchar();
					break;
				}else{
					pCurr=pHead;
					system("cls");
					printf("************删除联系人****************\n");
					printf("输入要删除人的姓名：");
					gets(szTempBuf);
					pCurr=DeleteItem(pCurr,szTempBuf);
					if(pCurr==NULL){
						printf("通讯录无此人！");
					}else{
						iNumOfItem--;
						printf("成功删除，按任意键返回！");
					}//end of else	 
				}//end else
				getchar();
				break;
 
 			case EXITADDRESSBOOK:
			 	iExitFlag=1;
				 if(iNewFileFlag==1){
					break;
				}
				fp=fopen("addressbook.txt","wb");
				if(fp==NULL){
					printf("Error! Enter and back!");
					getchar();
					break;
				}else{
					pCurr=pHead->next;
					//写入节点数
					 fwrite(&iNumOfItem,sizeof(int),1,fp);
					 while(pCurr!=NULL){
					 	fwrite(pCurr,sizeof(ADDRESSBOOK),1,fp);
					 	pTail=pCurr->next;
					 	free(pCurr);
					 	pCurr=pTail;
					 }//end while
					 fclose(fp);
				}//end of else
				break;
				
			default:
				system("cls");
				printf("*************无此选项***************\n");
				printf("             按任意键请重新选择       ");
				getchar();
				break;
		} //end switch
	}while(iExitFlag!=1);
	
	system("cls");
	printf("*************按任意键退出，谢谢使用***************\n");
	getchar();
} 


