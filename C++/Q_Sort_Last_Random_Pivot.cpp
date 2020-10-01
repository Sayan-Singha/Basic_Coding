/* C implementation QuickSort */
#include<iostream>
#include<time.h>
#include<iomanip>
#include<stdlib.h> 

using namespace std;

// A utility function to swap two elements 
void swap(int* a, int* b) 
{ 
	int t = *a; 
	*a = *b; 
	*b = t; 
} 

double time_taken;
clock_t start,end;

/* This function takes the pivot, places the pivot element at its correct position in sorted array, 
and places all smaller (smaller than pivot) to left of pivot 
and all greater elements to right of pivot */
void printArray(int *, int);
int partition (int arr[], int low, int piIndex) 
{ 
	int pivot = arr[piIndex]; 
	int i = (low - 1); // Index of smaller element 

	for (int j = low; j <= piIndex- 1; j++) 
	{ 
		// If current element is smaller than or equal to pivot
		if (arr[j] <= pivot) 
		{ 
			i++; // increment index of smaller element 
			swap(&arr[i], &arr[j]); 
		} 
	} 
	swap(&arr[i + 1], &arr[piIndex]); 
	return (i + 1); 
}


// Utility function to decide the partitioning method
int partIndexing(int arr[], int low,int high)
{
	  ////////////////////////////////////////////////////////////
	 // COMMENT OUT THE METHODS THAT ARE NOT NEEDED TO BE USED //
	////////////////////////////////////////////////////////////
	
	srand(time(0));
	// Last index as the pivot index
		//returns high directly
	
	// Random index as the pivot index
	/*int random=low+rand()%(high-low+1);
	swap(&arr[random], &arr[high]);*/
	
	return high;
}

/* The main function that implements QuickSort 
arr[] --> Array to be sorted, 
low --> Starting index, 
high --> Ending index */
void quickSort(int arr[], int low, int high) 
{ 
start = clock();
	if (low < high) 
	{ 
		
		// partition (ARR,p,index_of_pivot)
		int pi = partition(arr, low, partIndexing(arr,low,high)); 		// Last element as the Pivot

		quickSort(arr, low, pi - 1); 
		quickSort(arr, pi + 1, high); 
	} 
	::end = clock();
} 

/* Function to print an array */
void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++)
	{
		if(i<size-1) 
			cout<<arr[i]<<" <= "; 
		else
			cout<<arr[i];
	}
	cout<<endl;
} 

// Driver program to test above functions 
int main() 
{ 
	//srand(time(0));
	int arr[1000];
	cout<<"Original Array:-\n";
	for (int i=0;i<1000;i++)
	{
		//cout<<"i="<<i<<"\t";
		
		
		// 10 ELEMENTS
		/*arr[i]=rand()%10+1;
		i<9?cout<<arr[i]<<", ":cout<<arr[i];*/
		
		
		// 100 ELEMENTS
		/*arr[i]=rand()%100+1;
		i<99?cout<<arr[i]<<", ":cout<<arr[i];*/
		
		
		// 500 ELEMENTS
		/*arr[i]=rand()%500+1;
		i<499?cout<<arr[i]<<", ":cout<<arr[i];*/
		
		
		// 1000 ELEMENTS
		arr[i]=rand()%1000+1;
		i<999?cout<<arr[i]<<", ":cout<<arr[i];
		
		
		// 5000 ELEMENTS
		/*arr[i]=rand()%5000+1;
		i<4999?cout<<arr[i]<<", ":cout<<arr[i];*/
		
		
		// 10000 ELEMENTS
		/*arr[i]=rand()%10000+1;
		i<9999?cout<<arr[i]<<", ":cout<<arr[i];*/
		
		
		//cout<<"Rand= "<<arr[i]<<endl;
	}
	int n = sizeof(arr)/sizeof(arr[0]); 
	quickSort(arr, 0, n-1); 
	time_taken= (::end-start)/double(CLOCKS_PER_SEC);
	cout<<"\n\nSorted array:-\n"; 
	printArray(arr, n); 
	//cout<<"Time taken = "<<fixed<<time_taken<<setprecision(5);
	cout<<"Time taken = "<<::end<<"sec";
	return 0; 
} 

