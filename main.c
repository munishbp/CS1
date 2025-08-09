#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <limits.h>

#define MAX_STORES 16

typedef struct Store {
    char name[20];
    int x;
    int y;
} Store;

Store storeArray[MAX_STORES];  // array to hold store information
int array[MAX_STORES] = {-1};  // array to store the optimal order of store pairs

// Function prototypes
void permutations(int* perm, int* used, int k, int n, double currentDistance, double* minDistance, double** distanceMatrix);
void calculateDistances(int n, double** distanceMatrix);
double calculateDistance(int a, int b);
double** initializeDistanceMatrix(int size);
void freeDistanceMatrix(double** distanceMatrix, int size);
void printResult(int n, double** distanceMatrix);

// Function to allocate memory for distance matrix
double** initializeDistanceMatrix(int size) {
    double** matrix = (double**)malloc(size * sizeof(double*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (double*)malloc(size * sizeof(double));
    }
    return matrix;
}

// Function to free memory allocated for distance matrix
void freeDistanceMatrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Recursive function to find permutations of store pairs and calculate minimum distance
void permutations(int* perm, int* used, int k, int n, double currentDistance, double* minDistance, double** distanceMatrix) {
    int cnt = 2 * n;
    // base case: if all pairs have been chosen
    if (k == cnt) {
        // check if current permutation yields a smaller distance
        if (currentDistance < *minDistance) {
            *minDistance = currentDistance;
            memcpy(array, perm, cnt * sizeof(int));  // store the current permutation
        }
        return;
    }

    // alternate between selecting the first store in a pair and the second
    if (k % 2 == 0) {
        // choose the first store in the pair
        for (int i = 0; i < cnt; i++) {
            if (!used[i]) {
                used[i] = 1;          // mark the store as used
                perm[k] = i;          // record the index of the chosen store
                permutations(perm, used, k + 1, n, currentDistance, minDistance, distanceMatrix);
                used[i] = 0;          // backtrack: mark the store as unused
                break;                // only need to choose one store for the first in pair
            }
        }
    } else {
        // choose the second store in the pair
        int prev = perm[k - 1];        // previous store chosen in the current pair
        for (int i = 0; i < cnt; i++) {
            if (!used[i]) {
                double additionalDistance = distanceMatrix[prev][i];  // distance between the current and previous stores
                double newDist = currentDistance + additionalDistance;  // update total distance
                // only continue if the new distance is less than the current minimum
                if (newDist >= *minDistance) continue;
                used[i] = 1;          // mark the store as used
                perm[k] = i;          // record the index of the chosen store
                permutations(perm, used, k + 1, n, newDist, minDistance, distanceMatrix);
                used[i] = 0;          // backtrack: mark the store as unused
            }
        }
    }
}

// function to calculate distances between all store pairs
void calculateDistances(int n, double** distanceMatrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            distanceMatrix[i][j] = calculateDistance(i, j);  // calculate distance between store i and store j
        }
    }
}

// function to calculate Euclidean distance between two stores
double calculateDistance(int a, int b) {
    return sqrt(pow(storeArray[a].x - storeArray[b].x, 2) + pow(storeArray[a].y - storeArray[b].y, 2));
}

// function to print the result: total distance and optimal store pairs
void printResult(int n, double** distanceMatrix) {
    int cnt = 2 * n;  // total number of stores
    double total = 0;  // total distance travelled

    // calculate total distance and print each optimal store pair
    for (int i = 0; i < cnt; i += 2) {
        total += distanceMatrix[array[i]][array[i + 1]];  // add distance of each pair to total
    }
    printf("%.3f\n", total);  // print total distance

    // print each optimal store pair with their names and distance
    for (int i = 0; i < cnt; i += 2) {
        printf("(%s, %s, %.3f)\n", storeArray[array[i]].name, storeArray[array[i + 1]].name,
               distanceMatrix[array[i]][array[i + 1]]);
    }

    // reset the array to initial state (first element set to -1, others to 0)
    for (int r = 0; r < MAX_STORES; r++)
        array[r] = (r == 0) ? -1 : 0;
}

// main function to execute the program
int main(void) {
    int testCases = 0;  // number of test cases
    scanf("%d", &testCases);  // read number of test cases from input

    // iterate through each test case
    for (int t = 0; t < testCases; t++) {
        int numberOfPairs = 0;  // number of store pairs for the current test case
        scanf("%d", &numberOfPairs);  // read number of store pairs from input

        int perm[MAX_STORES] = {0};  // array to store current permutation of store indices
        int used[MAX_STORES] = {0};  // array to track used store indices

        int currentIndex = 0;  // index to track current position in storeArray
        // read store coordinates and names for each pair into storeArray
        for (int j = 0; j < numberOfPairs; j++) {
            char tempName1[20], tempName2[20];  // temporary variables for store names
            scanf("%d %d %s", &storeArray[currentIndex].x, &storeArray[currentIndex].y, tempName1);
            strcpy(storeArray[currentIndex].name, tempName1);  // copy first store name into storeArray
            scanf("%d %d %s", &storeArray[currentIndex + 1].x, &storeArray[currentIndex + 1].y, tempName2);
            strcpy(storeArray[currentIndex + 1].name, tempName2);  // copy second store name into storeArray
            currentIndex += 2;  // move to the next pair of stores
        }

        // allocate memory and calculate distances between all store pairs
        double** distanceMatrix = initializeDistanceMatrix(MAX_STORES);
        calculateDistances(numberOfPairs * 2, distanceMatrix);

        double minDistance = DBL_MAX;  // variable to store minimum distance found
        // find optimal permutation of store pairs with minimum distance
        permutations(perm, used, 0, numberOfPairs, 0.0, &minDistance, distanceMatrix);
        // print the total distance and optimal store pairs for the current test case
        printResult(numberOfPairs, distanceMatrix);

        // free memory allocated for distance matrix
        freeDistanceMatrix(distanceMatrix, MAX_STORES);
    }

    return 0;  // exit the program
}
