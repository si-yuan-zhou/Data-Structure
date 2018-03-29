#include <iostream>
#include <stdlib.h>
using namespace std;
#include "BinaryTree.h"
int main(int argc, char const *argv[])
{
	int MainMenu = -1;
	BinaryTree<int> T;
	BinaryTree<int> t;
	while (MainMenu != 6) {
		system("cls");
		cout <<"---------------- MainMenu ------------------"<<endl;
		cout <<"    1- Create BinaryTree(type is int)\n";
		cout <<"    2- Display in tree-shape\n";
		cout <<"    3- Get information of BiTree >>[SubMenu]\n";
		cout <<"    4- Operation of BiTree       >>[SubMenu]\n";
		cout <<"    5- Traverse BiTree           >>[SubMenu]\n";
		cout <<"    6- Exit\n";
		cout <<"--------------------------------------------"<<endl;
		cout <<"  Please choose:[ ]";
		cout <<"\b\b";
		cin  >> MainMenu;
		switch (MainMenu){
			case 1: 
				T.CreateBTree(-1);
				break;
			case 2: 
				cout << "This is a tree that turn 90 degree to left" <<endl;
				T.DisplayBTreeShape(T.GetRoot());
				cout << endl;
				system("pause");
				break;
			case 3:
				int op;
				do{
					system("cls");
					cout << "-----------2--Get information---------------"<<endl;
					cout << "    0--Return MainMenu"<<endl;
					cout << "    1--Get value of Root Node"<<endl;
					cout << "    2--IsEmpty"<<endl;
					cout << "    3--Caculate Depth"<<endl;
					cout << "    4--Parent Node"<<endl;
					cout << "    5--Value of Left Node"<<endl;
					cout << "    6--Value of Right Node"<<endl;
					cout << "    7--Left Sibling value"<<endl;
					cout << "    8--Right Sibling value"<<endl;
					cout << "    9--Number of leaves"<<endl;
					cout << "    10-Display in tree-shape"<<endl;
					cout << "--------------------------------------------"<<endl;
					cout << "    Please choose:[  ]";
					cout << "\b\b\b";
					cin  >> op;
					switch (op){
						case 1:
							int root;
							if (T.RootValue(root) == true)
								cout <<"Root Value: "<< root <<endl;
							else
								cout <<"BinaryTree is empty";
							system("pause");
							break;
						case 2:
							if(T.IsEmpty() == true)
								cout <<"BinaryTree is empty"<<endl;
							else
								cout <<"Not empty"<<endl;
							system("pause");
							break;
						case 3:
							cout <<"Depth is "<<T.BTreeDepth()<<endl;
							system("pause");
							break;
						case 4:
							cout <<"Please input value:[   ]";
							cout <<"\b\b\b";
							int node1;
							cin  >>node1;
							cout <<"Parent is "<<T.GetParent(node1)<<endl;
							system("pause");
							break;
						case 5:
					    	cout <<"Please input value :";
					    	int node2;
					    	cin  >>node2;
					    	cout <<"The Left node of this node is "<<T.GetLeftChild(node2)<<endl;
					    	system("pause");
							break;
						case 6:
							cout <<"Please input value :";
							int node3;
							cin  >>node3;
							cout <<"The Right node of this node is "<<T.GetRightChild(node3)<<endl;
							system("pause");
							break;
						case 7:
							cout <<"Please input value :";
							int node4;
							cin  >>node4;
							cout <<"The LeftSibling node of this node is "<<T.GetLeftSibling(node4)<<endl;
							system("pause");
							break;
						case 8:
							cout <<"Please input value :";
							int node5;
							cin  >>node5;
							cout <<"The RightSibling node of this node is "<<T.GetLeftSibling(node5)<<endl;
							system("pause");
							break;
						case 9:
							cout <<"Number of leaves:"<<T.LeafCount()<<endl;
							system("pause");
							break;
						case 10:
							T.DisplayBTreeShape(T.GetRoot());
							cout <<endl;
							system("pause");
							break;
						default:
							break;
					}
				}while(op != 0);
				break;
			case 4:
				int op2;
				do {
					system("cls");
					cout<<"--------3--Operation of BinaryTree----------"<<endl;
					cout<<"    0--Return MainMenu"<<endl;
					cout<<"    1--Destory BinaryTree"<<endl;
					cout<<"    2--Assign to specify node"<<endl;
					cout<<"    3--Insert"<<endl;
					cout<<"    4--Delete"<<endl;
					cout<<"    5--Display"<<endl;
					cout<<"--------------------------------------------"<<endl;
					cout<<"    Please choose:[ ]";
					cout<<"\b\b";
					cin>>op2;
					switch(op2){
						case 1:
							T.ClearBTree();
							cout<<"BTree has been destory!"<<endl;
							system("pause");
							break;
						case 2:
							int ChangeValue;//value need to change
							int NewValue;	//value after changing
							cout<<"Please input value needed to change:";
							cin >>ChangeValue;
							cout<<"Please input value after changing:";
							cin >>NewValue;
							if(T.SearchNode(ChangeValue)){
								(T.SearchNode(ChangeValue))->data = NewValue;
								cout<<"Change Successfully"<<endl;
							} else  {
								cout <<"Change Falsely"<<endl;
							}
							system("pause");
							break;
						case 3:
							cout <<"Please create a BTree without right subtree:\n"<<endl;
							t.CreateBTree(-1);
							cout <<"Please input the value where you want to insert"<<endl;
							int invalue;
							cin  >>invalue;
							cout <<"Insert left subtree(0) OR right subtree(1)";
							int lr;
							cin  >>lr;
							if(T.SearchNode(invalue) && t.GetRoot() && (t.GetRoot()->rchild)==NULL){
								t.InsertChild(T.SearchNode(invalue),t.GetRoot(),lr);
								cout <<"Successful"<<endl;
//								cout <<"After operating---"<<endl;
//								t.PreTraBTree();
							} else {
								cout <<"False"<<endl;
							}
							system("pause");
							break;
						case 4:
							cout <<"Please input value of node:";
							int mm;
							cin >>mm;
							cout <<"Delete Left(0),Right(1)"<<endl;
							int tag;
							cin  >>tag;
							if(T.SearchNode(mm)){
								T.DeleteChild(T.SearchNode(mm),tag);
								cout <<"Successful"<<endl;
							} else
								cout << "False"<<endl;
							T.PreTraBTree();
							system("pause");
							break;
						case 5:
							T.DisplayBTreeShape(T.GetRoot());
							cout <<endl;
							system("pause");
							break;
					}
				} while(op2 != 0);
				break;
			case 5:
				int op3;
				do{
					system("cls");
					cout<<"-----------4--Traverse BinaryTree-----------"<<endl;
					cout<<"    0--Return MainMenu"<<endl;
					cout<<"    1--Preorder  Traverse(R)"<<endl;
					cout<<"    2--Inorder   Traverse(R)"<<endl;
					cout<<"    3--Postorder Traverse(R)"<<endl;
					cout<<"    4--Preorder  Traverse(N)"<<endl;
					cout<<"    5--Inorder   Traverse(N)"<<endl;
					cout<<"    6--Level     Traverse   "<<endl;
					cout<<"--------------------------------------------"<<endl;
					cout<<"    Please choose:[  ]";
					cout<<"\b\b";
					cin>>op3;
					switch(op3){
						case 1:
							T.PreTraBTree();
							system("pause");
							break;
						case 2:
							T.InTraBTree();
							system("pause");
							break;
						case 3:
							T.PostTraBTree();
							system("pause");
							break;
						case 4:
							T.PreTraBTree_N();
							system("pause");
							break;
						case 5:
							T.InTraBTree_N();
							system("pause");
							break;
						case 6:
							T.LevelTraBTree();
							system("pause");
							break;
						default:break;	
					}	
				}while(op3 != 0);
				break;
			case 6:
				cout <<"Bye-Bye"<<endl;
				break;
			default:
				break;
			}
		}
	return 0;
}
