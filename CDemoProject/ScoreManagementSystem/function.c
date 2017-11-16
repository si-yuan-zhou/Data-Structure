
// FunctionName:UserScreen
// function:user main menue
// parameter:users choice datas ,integer vary from 1 to 4
int UserScreen(void){
	char ch[3];
	//clsrc()
	do{
		system("cls");
		printf("1--Input all datas\n");
		printf("2--Change data\n");
		printf("3--Data process\n");
		printf("4--Exit system!\n");
		printf("Please Selection:");
		gets(ch);
		if(ch[0]>'4'||ch[0]<'1')
			Bell();
		else
			return ch[0]-'0';
	}while(ch[0]>'4'||ch[0]<'1');
}

// FunctionName:Bell
// Function:Show error message
// parameter:no
// backvalue:no

void Bell(void){
	printf("\007");//alert
}

// FunctionName:ReadData
// Function:Input pupil`s information 
// parameter:Pointer point to STUDENTINFO
// backvalue:none

void ReadData(STUDENTINFO *p){
	char strTmp[15];
	long id[NUM];
	int i,sum=0; 
	do{ 
		printf("Please Input student ID:");
		gets(strTmp);
		if(atol(strTmp)!=0){
			if((p-1)->lNum!=atol(strTmp)&&(p-2)->lNum!=atol(strTmp))
				{p->lNum=atol(strTmp);}
			else 
				printf("ID has been token!\n");
		}else{
			printf("ID can not be empty!\n");
		}
	}while(atol(strTmp)==0||(p-1)->lNum==atol(strTmp)||(p-2)->lNum==atol(strTmp));
	
	printf("Please input name:");
	gets(p->strName);
	do{
		printf("Please input sex m/f:");
		gets(strTmp);
		p->chSex=strTmp[0];
		if(strTmp[0]!='f'&&strTmp[0]!='m')
			//Bell();
			printf("illegal!\n");
			continue;
	}while(strTmp[0]!='f'&&strTmp[0]!='m');
	for(i=0;i<3;i++){
		printf("Please input the score of class number %d :",i+1);
		gets(strTmp);
		p->iScore[i]=atoi(strTmp);
		sum+=p->iScore[i];
	}
	p->iScore[3]=sum/3;
}
// FunctionName:FunctionSelection
// Function:choice process function
// parameter:no
// backvalue:data user selected, integer,vary from 1 to 3

int FunctionSelection(void){
	char ch[3];
	//clscr();
	do{
		system("cls");
		printf("1--Statistic all people of each layer\n");
		printf("2-- Sort the class selected\n");
		printf("3--Find after inputing ID\n");
		printf("Please Selection:\n");
		gets(ch);
		if(ch[0]>'3'||ch[0]<'1'){
			Bell();
		}else{
			return ch[0]-'0';
		}
	}while(ch[0]>'3'||ch[0]<'1');
}
// FunctionName:ScoreStatistic
// Function:Statistic the number of each layer
// parameter:pStu:Pointer of STUDENTINFO point to address of Score
// 		  pScore:point to integer, transmit the address of each score array
// 		  iSelCore: integer,transmit all  courses
// backvalue:none

void ScoreStatistic(STUDENTINFO *pStu,int *pScore,int iSelCore){
	int i;
	for(i=0;i<NUM;i++)
		pScore[i]=0;
	for(i=0;i<NUM;i++)
		if((pStu+i)->iScore[iSelCore]>=90)
			pScore[0]++;
		else if((pStu+i)->iScore[iSelCore]>=80)
			pScore[1]++;
		else if((pStu+i)->iScore[iSelCore]>=70)
			pScore[2]++;
		else if((pStu+i)->iScore[iSelCore]>=60)
			pScore[3]++;
		else
			pScore[4]++;
}

// FunctionName:ScoreSort
// Function:Sort courses
// parameter:pStu:point to score array address
// backvalue:none
void ScoreSort(STUDENTINFO *pStu,int iSelCore){
	int i,j;
	STUDENTINFO Temp;
	for(i=0;i<NUM;i++){
		if((pStu+i)->iScore[iSelCore]<(pStu+j)->iScore[iSelCore]){
			Temp=*(pStu+i);
			*(pStu+i)=*(pStu+j);
			*(pStu+j)=Temp;
		}
	}
}

// FunctionName:PrintMessage
// Function:print student information
// parameter:pStu:point to score
// 		  iSel,integer,the section of student in array
// backvalue:none
void PrintMessage(STUDENTINFO *pStu,int iSel){
	printf("ID:%-8d Name:%-8s Sex:%-2c Scores of three courses:%-4d %-4d %-4d Average score:%-4d\n",(pStu+iSel)->lNum,
	(pStu+iSel)->strName,(pStu+iSel)->chSex,(pStu+iSel)->iScore[0],(pStu+iSel)->iScore[1],(pStu+iSel)->iScore[2],(pStu+iSel)->iScore[3]);
}
