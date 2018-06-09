#ifndef __OneToOthers__
#define __OneToOthers__

#include "ArrayGraph.h"
struct ArcCell{
	int adj;	//对无权图由1,0表示是否相邻，对带权图，则表示权值类型
	char *info;
};
template <class T>
struct _MGraph{
	T vertexs[MAX_VERTEXS_NUM];
	ArcCell arcs[MAX_VERTEXS_NUM][MAX_VERTEXS_NUM];
	int vexnum;
	int arcnum;
	int kind;
};

typedef int PathMatrix1[MAX_VERTEXS_NUM][MAX_VERTEXS_NUM];//路径矩阵，二维数组
typedef int ShortPathTable[MAX_VERTEXS_NUM];//最短距离表，一维数组
typedef int PathMatrix2[MAX_VERTEXS_NUM][MAX_VERTEXS_NUM][MAX_VERTEXS_NUM];
typedef int DistanceMatrix[MAX_VERTEXS_NUM][MAX_VERTEXS_NUM];

template <class T>
class MGraph{
	public:
		_MGraph<T> mgraph;
		bool visited[MAX_VERTEXS_NUM];
		void CreateGraph();
		void DestroyGraph();
		int LocateVex(T u);
		bool CreateDN();//有向图
		bool CreateUDN();//无向图
		bool (*VisitFunc)(T v);//访问结点方式
		void Display();
		void ShortestPath(int v0,PathMatrix1 &P,ShortPathTable &D);
};

#endif
