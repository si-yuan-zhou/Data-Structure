#include <stdio.h>
#include <stdlib.h>
#include <conio.h>//C语言图形函数
typedef struct{
	long lNum;//long integer to storage student ID
	char strName[20];//string arrary to storage student name
	char chSex;//m is male and f is female
	int iScore[4];//integer arrary to storage three subjects scores and average score
}STUDENTINFO;
#define NUM 3
int UserScreen(void);//The no-parameters function means that you can define it arbitrary type and numers function in c language 
void Bell(void);
void ReadData(STUDENTINFO *);
int FunctionSelection(void);
void ScoreStatistic(STUDENTINFO *,int *,int);
void ScoreSort(STUDENTINFO *,int);
void PrintMessage(STUDENTINFO *,int);
