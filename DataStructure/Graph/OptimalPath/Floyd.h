#ifndef __FLOYD__
#define __FLOYD__

//一对顶点之间最短路径
#define MAX_VERTEX_NUM 20
const int infinity = 100;

struct ArcCell{
	int adj;
	char *info;
};
template <class T>
struct _MGraph{
	T vertexs[MAX_VERTEX_NUM];
	ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
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
		void ShortestPath_Floyd(PathMatrix2 &P,ShortPathTable &D);
};
template <class T>
void ShortestPath_Floyd(PathMatrix2 &P,ShortPathTable &D){
	//用Floyd算法求有向网G各对结点v和w之间的最短路径，P[v][w]及带权长度D[v][w]
	//P[v][w][u]为true,则u是从v到w当前求得最短路径上的顶点
	for(int v = 0;v < mgraph.vexnum; ++v){
		//各结点之间初始已知路径及距离
		for(int w = 0;w < mgraph.vexnum; ++w){
			D[v][w] = mgraph.arcs[v][w].adj;//顶点v到w的直接距离
			for(int u = 0;u < mgraph.vexnum; ++u){
				P[v][w][u] = false;//路径矩阵初值
			}//endfor
			if(D[v][w] < infinity)//从v到w的直接距离
				P[v][w][v] = P[v][w][w] = true;//由v到w的路径经过v和w
		}//endfor
	}//endfor
	for(int u = 0;u < mgraph.vexnum; ++u){
		for(int v = 0;v < mgraph.vexnum; ++v){
			for(int w = 0;w < mgraph.vexnum; ++w){
				if(D[v][u] + D[u][w] < D[v][w]){
					//从v经u到w的一条路径更短
					D[v][w] = D[v][u] + D[u][w];//更新最短距离
					for(int i = 0;i < mgraph.vexnum; ++i){
						P[v][w][i] = P[v][u][i] || P[u][w][i];
					}//endfor
					//从v到w的路径经过从v到u和从u到w的所有路径
				}
			}//endfor
		}//endfor
	}//endfor
}
#endif
