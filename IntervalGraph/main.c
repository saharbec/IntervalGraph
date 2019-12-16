#include <stdio.h>

typedef struct interval {
	int firstIndex;
	int lastIndex;
	int degree;
	int* neighbors;
}interval;

void GreedyColoring();
void swap(interval*, interval*);
void bubbleSort(interval*, int);
int findNumberOfEdges(interval*, int, int*, int*);
interval* setIntervalArray(int);
void printFinalData(int,int, int, int);
void printIntervals(interval* , int );

void main() {
	GreedyColoring(); // Calling the function, expecting to print out all the data required.
}

void GreedyColoring() {
	int i, k, j = 0, numOfEdges, minDegree = 0, maxDegree = 0;
	interval* intervalsArr;
	printf("Please input k\n");
	scanf_s("%d", &k); // Getting the interval's family size from the user.
	intervalsArr = setIntervalArray(k);
	printIntervals(intervalsArr, k);
	numOfEdges = findNumberOfEdges(intervalsArr, k, &minDegree, &maxDegree);
	printFinalData(k, numOfEdges, maxDegree, minDegree);
}

void swap(interval *xp, interval *yp)
{
	interval temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void bubbleSort(interval* arr,int arrSize) {
	int i, j;
	for (i = 0; i < arrSize - 1; i++)
		// Last i elements are already in place  
		for (j = 0; j < arrSize - i - 1; j++) {
			if (arr[j].firstIndex > arr[j + 1].firstIndex ||
				(arr[j].firstIndex == arr[j + 1].firstIndex && arr[j].lastIndex > arr[j + 1].lastIndex)) {
				swap(&arr[j], &arr[j + 1]);
			}
		}
}

int findNumberOfEdges(interval *arr, int arrSize,int* minDeg,int* maxDeg) {
	int i, j,sumOfDegrees=0;
	for (i = 0; i < arrSize; i++) {
		for (j = 0; j < arrSize; j++) {
				if (i != j) {
					if ((arr[j].firstIndex >= arr[i].firstIndex && arr[j].firstIndex <= arr[i].lastIndex) ||
						(arr[j].lastIndex >= arr[i].firstIndex && arr[j].lastIndex <= arr[i].lastIndex) ||
						(arr[i].firstIndex >= arr[j].firstIndex && arr[i].firstIndex <= arr[j].lastIndex) ||
						(arr[i].firstIndex >= arr[j].firstIndex && arr[i].firstIndex <= arr[j].lastIndex))
					{
						arr[i].degree++;
					}
				}
			}
		sumOfDegrees += arr[i].degree;
		if (arr[i].degree > *maxDeg) *maxDeg = arr[i].degree;
		else if (arr[i].degree < *minDeg) *minDeg = arr[i].degree;
		}
	return sumOfDegrees/2;
}

interval* setIntervalArray(int size) {
	int i;
	interval* intervalsArr = (interval*)malloc(size * sizeof(interval));
	printf("You will now be asked to insert a family of %d intervals: \n", size);
	for (i = 0; i < size; i++) {
		printf("%dth interval: ", i + 1);
		scanf_s("%d%d", &intervalsArr[i].firstIndex, &intervalsArr[i].lastIndex);
		intervalsArr[i].degree = 0;
	}
	bubbleSort(intervalsArr, size);
	return intervalsArr;
}

void printFinalData(int numOfVertices, int numOfEdges, int maxDegree, int minDegree) {
	printf("G edges = %d \n", numOfEdges);
	printf("Maximum Degree of G = %d \nMinimum Degree of G = %d \n", maxDegree, minDegree);
	printf("G's Complement Edges = %d \n", (numOfVertices*(numOfVertices - 1)) / 2 - numOfEdges);
	printf("Maximum Degree of G's Complement = %d \n", numOfVertices - minDegree - 1);
	printf("Minimum Degree of G's Complement = %d \n", numOfVertices - maxDegree - 1);
}

void printIntervals(interval* intervalsArr,int size) {
	int i;
	printf("The intervals family is: \n");
	for (i = 0; i < size - 1; i++) {
		printf("[%d,%d],", intervalsArr[i].firstIndex, intervalsArr[i].lastIndex);
	}
	printf("[%d,%d] \n", intervalsArr[i].firstIndex, intervalsArr[i].lastIndex);
}
