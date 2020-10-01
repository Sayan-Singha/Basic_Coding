#include<iostream>
#include<fstream>
#include<conio.h>
using namespace std;

// CLASS ADT TO IMPLEMENT REQUIRED OPERATION
class Node
{
	public:
		void Node_Add(char);
		void Node_Rev();
		Node()	{prev=next=NULL;}
		~Node()	{prev=next=NULL;}
	private:
		char info;
		Node *prev, *next;
}*HEAD;

// MEMBER FUNCTION TO FEED INFORMATION INTO NODES
void Node::Node_Add(char info)
{
	Node *node=new Node;
	node->info=info;
	if(HEAD!=NULL)
	{
		node->prev=HEAD;
		HEAD->next=node;
	}
	HEAD=node;
}

// MEMBER FUNCTION TO REVERSE THE ORDER OF THE NODES AND THEIR INFO
void Node::Node_Rev()
{
	Node *temp=HEAD;
	cout<<"The reversed string is :- \n";
	ofstream out("String_Rev.dat",ios::out);		// Opening file in write mode
	while(temp!=NULL)
	{
		cout<<temp->info;				// Output the reversed string on the console
		out<<temp->info;				// Output reversed string in a new file through the output stream
		temp=temp->prev;
	}
	out.close();			// Output stream (write mode) closed
}

main()
{
	Node ptr;
	char str[50];
	ifstream in("String.dat",ios::in);		// Opening file in read mode
	while(!in.eof())
	{
		in>>str;							// Taking input of the string through input stream
		cout<<"\n\nThe original string is :- \n"<<str<<endl<<endl;		// Printing original string
		for(int i=0;str[i]!='\0';i++)
			ptr.Node_Add(str[i]);				// Sending the input string for node creation through class member function
		ptr.Node_Rev();							// Class member function called to reverse the original string and print it in new file
	}
}
