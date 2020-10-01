
#include<stdlib.h>
#include<string.h> 
#include<stdio.h>
#include<time.h>
double time_taken;
clock_t start,end; 
int partition(int arr[], int l, int r, int k); 
int kthSmallest(int arr[], int l, int r, int k); 
void swap(int *a, int *b) 
{ 
	int temp = *a; 
	*a = *b; 
	*b = temp; 
} 
void quickSort(int arr[], int l, int h) 
{ start=clock();
	if (l < h) 
	{ 
		
		int n = h-l+1; 

		 
		int med = kthSmallest(arr, l, h, n/2); 

		
		int p = partition(arr, l, h, med); 

		 
		quickSort(arr, l, p - 1); 
		quickSort(arr, p + 1, h); 
	} 
	::end=clock();
} 


int findMedian(int arr[], int n) 
{ 
	int i, j;  
    for (i = 0; i < n-1; i++) 
	{    
    for (j = 0; j < n-i-1; j++)
	{  
        if (arr[j] > arr[j+1])
		{  
            swap(&arr[j], &arr[j+1]);
		}
	}
}
	return arr[n/2];  
} 

int kthSmallest(int arr[], int l, int r, int k) 
{ 
	
	if (k > 0 && k <= r - l + 1) 
	{ 
		int n = r-l+1;  
		int i, median[(n+4)/5];  
		for (i=0; i<n/5; i++) 
			median[i] = findMedian(arr+l+i*5, 5); 
		if (i*5 < n)  
		{ 
			median[i] = findMedian(arr+l+i*5, n%5); 
			i++; 
		} 

		int medOfMed = (i == 1)? median[i-1]: 
								kthSmallest(median, 0, i-1, i/2); 


		int pos = partition(arr, l, r, medOfMed); 
	
		if (pos-l == k-1) 
			return arr[pos]; 
		if (pos-l > k-1) 
			return kthSmallest(arr, l, pos-1, k); 
		return kthSmallest(arr, pos+1, r, k-pos+l-1); 
	} 

	return INT_MAX; 
} 


int partition(int arr[], int l, int r, int x) 
{ 
	int i; 
	for (i=l; i<r; i++) 
		if (arr[i] == x) 
		break; 
	swap(&arr[i], &arr[r]); 
	i = l; 
	for (int j = l; j <= r - 1; j++) 
	{ 
		if (arr[j] <= x) 
		{ 
			swap(&arr[i], &arr[j]); 
			i++; 
		} 
	} 
	swap(&arr[i], &arr[r]); 
	return i; 
} 
void printArray(int arr[], int size) 
{ 
	int i; 
	for (i=0; i < size; i++)
	{
		if(i<size-1) 
			printf("%d <=",arr[i]); 
		else
			printf("%d",arr[i]);
	}
	printf("\n");
} 
int main() 
{ 
	int arr[1000];
	printf("ORIGINAL ARRAY: \n\n");
	for (int i=0;i<1000;i++)
	{
				
		//FOR 10 ELEMENTS:
		/* arr[i]=rand()%10+1;
		i<9?cout<<arr[i]<<", ":cout<<arr[i]; */
		
		
		//FOR 100 ELEMENTS:
		/* arr[i]=rand()%100+1;
		i<99?cout<<arr[i]<<", ":cout<<arr[i]; */
		
		
		//FOR 500 ELEMENTS:
		/* arr[i]=rand()%500+1;
		i<499?cout<<arr[i]<<", ":cout<<arr[i]; */
		
		
		//FOR 1000 ELEMENTS:
		arr[i]=rand()%1000+1;
		i<999?printf("%d, ",arr[i]):printf("%d",arr[i]);
		
		
		//FOR 5000 ELEMENTS:
		/* arr[i]=rand()%5000+1;
		i<4999?cout<<arr[i]<<", ":cout<<arr[i]; */
		
		
		//FOR 10000 ELEMENTS:
		/* arr[i]=rand()%10000+1;
		i<9999?cout<<arr[i]<<", ":cout<<arr[i]; */
		
		
		
	}
	
	int n = sizeof(arr) / sizeof(arr[0]); 
	quickSort(arr, 0, n - 1); 
	time_taken= (::end-start)/double(CLOCKS_PER_SEC);
	printf("\n\nSORTED ARRAY: \n\n"); 
	printArray(arr, n);
	printf("TIME TAKEN = %d sec",::end); 
	return 0; 
} 
