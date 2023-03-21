#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

void merge(int pData[], int l, int mid, int r) {

  int size1 = mid - l + 1; 
  int size2 = r - mid; 
  
  int data1[size1]; 
  int data2[size2]; 

  int i, j, k; 

  for (i = 0; i < size1; i++) {
    data1[i] = pData[l + i]; 
  }
  for (j = 0; j < size2; j++) {
    data2[j] = pData[mid + j + 1]; 
  }

  i = 0; 
  j = 0; 
  k = l; 

  while (i < size1 && j < size2) {
    if (data1[i] <= data2[j]) {
      pData[k] = data1[i]; 
      i++; 
    }
    else { 
      pData[k] = data2[j]; 
      j++; 
    }
    k++; 
  }
  while (i < size1) {
    pData[k] = data1[i]; 
    i++; 
    k++; 
  }
  while (j < size2) {
    pData[k] = data2[j]; 
    j++; 
    k++; 
  }
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r) {

  int mid; 
  
  if (l < r) {
    
    mid = (l + r)/2; 

    mergeSort(pData, l, mid);

    mergeSort(pData, mid+1, r);  

    merge(pData, l, mid, r);

  }
  
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n) { 
  
  int i, item, j;
  for (i = 1; i < n; i++) {
    item = pData[i];

    for(j = i-1; j >= 0; j--) {
      if(pData[j] > item)
        pData[j+1] = pData[j];
      else
        break;
    }
    pData[j+1] = item;
    
  }
  
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated

// A function to implement bubble sort

void bubbleSort(int* pData, int n) {

  int i, j, temp; 
  for (int i = 0; i < n-i-1; i++) {
    for (int j = 0; j < n-i-1; j++){
      if (pData[j] > pData[j+1]) {
        temp = pData[j]; 
        pData[j] = pData[j + 1]; 
        pData[j + 1] = temp; 
      }
    }
  }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n) {
	int i, j, min_idx, temp;
// One by one move boundary of unsorted subarray
  for (i = 0; i < n-1; i++) {
   
// Find the minimum element in unsorted array
    min_idx = i;
    for (j = i + 1; j < n; j++)
      if (pData[j] < pData[min_idx])
        min_idx = j;
// Swap the found minimum element with the first element
        temp = pData[i];
        pData[i] = pData[min_idx];
        pData[min_idx] = temp;
    }
}

//x parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);

    //Implement parse data block
    for (int i = 0; i < dataSz; i++) {
      fscanf(inFile, "%d", &(*ppData)[i]); 
    }
		
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}