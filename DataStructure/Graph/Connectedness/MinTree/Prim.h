#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
#ifndef __PRIM__
#define __PRIM__

#define MAX_VERTEX_NUM 20	//最大顶点数
#define MAXEDGE 190			//图中最大边树
const int infinity = 100;
struct ArcCell{
	int adj;		//对无权图右1,0表示是否相邻，对带权图，则为权值类型
	char *info;		//该弧的相关信息
};
template <class T>
struct minside{
	//记录从顶点集U到顶点集V~U的代价最小的边的辅助数组定义
	T adjvex;
	int lowcost;
};
template <class T>
struct EdgeType{
	T v1,v2;
	int cost;
};
template <class T>
struct _MGraph{
	T vertexs[MAX_VERTEX_NUM];
	ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum;
	int arcnum;
	int kind;
};
template <class T>
class MGraph{
	_MGraph<T> mgraph;
	bool visited[MAX_VERTEX_NUM];
	public:
		bool CreateUDN();//创建无向图
		int Minimum(minside<T> *SZ);//求辅助数组sz中的lowcost的最小正值
		int LocateVertex(T u);//返回该顶点在图中的位置
		void Display();
		void MinSpanTree_Prim(T u);//用普里木算法从顶点ｕ开始构造网的最小生成树并输出个边
		void DestoryGraph();
};
template <class T>
void MGraph<T>::Display(){
	//输出权值的邻接矩阵
	for(int i = 0;i < mgraph.vexnum; ++i){
		for(int j = 0;j < mgraph.vexnum; ++j){
			if (mgraph.arcs[i][j].adj == infinity]) {
				cout <<setw(15)<<"INF"<<"\t";
			} else {
				cout <<setw(15)<<mgraph.arcs[i][j].adj<<"\t";
			}
		}//endfor
		cout <<endl;
	}//endfor
}
template <class T>
bool MGraph<T>::CreateUDN(){
	//构造无向图
	int w;
	T v1,v2;
	cout <<"请输入无向图的顶点个数，边的个数：";
	cin >> mgraph.vexnum >> mgraph.arcnum;
	cout << "请输入输入各个顶点";
	for(int i = 0;i < mgraph.vexnum; ++i){
		for(int j = 0;j < mgraph.vexnum; ++j){
			mgraph.arcs[i][j].adj = infinity;
			mgraph.arcs[i][j].info = false;
		}//endfor
	}//endfor
	for(int i = 0;i < mgraph.arcnum; ++i){
		cout << "请输入一条边依附的两个顶点权值";
		cin >> v1>>v2>>w;
		int m = LocateVertex(v1);
		int n = LocateVertex(v2);
		mgraph.arcs[m][n].adj = w;
		mgraph.arcs[n][m].adj = w;
	}//endfor
	mgraph.kind = 3;
	return true;
}
template <class T>
void MGraph<T>::DestoryGraph(){
	for(int i = 0;i < mgraph.vexnum; ++i){
		for(int j = 0;j < mgraph.vexnum; ++j){
			if(mgraph.arcs[i][j].info){
				delete[] mgraph.arcs[i][j].info;
				mgraph.arcs[i][j].info = mgraph.arcs[j][i].info = NULL;
			}
		}//endfor
	}//endfor
	mgraph.vexnum = 0;
	mgraph.arcnum = 0;
}
template <class T>
int MGraph<T>::LocateVertex(T u){
	for(int i = 0;i < MAX_VERTEX_NUM; ++i){
		if(u == mgraph.vertexs[i])
			return i;
	}//endfor
	return -1;
}
template <class T>
int MGraph<T>::Minimum(minside<T> SZ[MAX_VERTEX_NUM]){
	//求助数组sz中的lowcost的最小正值
	int i = 0,min,k;
	while(!SZ[i].lowcost){
		i++;
	}//endwhile
	min = SZ[i].lowcost;//找到第一个非0值
	k = i;
	for(int j = i+1;j < mgraph.vexnum; ++j){
		//在第一个非０值之后开始依次寻找较小值，并且记录位置
		if(SZ[j].lowcost > 0){
			if(min > SZ[j].lowcost){
				//找到较小值
				min = SZ[j].lowcost;
				k = j;//记录较小位置
			}
		}
	}//endfor
	return k;
}
template <class T>
void MGraph<T>::MinSpanTree_Prim(T u){
	int k;
	minside<T> closedge[MAX_VERTEX_NUM];
	k = LocateVertex(u);
	for(int j = 0;j < mgraph.vexnum; ++j){
		if(j != k){
			closedge[j].adjvex = u;
			closedge[j].lowcost = mgraph.arcs[k][j].adj;
		}
	}//endfor
	closedge[k].lowcost = 0;
	cout <<"最小生成树各个边依次是:"<<endl;
	for(int i = 1;i < mgraph.vexnum; ++i){
		k = Minimum(closedge);//求出下一个结点位置
		cout <<closedge[k].adjvex << "-" <<mgraph.vertexs[k]<<"权值: "<<closedge[k].lowcost<<endl;
		closedge[k].lowcost = 0;//将位置为k的顶点并入u集合
		for(int j = 0;i < mgraph.vexnum; ++j){
			//新顶点并如u集合，重新选择最小边
			if(mgraph.arcs[k][j].adj < closedge[j].lowcost){
				closedge[j].adjvex = mgraph.vertexs[k];
				closedge[j].lowcost = mgraph.arcs[k][j].adj;
			}
		}//endfor
	}//endfor
}
#endif
