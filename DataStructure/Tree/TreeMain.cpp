#include <iostream>
#include <cstdlib>
using namespace std;
#include "Tree.h"
int main(int argc, char* argv[]){
	CTree<char> PT;
	CTree<char> c;
	int op;
	do{
		cout << "\t-----MainMenu------\t" <<endl;
		cout << "\t0--Exit" <<endl;
		cout << "\t1--Create Tree" <<endl;
		cout << "\t2--Clear Tree" <<endl;
		cout << "\t3--Whether is empty" <<endl;
		cout << "\t4--Return Depth" <<endl;
		cout << "\t5--Return Root value" <<endl;
		cout << "\t6--Return value accroding to order number" <<endl;
		cout << "\t7--Change node value" <<endl;
		cout << "\t8--Return parent value" <<endl;
		cout << "\t9--Return far left child value" <<endl;
		cout << "\t10-Return right Sibling value" <<endl;
		cout << "\t11-Output Tree" <<endl;
		cout << "\t12-Insert" <<endl;
		cout << "\t13-Delete" <<endl;
		cout << "\t14-Traverse Tree" <<endl;
		cout << "\tPlease choose:[  ]";
		cout << "\b\b\b";
		cin  >> op;
		switch(op){
			case 0:break;
			case 1:
				   PT.CreateTree('#');
				   break;
			case 2:
				   PT.ClearTree();
				   break;
			case 3: 
				   cout << (PT.IsEmpty() == true?"Tree is empty":"Not empty") << endl;
				   break;
			case 4: 
				   cout <<"Tree's depth is: " << PT.TreeDepth() << endl;
				   break;
			case 5: 
				   if (PT.Root() == 0) {
						cout << "Tree is empty" << endl;
				   } else {
						cout << "Root node value is: "<<PT.Root() <<endl;
				   }
				   break;
			case 6: 
				   cout << "Please input order of node: ";
				   int index;
				   cin >> index;
				   if(PT.Value(index) != 0) {
						cout << "Order number "<< index <<"'s value is "<<PT.Value(index)<<endl;
				   } else {
						cout << "Bad order number!" << endl;
				   }
				   break;
			case 7: 
				   char cur_e;
				   cout << "Please input what you want to change: ";
				   cin  >> cur_e;
				   char value;
				   cin  >> value;
				   if (PT.Assign(cur_e,value) == true) {
						cout << "Successfuly" << endl;
				   } else {
						cout << "Fail" << endl;
				   }
				   break;
			case 8: 
				   char cur_e2;
				   cout << "Please input node value: ";
				   cin  >> cur_e2;
				   if (PT.parent(cur_e2) == 0) {
						cout << "This node isn't exsit or it's root node";
				   } else {
						cout << "Parents of the node is "<< PT.parent(cur_e2) <<endl;
				   }
				   break;
			case 9: 
				   char cur_e3;
				   cout << "Please input value of node: ";
				   cin  >> cur_e3;
				   if (PT.LeftChild(cur_e3)) {
						cout << "Node "<< cur_e3 <<"'s far left node is: "<< PT.LeftChild(cur_e3)<<endl;
				   } else {
						cout << "Is leaf node or not exist";
				   }
				   break;
			case 10: 
				   char cur_e4;
				   cout << "Please input value of node: ";
				   cin  >> cur_e4;
				   if (PT.RightSibling(cur_e4)) {
						cout << "Right Sibling of this node is: " << PT.RightSibling(cur_e4) << endl;
				   } else {
						cout << "Not exist or have no right siblings"<< endl;
				   }
				   break;
			case 11: 
				   PT.Print();
				   break;
			case 12: 
				   c.CreateTree('#');
				   cout << "Insert c into current tree: input insert position and parent value of this place: ";
				   int insertPos;
				   char p;
				   cin  >> insertPos >> p;
				   PT.InsertChild(p,insertPos,c.GetTree());
				   break;
			case 13: 
				   char par;
				   cout <<"Please input the node's parent's value that you want to delete: ";
				   cin  >> par;
				   cout <<"Please input subtree sequence to be deleted: ";
				   int pos;
				   cin  >> pos;
				   PT.DeleteChild(par,pos);
				   break;
			case 14: 
				   PT.TraverseTree();
				   break;
			default:break;
		}//endswitch
	}while(op != 0);
	return 0;
}
