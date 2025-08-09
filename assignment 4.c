/* COP 3502C Programming Assignment 4
This program is written by: Munish Persaud */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct stores {
    int x;
    int y;

} StoreLoc;

StoreLoc* ReadData(int n);
int compareTo(StoreLoc* ptrPt1, StoreLoc* ptrPt2);
void mergeSort(StoreLoc arr[], int Sindex, int Eindex, int threshold);
void merge(StoreLoc a[], int l, int m, int r);
void insertionSort(StoreLoc arr[], int Sindex, int Eindex);
void wrapperFunction(StoreLoc* ptr, int n, int threshold);
int binarySearch(StoreLoc* arr, int n, StoreLoc* query);

int myX;
int myY;

int compareTo(StoreLoc* ptrPt1, StoreLoc* ptrPt2) {
    float dist1 = sqrt((ptrPt1->x - myX) * (ptrPt1->x - myX) + (ptrPt1->y - myY) * (ptrPt1->y - myY));

    float dist2 = sqrt((ptrPt2->x - myX) * (ptrPt2->x - myX) + (ptrPt2->y - myY) * (ptrPt2->y - myY));


    if (dist1 < dist2) return -1;
    if (dist1 > dist2) return 1;

    // If distances are equal, compare x coordinates
    if (ptrPt1->x < ptrPt2->x) return -1;
    if (ptrPt1->x > ptrPt2->x) return 1;

    // If x coordinates are equal, compare y coordinates
    if (ptrPt1->y < ptrPt2->y) return -1;
    if (ptrPt1->y > ptrPt2->y) return 1;

    return 0; // Points are identical
}

void mergeSort(StoreLoc arr[], int Sindex, int Eindex, int threshold) {
    if (Eindex - Sindex + 1 <= threshold) {
        insertionSort(arr, Sindex, Eindex);
    } else {
        if (Eindex > Sindex) {
            int m = (Sindex + Eindex) / 2;
            mergeSort(arr, Sindex, m, threshold);
            mergeSort(arr, m + 1, Eindex, threshold);
            merge(arr, Sindex, m, Eindex);
        }
    }
}


void merge(StoreLoc a[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    StoreLoc* L = malloc(sizeof(StoreLoc) * n1);
    StoreLoc* R = malloc(sizeof(StoreLoc) * n2);

    for (i = 0; i < n1; i++) {
        L[i] = a[l + i];
    }

    for (j = 0; j < n2; j++) {
        R[j] = a[m + 1 + j];
    }
    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (compareTo(&L[i], &R[j]) <= 0) {
            a[k] = L[i];
            k++;
            i++;
        } else {
            a[k] = R[j];
            k++;
            j++;
        }
    }
    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
    free(R);
    free(L);
}

void insertionSort(StoreLoc arr[], int Sindex, int Eindex) {
    int i, j;
    StoreLoc item;
    for (i = Sindex + 1; i <= Eindex; i++) {
        item = arr[i];
        for (j = i - 1; j >= Sindex && compareTo(&arr[j], &item) > 0; j--) {
            arr[j + 1] = arr[j];
        }
        arr[j + 1] = item;
    }
}

StoreLoc* ReadData(int n) {
  StoreLoc* ptr = malloc(n * sizeof(StoreLoc));
  for (int i = 0; i < n; i++){
    scanf("%d %d", &ptr[i].x, &ptr[i].y); 
  }
  return ptr;
 }


void wrapperFunction(StoreLoc* ptr, int n, int threshold) {
  mergeSort(ptr, 0, n-1, threshold);
}

int binarySearch(StoreLoc* arr, int n, StoreLoc* query) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = compareTo(&arr[mid], query);
        if (cmp == 0) return mid; 
        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }

    return -1; // Not found
}

int main(void) {
  //input goes x and y of my location, then number of smoothie shops, then number of points to search, then threshold. 
  int numShops, numPoints, threshold;
  scanf("%d %d", &myX, &myY);
  scanf("%d", &numShops);
  scanf("%d", &numPoints);
  scanf("%d", &threshold);

  StoreLoc* ptrStores = ReadData(numShops);
  StoreLoc* ptrPoints = ReadData(numPoints); 

  wrapperFunction(ptrStores, numShops, threshold);

  for(int i=0; i<numShops; i++){
    printf("%d %d\n", ptrStores[i].x, ptrStores[i].y); 
  }
  

  for(int i = 0; i < numPoints; i++) {
      int result = binarySearch(ptrStores, numShops, &ptrPoints[i]);
      if(result != -1) {
          printf("%d %d found at rank %d\n", ptrPoints[i].x, ptrPoints[i].y, result);
      } else {
          printf("%d %d not found\n", ptrPoints[i].x, ptrPoints[i].y);
      }
  }

  
  
}