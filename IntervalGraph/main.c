#include <stdio.h>

void GreedyColoring();
void bubbleSort(int*, int);
void swap(int*, int*);
int findNumberOfEdges(int*, int,int*,int*);

void main() {
	GreedyColoring(); // Calling the function, expecting to print out all the data required.
}

void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void bubbleSort(int* arr,int arrSize) {
	int i, j;
	for (i = 0; i < arrSize - 2; i= i+2)
		// Last i elements are already in place  
		for (j = 0; j < arrSize - i - 2; j=j+2)
			if (arr[j] > arr[j + 2] || (arr[j] == arr[j+2] && arr[j+1]  > arr[j+3])) {
				swap(&arr[j], &arr[j + 2]);
				swap(&arr[j + 1], &arr[j + 3]);
			}

}

int findNumberOfEdges(int *arr, int arrSize,int* minDeg,int* maxDeg) {
	int i, j;
	for (i = 2; i < arrSize; i = i + 2) {
		if ((arr[i] >= arr[0] && arr[i] <= arr[1]) || (arr[i + 1] >= arr[0] && arr[i + 1] <= arr[1])) {
			(*minDeg)++;
			(*maxDeg)++;
		}
	}

}

void GreedyColoring() {
	int i, k, j = 0, numOfEdges, *intervalsArr,minDegree = 0,maxDegree = 0;
	printf("Please input k\n");
	scanf_s("%d", &k); // Getting the interval's family size from the user.
	intervalsArr = (int*)calloc(2 * k * sizeof(int));
	printf("You will now be asked to insert a family of %d intervals: \n", k);
	for (i = 0; i < k; i++,j=j+2) {
		printf("%dth interval: ", i + 1);
		scanf_s("%d%d", &intervalsArr[j],&intervalsArr[j+1]);
	}
	bubbleSort( intervalsArr,k * 2);
	printf("The intervals family is: \n");
	j = 0;
	for (i = 0; i < k-1; i++,j=j+2) {
		printf("[%d,%d],", intervalsArr[j], intervalsArr[j+1]);
	}
	printf("[%d,%d] \n", intervalsArr[j], intervalsArr[j+1]);
	numOfEdges = findNumberOfEdges(intervalsArr, k * 2,&minDegree,&maxDegree);
	printf("Min: %d, Max:%d", minDegree, maxDegree);
}