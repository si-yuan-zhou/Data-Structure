#include "fundeclaration.h"
#include "function.c"
int main(int argc, char const *argv[])
{
	STUDENTINFO stud[NUM];
	FILE *fp;
	int i,j,iIndex,iSubIndex,iScoreCode;
	long lNumSearch;
	char buffTmp[10];
	int iScoreSeg[5]={0};
	do{
		iIndex=UserScreen();//trabfer the userscreen
		system("cls");
		//clrscr(); clear the screen
		switch(iIndex){
			case 1:
				   printf("Please input%d students information\n\n",NUM);//input all datas
				   if((fp=fopen("Data.txt","w"))==NULL){
				   	printf("File open false ,system will exit!");
				   	exit(1);
				   }
				   for(i=0;i<NUM;i++)
				   		ReadData(stud+i);
				   fwrite(stud,sizeof(STUDENTINFO),NUM,fp);
				   fclose(fp);
				   for(i=0;i<NUM;i++)
					    PrintMessage(stud,i);
					getchar();
					break;
			case 2://change datas
					if((fp=fopen("Data.dat","r+"))==NULL){
				   	printf("File open false ,system will exit!");
				   	exit(1);
				   }
				   printf("Please input the student id which you want to change!\n");
				   gets(buffTmp);
				   lNumSearch=atol(buffTmp);//change string to long integer
				   for(i=0;i<NUM;i++)
				   		if(lNumSearch==stud[i].lNum)
				   			break;
				   	if(i<NUM)
				   		ReadData(stud+i);
				   	else
				   		printf("no this id\n");
				   	fwrite(stud,sizeof(STUDENTINFO),NUM,fp);
				   	fclose(fp);
				   	for(i=0;i<NUM;i++)
				   		PrintMessage(stud,i);
				   	getchar();
				   	break;
			case 3:
					printf("Please chose what you want:\n");
					iSubIndex=FunctionSelection();
					if((fp=fopen("Data.txt","r+"))==NULL){
				   	printf("File open false ,it maybe cause by the file was not be build ,system will exit!");
				   	exit(1);
				   }
				   fread(stud,sizeof(STUDENTINFO),NUM,fp);
				   switch(iSubIndex){
				   		case 1://statistic the people number of each score layer
				   			printf("input courses need to statistic ,1,2,3 is three courses and 4 is average score\n");
				   			gets(buffTmp);
				   			iScoreCode=atoi(buffTmp)-1;//将字符串转换成整型数
							ScoreStatistic(stud,iScoreSeg,iScoreCode);
							if(iScoreCode>0&&iScoreCode<3){
								printf("The number of each score layer in number %d class: \n",iScoreCode+1);
								printf("Up 90 is :\t%-5d\n",iScoreSeg[0]);
								printf("80 to 89 is :\t%-5d\n",iScoreSeg[1]);
								printf("70 to 79 is :\t%-5d\n",iScoreSeg[2]);
								printf("60 to 69 is :\t%-5d\n",iScoreSeg[3]);
								printf("Disqualified number:\t%-5d\n",iScoreSeg[4]);
							}else{
								printf("The number of average score in each layer\n:");
								printf("Up 90 is :\t%-5d\n",iScoreSeg[0]);
								printf("80 to 89 is :\t%-5d\n",iScoreSeg[1]);
								printf("70 to 79 is :\t%-5d\n",iScoreSeg[2]);
								printf("60 to 69 is :\t%-5d\n",iScoreSeg[3]);
								printf("Disqualified number:\t%-5d\n",iScoreSeg[4]);
							}
							break;
						case 2://sort all courses
								printf("Please input the class you want to sort,1 2 3 is three classes and 4 is average score\n");
								gets(buffTmp);
								iScoreCode=atoi(buffTmp)-1;
								ScoreSort(stud,iScoreCode);
								for(i=0;i<NUM;i++)
									PrintMessage(stud,i);
								break;
						case 3://find by inputed bunber
							printf("Please input the student id you want to find%d:\n",NUM);
							gets(buffTmp);
							lNumSearch=atol(buffTmp);
							for(i=0;i<NUM;i++)
								if(lNumSearch==stud[i].lNum)
									break;
								if(i<=NUM)
									PrintMessage(stud,i);
								else
									printf("no id\n");
								getchar();
								fclose(fp);
								break;
				   }
			case 4:return 0;//exit ststem
		}
	}while(iIndex!=4);
	return 0;
}

