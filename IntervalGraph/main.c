#include <stdio.h>

typedef struct interval {
	int firstIndex;
	int lastIndex;
	int degree;
	int color;
	struct interval** neighbors;
}interval;

void GreedyColoring();
void swap(interval*, interval*);
void sortIntervalsArray(interval*, int);
int findNumberOfEdges(interval*, int, int*, int*);
int setVerticesColors(interval*, int);
interval* setIntervalArray(int);
void printFinalData(int,int, int,int, int);
void printIntervals(interval* , int );
void findAndPrintOptimalColoring(interval* , int);
void freeAllocatedSpace(interval**,int);


void main() {
	GreedyColoring(); // Calling the function, expecting to print out all the data required.
}

void GreedyColoring() {
	int numOfIntervals, j = 0, numOfEdges, minDegree = 0, maxDegree = 0,chromaticNumber = 1;
	interval* intervalsArr;
	printf("Please input k\n");
	scanf_s("%d", &numOfIntervals); // Getting the interval's family size from the user.
	intervalsArr = setIntervalArray(numOfIntervals);
	printIntervals(intervalsArr, numOfIntervals);
	numOfEdges = findNumberOfEdges(intervalsArr, numOfIntervals, &minDegree, &maxDegree);
	chromaticNumber = setVerticesColors(intervalsArr, numOfIntervals);
	printFinalData(numOfIntervals, numOfEdges,chromaticNumber, maxDegree, minDegree);
	findAndPrintOptimalColoring(intervalsArr,numOfIntervals);
	freeAllocatedSpace(&intervalsArr, numOfIntervals);
}

void swap(interval *xp, interval *yp)
{
	interval temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void sortIntervalsArray(interval* arr,int arrSize) {
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
	int i, j,k=0,sumOfDegrees=0;
	for (i = 0; i < arrSize; i++) {
		for (j = 0; j < arrSize; j++) {
				if (i != j) {
					if ((arr[j].firstIndex >= arr[i].firstIndex && arr[j].firstIndex <= arr[i].lastIndex) ||
						(arr[j].lastIndex >= arr[i].firstIndex && arr[j].lastIndex <= arr[i].lastIndex) ||
						(arr[i].firstIndex >= arr[j].firstIndex && arr[i].firstIndex <= arr[j].lastIndex) ||
						(arr[i].firstIndex >= arr[j].firstIndex && arr[i].firstIndex <= arr[j].lastIndex))
					{
						arr[i].degree++;
						arr[i].neighbors[k] = &arr[j];
						k++;
					}
				}
			}
		k = 0;
		arr[i].neighbors = (interval**)realloc(arr[i].neighbors,arr[i].degree * sizeof(interval*));
		sumOfDegrees += arr[i].degree;
		if (arr[i].degree > *maxDeg) *maxDeg = arr[i].degree;
		else if (arr[i].degree < *minDeg) *minDeg = arr[i].degree;
		}
	return sumOfDegrees/2; // Sum of degrees divided by two(formula for number of edges)
}

int setVerticesColors(interval* intervalsArr,int size) {
	int i, j = 0,numberOfColors = 1;
	for (i = 0; i < size; i++) {
		if (intervalsArr[i].neighbors != NULL) {
			for (j = 0; j < intervalsArr[i].degree; j++) {
				// Check if a neighbor of a vertex has the same color
				if (intervalsArr[i].color == (*intervalsArr[i].neighbors[j]).color) {
					(*intervalsArr[i].neighbors[j]).color++;
					// Raise chromatic number if needed
					if ((*intervalsArr[i].neighbors[j]).color > numberOfColors)
						numberOfColors = (*intervalsArr[i].neighbors[j]).color; 
				}
			}
		}
		
	}
	return numberOfColors;
}

interval* setIntervalArray(int size) {
	int i;
	interval* intervalsArr = (interval*)malloc(size * sizeof(interval));
	printf("You will now be asked to insert a family of %d intervals: \n", size);
	for (i = 0; i < size; i++) {
		printf("%dth interval: ", i + 1);
		scanf_s("%d%d", &intervalsArr[i].firstIndex, &intervalsArr[i].lastIndex);
		intervalsArr[i].degree = 0;
		intervalsArr[i].color = 1;
		intervalsArr[i].neighbors = (interval**)malloc(size * sizeof(interval*));
	}
	sortIntervalsArray(intervalsArr, size);
	return intervalsArr;
}

void printFinalData(int numOfVertices, int numOfEdges,int chromaticNumber, int maxDegree, int minDegree) {
	printf("G edges = %d \n", numOfEdges);
	printf("Maximum Degree of G = %d \nMinimum Degree of G = %d \n", maxDegree, minDegree);
	printf("Chromatic Number of G = %d \n", chromaticNumber);
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

void findAndPrintOptimalColoring(interval* intervalsArr, int size) {
	int i, j;
	// Sort intervals by colors 
	for (i = 0; i < size - 1; i++) {
		for (j = 0; j < size - i - 1; j++) {
			if (intervalsArr[j].color > intervalsArr[j + 1].color) {
				swap(&intervalsArr[j], &intervalsArr[j + 1]);
			}
		}
	}
	//Print intervals by colors
	printf("Optional Coloring: ");
	for (i = 0; i < size; i++) { 
		if (intervalsArr[i].color != intervalsArr[i - 1].color || i == 1) printf("{");
		printf("[%d,%d]",intervalsArr[i].firstIndex,intervalsArr[i].lastIndex);
		if (i == size - 1 || intervalsArr[i].color != intervalsArr[i + 1].color) {
			printf("} = %d", intervalsArr[i].color);
		}
		if (i < size - 1) printf(", ");
	}
	printf("\n");
}

void freeAllocatedSpace(interval** arr, int size) {
	int i,j;
	for (i = 0; i < size; i++) {
		free((*arr)[i].neighbors);
	}
	free(*arr);
}