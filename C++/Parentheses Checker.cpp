#include<iostream>
#include<conio.h>
using namespace std;


// CLASS ADT TO IMPLEMENT STACK OPERATIONS
class Stack
{
	public:
		Push(char);
		void P_Check();
		Stack()		{Link=NULL;}			// By default, Link to a new node will point to NULL (applicable for 1st node)
		~Stack()	{info=0;Link=NULL;}
	private:
		Pop();
		char info;
		Stack *Link;
		
}*TOP;


// CLASS MEMBER FUNCTION TO PUSH ELEMENTS INTO STACK
Stack::Push(char info)
{
	Stack *newnode=new Stack;	// Allocation of memory for new node
	newnode->info=info;			// Feeding of info
	if(TOP!=NULL)				// TOP!=NULL denotes stack is NOT EMPTY
		newnode->Link=TOP;		// Link of the new node points to the current TOP location (location of the previous node)
	TOP=newnode;				// Now, newnode Link points to previous node, and previous TOP points to new node
}


// CLASS MEMBER FUNCTION TO POP ELEMENTS FROM STACK
Stack::Pop()
{
	if(TOP==NULL)		// Condition for empty stack
		return 0;	
	else				// Stack is not empty
	{
		Stack *temp;
		temp=TOP;			// Storing TOP (to be deleted) in temp location
		TOP=TOP->Link;		// TOP points to Link of TOP -> location of the previous node
		delete temp;
	}
}

// MEMBER FUNCTION TO CHECK FOR PARENTHESES
void Stack::P_Check()
{
	Stack *temp=TOP;
	int flag=0,x=0,y=0;
	while(temp!=NULL)
	{
		if(temp->info=='(')
		{
			x++;					// Checking the no. of "("  in the entire expression
			if(x>y)					// If "(" comes after ")" while both being in the same no. 
				break;				// This check prevents situations like (a+b))(		--		where ( and ) are in same number, but not in proper order.
		}
		else if(temp->info==')')	// Checking the no. of ")"  in the entire expression
			y++;
		temp=temp->Link;
	}
	if(x!=y)						// If the no. of "(" and ")" don't match, then parentheses aren't properly closed.
		cout<<"Parentheses are not properly closed!";
	else
		cout<<"Parentheses are properly closed!";
}

main()
{
	Stack exp;
	char ch[20];
	cout<<"Enter the input string: "; gets(ch);		// Input of the string
	for(int i=0;ch[i]!='\0';i++)
	{
		exp.Push(ch[i]);			// Pushing string elements one by one into the stack
	}
	exp.P_Check();
}
