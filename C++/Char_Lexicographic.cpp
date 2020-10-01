/*##########################################################################################################################
### PROGRAM TO READ STRING INPUT FROM A FILE AND ARRANGE THE ELEMENTS IN A LEXICOGRAPHIC MANNER INTO ANOTHER OUTPUT FILE ###
##########################################################################################################################*/

#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;

int j=0;
char tree[100], A[100], sort[100];

// UTILITY FUNCTION TO SWAP 2 GIVEN ELEMENTS
void Swap(char*a, char*b)
{
	char temp;
	temp=*a;
	*a=*b;
	*b=temp;
}

// FUNCTION TO CREATE THE HEAP STRUCTURE
void insbheap(int item)
{
	j++;
	int PTR=j;
	A[j]=item;
	int PAR;
	char temp;
	while(PTR>1)
	{
		PAR=PTR/2;
		if(A[PAR]>A[PTR])
		{
			Swap(&A[PAR],&A[PTR]);
			PTR=PAR;
		}
		else 
		return;
	}
}

// FUNCTION TO DELETE ELEMENTS FROM THE BHEAP - REQUIRED TO SORT THE ELEMENTS OF THE HEAP
char delbheap()
{
	int LAST=A[j];
	j--;
	
	int PTR=1,LEFT=2,RIGHT=3;
	char K=A[PTR];
	A[PTR]=LAST;
	while(LEFT<=j)
	{
		if((A[LEFT]>=A[PTR])&&(A[RIGHT]>=A[PTR]))
		break;
		else if(A[LEFT]<=A[RIGHT])
		{
			Swap(&A[LEFT],&A[PTR]);
			PTR=LEFT;
		}
		else
		{
			Swap(&A[RIGHT],&A[PTR]);
			PTR=RIGHT;	
		}
		LEFT=2*PTR;
		RIGHT=LEFT+1;
	}
	return K;
}


int main()
{
	int size,i,cnt=0;
	ifstream fin("TEXT.dat");
	ofstream fout("Lexi.dat");
    char ch;
    while(!fin.eof())
    {
    	fin>>tree[cnt];
    	cnt++;
    }
    tree[cnt+1]='\0';
    size=strlen(tree);
    fin.close();
	for(i=0;i<size;i++)
		insbheap(tree[i]);
	for(i=0;i<size;i++)
	{
		char item=delbheap();
		fout<<item;
		sort[i]=item;
	}
	cout<<"\n\nLexicographically arranged elemets [ignoring spaces] from the file are as follows:-\n";
	for(i=0;i<size;i++)
		cout<<sort[i]<<" ";
	return 0;
}
