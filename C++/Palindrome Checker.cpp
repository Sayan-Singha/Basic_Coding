#include<iostream>
#include<string.h>
#include<conio.h>
using namespace std;

// CLASS ADT FOR IMPLEMENTATION OF CIRCULAR QUEUE
class C_Queue
{
	public:
		Feed(char);
		Pal_Check(int);
		C_Queue(){info=0;Link=NULL;}
		~C_Queue(){info=0;Link=NULL;}
	private:
		int info;
		C_Queue *Link;
}*FRONT,*REAR;


// CLASS MEMBER FUNCTION TO FEED INFO INTO QUEUE
C_Queue::Feed(char ch)
{
	C_Queue *node=new C_Queue;
	node->info=ch;
	if(REAR==NULL)
		FRONT=node;
	else
		REAR->Link=node;
	REAR=node;
	node->Link=FRONT;
}

// FUNCTION TO CHECK FOR PLAINDROME
C_Queue::Pal_Check(int n)
{
	C_Queue *temp;
	while(FRONT->info==REAR->info)					// Checking values of front and rear for similarity (loop runs only if they are same)
	{
		FRONT=FRONT->Link;							// After check, FRONT moves on to point the immediate next node
		temp=FRONT;
		while(temp->Link!=REAR)						// REAR needs to point its previous node (the node, whose Link is REAR)
			temp=temp->Link;						// temp increases until previous node of REAR
		REAR=temp;									// REAR is assigned the location of its previous node
		if(FRONT==REAR||FRONT->Link==REAR)			// In case FRONT & REAR point to same location, or they are just next to each other, it marks the end of the queue
		{
			cout<<"Given string is a Plaindrome!";
			return 0;								// As comparison is successful till the end of the queue, termination stops and palindrome is true
		}
	}
	cout<<"Given string is not a plaindrome!";		// If control comes out of while, means some element were not matched and string is not a plaindrome
	return 0;
}

main()
{
	C_Queue ptr;
	int i;	char str[50];
	cout<<"Enter String: ";	gets(str);
	for(i=0;str[i]!='\0';i++)
		ptr.Feed(toupper(str[i]));			// Feeding character wise input to the queue, keeping the all the characters to upper case for comparison
	ptr.Pal_Check(i);						// Calling function to check for palindrome
}
