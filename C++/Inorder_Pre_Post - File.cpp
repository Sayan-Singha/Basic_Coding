/* PROGRAM TO CONSTRUCT A COMPLETE BINARY TREE FROM GIVEN PRE ORDER AND POST ORDER */
#include <iostream>
#include <stdlib.h>
#include<fstream>
#include<conio.h>
using namespace std;

/* A binary tree node has data, pointer to left child 
and a pointer to right child */
class node 
{
	private:
		int info; 
		node *left,*right;
	public:
		node *Insert(int);
		node *Const_Tree(int*,int*,int*,int,int,int);
		node *Tree(int*,int*,int);
		void print_Inorder(node*);
}; 

// function to create a node 
node* node::Insert(int data)
{ 
	node* temp=new node;
	temp->info = data; 
	temp->left=temp->right=NULL; 
	return temp; 
} 

// recursive function to create the full binary tree from pre and post oders
node* node::Const_Tree(int pre[], int post[], int* preIndex, int l, int h, int size)
{ 
	// Base case 
	if (*preIndex >= size || l > h)
		return NULL;

	// The first node in preorder traversal is root. Using that to initialise tree 
	node* root=Insert(pre[*preIndex]); 
	++*preIndex;

	// If the current subarry has only one element, end
	if (l == h)
		return root; 

	// Search the next element of pre[] in post[] 
	int i;
	for (i=l;i<=h;i++) 
		if (pre[*preIndex]==post[i]) 
			break;

	// Dividing the post order array into 2 parts - left and right sub-trees
	if (i<=h)
	{ 
		root->left=Const_Tree(pre, post, preIndex, l, i, size);
		root->right=Const_Tree(pre, post, preIndex, i + 1, h, size);
	} 
	return root; 
} 

// Function to create the full binary tree
node* node::Tree(int pre[], int post[], int size) 
{ 
	int preIndex = 0; 
	return Const_Tree(pre, post, &preIndex, 0, size-1, size);
} 

// A function to print inorder traversal of a Binary Tree 
void node::print_Inorder(node* node)
{
	if (node==NULL) 
		return;
	print_Inorder(node->left);
	ofstream fout("Inorder.dat");
	cout<<node->info<<" ; ";
	fout<<node->info;
	fout.close();
	print_Inorder(node->right);
}

// Main function 
int main () 
{ 
	int i,x=0;
	node newnode;						// class object required to call member functions
	
	ifstream fin("PreOrder.dat");		
	if(!fin)											// if file doesn't exist
	{
		cout<<"PreOder file not found!\n[error404]";
		return 0;
	}
	while(!fin.eof())
	{
		fin>>i;									// one file (preorder) opened and run through, to get the size of the total array
		x++;
	}
	fin.close();
	
	int pre[x],post[x];							// initialising arrays with required size
	x=0;
	cout<<"PreOrder:-\n";
	fin.open("PreOrder.dat");					// opening of pre order file
	while(!fin.eof())
	{
		fin>>pre[x];							// taking elements into the preorder array
		cout<<pre[x]<<" ; ";
		x++;
	}
	fin.close();
	
	fin.open("PostOrder.dat");					// opening of post order file
	cout<<"\n\nPostOrder:-\n";
	if(!fin)									// if file doesn't exist
	{
		cout<<"PostOder file not found!\n[error404]";
		return 0;
	}
	x=0;
	while(!fin.eof())
	{
		fin>>post[x];							// taking file elements into the post order array
		cout<<post[x]<<" ; ";
		x++;
	}
	fin.close();
	x=0;
	int size=sizeof(pre)/sizeof(pre[0]);					// calculation of no. of elements (total size/size of each element)
	node *root = newnode.Tree(pre, post, size);				// calling of tree creation function
	cout<<"\n\nInorder traversal of the constructed tree:- \n";
	newnode.print_Inorder(root);							// display function
	return 0; 
} 


