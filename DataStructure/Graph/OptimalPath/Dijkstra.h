#ifndef __OneToOthers__
#define __OneToOthers__

//某点到其余各点的最短路径
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
		void ShortestPath_Dijkstra(int v0,PathMatrix1 &P,ShortPathTable &D);
};
template <class T>
void MGraph<T>::ShortestPath_Dijkstra(int v0,PathMatrix1 &P,ShortPathTable &D){
	//用Dijkstra算法求有向图的v0顶点到其余顶点v的最短路径P[v]及带权长度
	//D[v],若P[v][w]为true，则w是从v0到v当前求得最短路径上的顶点
	//finall[v]为true当且仅当v属于s，即已经求得从v0到v的最短路径
	int min;
	bool finall[MAX_VERTEXS_NUM];//辅助矩阵，为真表示该顶点到v0的最短距离已求出，初始值为假
	for(int v = 0;v < mgraph.vexnum; ++v){
		finall[v] = false;
		D[v] = mgraph.arcs[v0][v].adj;//D[]存放v0到v的最短距离，初始值为v0到v的直接距离
		for(int w = 0;w < mgraph.vexnum; ++w){
			P[v][w] = false;
		}//endfor
		if(D[v] < infinity){
			//v0到v有直接路径
			//一维数组p[v][]表示v0到v最短路径通过的顶点
			P[v][v0] = P[v][v] = true;
		}
	}//endfor
	D[v0] = 0;//<v0,v0> = 0
	finall[v0] = true;
	for(int i = 0;i < mgraph.vexnum; ++i){
		//其余G.vexnum-1个顶点
		//循环每次求得v0到某顶点v的最短路径，并将v并入s集
		min = infinity;//初始值
		for(int w = 0;w < mgraph.vexnum; ++w){
			if(!finall[w] && D[w] < min){
				//在s集之外的顶点中找离v0最近的顶点，并将其赋给v，距离付给min
				v = w;
				min = D[w];
			}
		}//endfor
		finall[v] = true;//离v0最近的v并入s集
		for(int w = 0;w < mgraph.vexnum; ++w){
			//根据新并入的顶点，更新不在s中的顶点到v0的距离和路径数组
			if(!finall[w] && min < infinity && mgraph.arcs[v][w].adj < infinity && (min + mgraph.arcs[v][w].adj < D[w])){
			//w不属于s集且v0->v->w的距离小于目前v0->w的距离
				D[w] = min + mgraph.arcs[v][w].adj;
				for(int j = 0;j < mgraph.vexnum; ++j){
					//修改p[w],v0到w经过的顶点包括vo到v经过的顶点再加上顶点w
					P[w][j] = P[v][j];
				}//endfor
				P[w][w] = true;
		}//endfor
	}//endfor
}
#endif
