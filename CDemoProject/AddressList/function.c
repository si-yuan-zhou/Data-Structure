
/*
function:主菜单处理功能
函数名：SelMenuItem
参数：void 
返回值：int
*/
int SelMenuItem(void){
	char szBuff[10];
	gets(szBuff);
	return atoi(szBuff)-1;
}

/*
函数名：ShowItemOfBook
功能：显示一项通讯内容
参数：显示节点指针。PADDRESSBOOK 类型
返回值：下一个节点的指针， PADDRESSBOOK 类型
*/
PADDRESSBOOK ShowItemOfBook(PADDRESSBOOK p){
	printf("%10s%15s%15s\n",p->szName,p->szMobil,p->szTel);
	return p->next;
}

/*
	功能：按照名字查找
	函数名：QueryByName
	参数：链表头指针	PADDRESSBOOK 类型
			待查姓名	字符指针
	返回值： 查找地址	PADDRESSBOOK 类型 
*/
PADDRESSBOOK QueryByName(PADDRESSBOOK p,char *szpName){
	PADDRESSBOOK pQuer=NULL;
	PADDRESSBOOK pTemp=p;
	while(pTemp!=NULL){
		if(strcmp(szpName,p->szName)==0){
			pQuer=p;
			break;
		}//end if
		p=p->next;
		pTemp=p;
	}//end while
	return pQuer;
}

/*
	功能：修改指定姓名的数据
	函数名：ModifyItem
	参数：链表首地址	PADDRESSBOOK 类型
	返回值：修改项地址	PADDRESSBOOK 类型 
*/
PADDRESSBOOK ModifyItem(PADDRESSBOOK p,char*szpName){
	PADDRESSBOOK pModi;
	PADDRESSBOOK pTemp;
	char szBuff[20];
	pModi=NULL;
	pTemp=p;
	while(pTemp!=NULL){
		if(strcmp(szpName,p->szName)==0){
			pModi=p;
			printf("修改%s的通讯录\n",p->szName);
			printf("重新输入姓名：");
			gets(szBuff);
			if(szBuff[0]!='\0'){
				strcpy(p->szName,szBuff);
			}
			printf("重新输入移动电话号码：");
			gets(szBuff);
			if(szBuff[0]!='\0'){
				strcpy(p->szMobil,szBuff);
			}
			printf("重新输入固定电话号码：");
			gets(szBuff);
			if(szBuff[0]!='\0'){
				strcpy(p->szTel,szBuff);
			} 
			break;
		}
		p=p->next;
		pTemp=p;
	}//end while
	return pModi;
}

/*
	功能：在尾部添加数据
	函数名：AppendItem
	参数：头指针   PADDRESSBOOK 类型
	返回值：尾指针	PADDRESSBOOK 类型 
*/
PADDRESSBOOK AppendItem(PADDRESSBOOK p){
	PADDRESSBOOK pTail=NULL;
	//搜索尾节点
	while(p->next!=NULL){
		p=p->next;
	} //end  while
	pTail=(PADDRESSBOOK)malloc(sizeof(ADDRESSBOOK));
	p->next=pTail;
	printf("输入姓名：");
	gets(pTail->szName);
	printf("输入移动电话号码：");
	gets(pTail->szMobil);
	printf("输入固定电话号码：");
	gets(pTail->szTel);
	pTail->next=NULL;
	return pTail;	
} 

/*
	功能：删除指定姓名的数据
	函数名：DeleteItem
	参数：数据节点的头指针 	PADDRESSBOOK 类型
	返回值：删除前驱节点指针	PADDRESSBOOK 类型  
*/
PADDRESSBOOK DeleteItem(PADDRESSBOOK p,char *szpName){
	PADDRESSBOOK pCurr=NULL;
	PADDRESSBOOK pTemp=NULL;
	PADDRESSBOOK pNext=p;
	while(pNext!=NULL){
		if(strcmp(p->next->szName,szpName)==0){
			pCurr=p;
			pTemp=p->next;
			p->next=p->next->next;
			free(pTemp);
			break;
		}
		p=p->next;
		pNext=p;
	}//end while
	return pCurr;
} 

/*
	功能：从文件读数据到链表
	函数名：ReadData
	参数：链表头指针 PADDRESSBOOK类型
			文件指针	FILE* 类型
	返回值： 节点个数	int 类型 
*/
int ReadData(PADDRESSBOOK p,FILE *fp){
	PADDRESSBOOK pTail,pCurr;
	int iNum,i;
	//从文件读节点数
	fread(&iNum,sizeof(int),1,fp);
	for(i=0;i<iNum;i++){
		pTail=(PADDRESSBOOK)malloc(sizeof(ADDRESSBOOK));
		fread(pTail,sizeof(ADDRESSBOOK),1,fp);
		pCurr=pTail;
		p->next=pTail;
		p=pTail; 
	} 
	pTail->next=NULL;
	return iNum;
} 

/*
	功能：建立通讯录链表
	函数名：CreateAddressBook
	参数：链表头节点地址	PADDRESSBOOK类型
	返回值：节点数	int 类型 
*/
int CreateAddressBook(PADDRESSBOOK p){
	PADDRESSBOOK pTail=p;
	PADDRESSBOOK pCurr=p;
	int iNumOfItem=0;
	char szTempBuf[20];
	while(1){
		printf("输入姓名：");
		gets(szTempBuf);
		if(szTempBuf[0]=='\0'){
			break;
		}
		pTail=(PADDRESSBOOK)malloc(sizeof(ADDRESSBOOK));
		strcpy(pTail->szName,szTempBuf);
		printf("输入移动电话号码：");
		gets(pTail->szMobil); 
		printf("输入固定电话号码：");
		gets(pTail->szTel); 
		pCurr->next=pTail;
		iNumOfItem++;
		pTail->next=NULL;
		pCurr=pTail;
	}//end while
	return iNumOfItem;
}
