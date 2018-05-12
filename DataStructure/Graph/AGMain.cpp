#include <iostream>
#include <string>
using namespace std;
#include "./ArrayGraph.h"

void showOper(){
	cout << endl;
	cout << "*********************************************************"<<endl;
	cout << "0.-----Create Graph" <<endl;
	cout << "1.-----Return the index of v" <<endl;
	cout << "2.-----Return value of wnated position" <<endl;
	cout << "3.-----Change the value of a vertex" <<endl;
	cout << "4.-----Add new node in graph" <<endl;
	cout << "5.-----Delete vertex v and related arcs or edges" <<endl;
	cout << "6.-----Add a new arc from v to w" <<endl;
	cout << "7.-----Delete a arc from v to w" <<endl;
	cout << "8.-----Depth-first traversal from first vertex in the graph" <<endl;
	cout << "9.-----Breadth-first traversal from first vertex in the graph"<<endl;
	cout << "10.----Display Graph" <<endl;
	cout << "11.----Destroy Graph" <<endl;
	cout << "12.----Exit" <<endl;
	cout << "*********************************************************"<<endl;
	cout << "Please enter index "; 
}

int main(int argc, char* argv[]){
	int opchoice;
	MGraph<string> g;
	g.CreateGraph();

	string str,v,value,w;
	do{
		showOper();
		cin >> opchoice;
		switch(opchoice){
			case 0:
				g.CreateGraph();
				cout << endl;
				break;
			case 1:
				cout << "Please enter the name of vertex where you wnat to query: ";
				cin >> str;
				cout << "Vertex" << str << "'s place in graph is "<<g.LocateVertex(str) << endl;
				break;
			case 2:
				int index;
				cout << "Please enter the vertex position you want to query: ";
				cin >> index;
				cout << "Postion is "<< index << "Vertex is "<< g.GetVertex(index)<< endl;
				break;
			case 3:
				cout << "Please enter the value of vertex you want to change: ";
				cin >> v;
				cout << "Please enter the new value:";
				cin >> value;
				g.PutVertex(v,value);
				cout << endl;
				break;
			case 4:
				cout << "Please enter the value of vertex you want to add: ";
				cin >> v;
				g.InsertVertex(v);
				cout << endl;
				break;
			case 5:
				cout << "Please enter the value of vertex you want to delete: ";
				cin >> v;
				g.DeleteVertex(v);
				g.Display();
				cout << endl;
				break;
			case 6:
				cout << "Please enter the two vertexs who are the breakpoints of arc you want to add:";
				cin >> v >> w;
				g.InsertArc(v,w);
				cout << endl;
				break;
			case 7:
				cout << "Please enter the two vertexs who are the breakpoints of arc you want to delete:";
				cin >> v >> w;
				g.DeleteArc(v,w);
				cout << endl;
				break;
			case 8:
				cout << "Traversal seuqence by Depth-First starting from the first vertex:"<<endl;
				g.DFSTraverse(visit);
				cout << endl;
				break;
			case 9:
				cout << "Traversal seuqence by Breadth-First starting from the first vertex:"<<endl;
				g.BFSTraverse(visit);
				cout << endl;
				break;
			case 10:
				g.Display();
				cout << endl;
				break;
			case 11:
				g.DestroyGraph();
				cout << endl;
				break;
			case 12:
				cout << "Bye-bye!"<< endl;
				break;
			default:
				cout << "Bad Operator!"<< endl;
				break;
		}//endswitch
	}while(opchoice != 12);
	return 0;
}
