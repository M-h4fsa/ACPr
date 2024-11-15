#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void genRandArray(int n, const char* f) {
    FILE* file = fopen(f, "w");
    if (!file) {
        printf("Error: couldn't open file\n");
        return;
    }

    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++) {
        int num = (rand() & (1000 | 1));

        fprintf(file, "%d ", num);
    }

    fclose(file);
}

int* readArrFile(const char* f, int* size) {
    FILE* file = fopen(f, "r");
    if (!file) {
        printf("Error: couldn't open file\n");
        return NULL;
    }

    if (fscanf(file, "%d", size) != 1) {
        printf("Error: array size invalid\n");
        fclose(file);
        return NULL;
    }

    int* array = (int*)malloc(*size*sizeof(int));
    if (!array) {
        printf("Error: malloc failed\n");
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < *size; i++) {
        if (fscanf(file, "%d", &array[i]) != 1) {
            printf("Error: reading failed\n");
            free(array);
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return array;
}

void printArr(const int* array, int size) {
    printf("Array elements:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int* copy_array(const int* array, int size) {
    int* newArr = (int*)malloc(size*sizeof(int));
    if (!newArr) {
        printf("Error: malloc failed\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        newArr[i] = array[i];
    }
    return newArr;
}

//helper function for mergeSort
void merge(int* array, int left, int mid, int right, int* comparisons, int* passes) {
    int n1 = mid-left+1;
    int n2 = right-mid;

    int* L = (int*)malloc(n1*sizeof(int));
    int* R = (int*)malloc(n2*sizeof(int));

    for (int i = 0; i < n1; i++) {
        L[i] = array[left+i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = array[mid+1+j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        (*comparisons)++;
        if (L[i] <= R[j]) {
            array[k++] = L[i++];
        } else {
            array[k++] = R[j++];
        }
    }

    while (i < n1) {
        array[k++] = L[i++];
    }
    while (j < n2) {
        array[k++] = R[j++];
    }

    free(L);
    free(R);
    (*passes)++;
}

//helper for partition function
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//helper function for quick sort 
int partition(int* array, int left, int right, int* comparisons) {
    int pivot = array[left];
    int i = left;
    int j = right + 1;

    while (1) {
        do {
            i++;
            (*comparisons)++;
        } while (i <= right && array[i] < pivot);

        do {
            j--;
            (*comparisons)++;
        } while (array[j] > pivot);

        if (i >= j) {
            swap(&array[left], &array[j]); 
            return j; 
        }

        swap(&array[i], &array[j]);
    }
}
/*________sorting algorithms________*/

//Selection
void selectionSort(int* array, int size, int* comparisons, int* passes, int* swaps) {
    *comparisons = 0;
    *passes = 0;
    *swaps = 0;

    for (int i = 0; i < size-1; i++) {
        (*passes)++;
        int min_index = i;
        for (int j = i+1; j < size; j++) {
            (*comparisons)++;
            if (array[j] < array[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int temp = array[min_index];
            array[min_index] = array[i];
            array[i] = temp;
            (*swaps)++;
        }
    }
}

//Bubble
void bubbleSort(int* array, int size, int* comparisons, int* passes, int* swaps) {
    *comparisons = 0;
    *passes = 0;
    *swaps = 0;

    for (int i = 0; i < size-1; i++) {
        (*passes)++;
        for (int j = 0; j < size-i-1; j++) {
            (*comparisons)++;
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                (*swaps)++;
            }
        }
    }
}

//Insertion
void insertionSort(int* array, int size, int* comparisons, int* passes) {
    *comparisons = 0;
    *passes = 0;

    for (int i = 1; i < size; i++) {
        (*passes)++;
        int key = array[i];
        int j = i-1;
        while (j >= 0 && array[j] > key) {
            (*comparisons)++;
            array[j+1] = array[j];
            j--;
        }
        //last comparison
        (*comparisons)++; 
        array[j+1] = key;
    }
}

//merge
void mergeSort(int* array, int size, int* comparisons, int* passes) {
    int* temp = (int*)malloc(size*sizeof(int));
    if (!temp) {
        printf("Error: malloc failed\n");
        return;
    }

    *comparisons = 0;
    *passes = 0;

    for (int len = 1; len < size; len *= 2) {
        (*passes)++;
        for (int i = 0; i < size; i += 2*len) {
            int left = i;
        int mid;
        if (i+len-1 < size) {
            mid = i+len-1;
        } else {
            mid = size-1;
        }

            int right;
            if (i+2*len-1 < size) {
                right = i+2*len-1;
            } else {
                right = size-1;
            }
            int n1 = mid-left+1;
            int n2 = right-mid;

            int* L = (int*)malloc(n1*sizeof(int));
            int* R = (int*)malloc(n2*sizeof(int));

            for (int j = 0; j < n1; j++) {
                L[j] = array[left+j];
            }
            for (int j = 0; j < n2; j++) {
                R[j] = array[mid+1+j];
            }

            int x = 0, y = 0, z = left;
            while (x < n1 && y < n2) {
                (*comparisons)++;
                if (L[x] <= R[y]) {
                    array[z++] = L[x++];
                } else {
                    array[z++] = R[y++];
                }
            }

            while (x < n1) {
                array[z++] = L[x++];
            }
            while (y < n2) {
                array[z++] = R[y++];
            }

            free(L);
            free(R);
        }
    }

    free(temp);
}

//mergeRecursive
void mergeRecSort(int* array, int left, int right, int* comparisons, int* passes) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeRecSort(array, left, mid, comparisons, passes);
        mergeRecSort(array, mid + 1, right, comparisons, passes);

        (*passes)++;
        merge(array, left, mid, right, comparisons, passes);
    }
}

//Quick
void quickSort(int* array, int begin, int end, int* comparisons, int* passes) {
    if (begin < end) {
        (*passes)++;  
        
        int p = partition(array, begin, end, comparisons);
        
        quickSort(array, begin, p - 1, comparisons, passes);
        quickSort(array, p + 1, end, comparisons, passes);
    }
}

int main() {
    srand(time(NULL)); 

    char filename[50];
    int arr_size;
    //init counters
    int comparisons, passes, swaps;
    //user prompt
    printf("Enter the file name for your randomized array: ");
    scanf("%s", filename);
    printf("Enter the number of elements of your array: ");
    scanf("%d", &arr_size);
    //generate
    genRandArray(arr_size, filename);
    //read
    int* array = readArrFile(filename, &arr_size);
    if (!array) {
        return 1;
    }
    printf("Array before sorting:\n ");
    printArr(array, arr_size);
    //make array copies
    int* selection_array = copy_array(array, arr_size);
    int* bubble_array = copy_array(array, arr_size);
    int* insertion_array = copy_array(array, arr_size);
    int* merge_array = copy_array(array, arr_size);
    int* merge_rec_array = copy_array(array, arr_size);
    int* quick_array = copy_array(array, arr_size);

    //start sorting
    /*____selection____*/
    printf("SELECTION SORT:\n ");
    selectionSort(selection_array, arr_size, &comparisons, &passes, &swaps);
    printf("metrics: %d comparisons, %d passes, %d swaps\n", comparisons, passes, swaps);
    free(selection_array);
    /*________________*/
    printf("\n");
    /*____Bubble____*/
    printf("BUBBLE SORT:\n ");
    bubbleSort(bubble_array, arr_size, &comparisons, &passes, &swaps);
    printf("metrics: %d comparisons, %d passes, %d swaps\n", comparisons, passes, swaps);
    free(bubble_array);
    /*________________*/
    printf("\n");
    /*____Insertion____*/
    printf("INSERTION SORT:\n ");
    insertionSort(insertion_array, arr_size, &comparisons, &passes);
    printf("metrics: %d comparisons, %d passes\n", comparisons, passes);
    free(insertion_array);
    /*________________*/
    printf("\n");
        /*____Merge____*/
    printf("MERGE SORT:\n ");
    mergeSort(merge_array, arr_size, &comparisons, &passes);
    printf("metrics: %d comparisons, %d passes\n", comparisons, passes);
    free(merge_array);
    /*________________*/
    printf("\n");
    /*____Merge Recursive____*/
    comparisons=0;passes=0;
    printf("RECURSIVE MERGE SORT:\n ");
    mergeRecSort(merge_rec_array,0, arr_size-1, &comparisons, &passes);
    printf("metrics: %d comparisons, %d passes\n", comparisons, passes);
    free(merge_rec_array);
    /*________________*/
    printf("\n");
    /*____Quick____*/
    comparisons=0;passes=0;
    printf("QUICK SORT:\n ");
    quickSort(quick_array,0, arr_size-1, &comparisons, &passes);
    printf("metrics: %d comparisons, %d passes\n", comparisons, passes);
    free(quick_array);
    /*________________*/
    printf("\n");
    free(array);

    return 0;
}
