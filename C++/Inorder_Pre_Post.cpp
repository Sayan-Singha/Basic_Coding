/* PROGRAM TO CONSTRUCT A COMPLETE BINARY TREE FROM GIVEN PRE ORDER AND POST ORDER */
#include <iostream>
#include <stdlib.h>
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
	cout<<node->info<<" ; ";
	print_Inorder(node->right);
}

// Main function 
int main () 
{ 
	int i,x;
	node newnode;
	cout<<"How many elements do you want to enter?: ";
	cin>>x;
	int pre[x],post[x];
	cout<<"\nEnter Pre order:- \n";
	for(i=0;i<x;i++)
	{
		cout<<"Element "<<i+1<<": ";
		cin>>pre[i];
	}
	cout<<"\nEnter Post order:- \n";
	for(i=0;i<x;i++)
	{
		cout<<"Element "<<i+1<<": ";
		cin>>post[i];
	}
	//int pre[] = {1, 2, 4, 8, 9, 5, 3, 6, 7}; 
	//int post[] = {8, 9, 4, 5, 2, 6, 7, 3, 1}; 
	int size=sizeof( pre )/sizeof(pre[0]);
	node *root = newnode.Tree(pre, post, size);
	cout<<"Inorder traversal of the constructed tree: \n";
	newnode.print_Inorder(root);

	return 0; 
} 


