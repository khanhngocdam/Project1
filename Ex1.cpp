#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <time.h>
using namespace std;

void printMenuCreatData() {
        cout << "1. Input from keyboard \n";
        cout << "2. Random\n";
        cout << "3. File\n";
        cout << "Enter your choice:  ";
}
//----------------------------------------------------------------
void printMenuAlgorithm() {
    cout << "Sorting Algorithms\n";
    cout << "1. Buble sort\n";
    cout << "2. Insertion sort \n";
    cout << "3. Quick sort \n";
    cout << "4. Merge sort \n";
    cout << "5. Heap sort \n";
    cout << "Enter your choice:  ";

}
//-----------------------------------------------------------------
// buble sort  O(n^2)
void bubleSort(int array[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = n - 1; j > i; j-- ) {
            if (array[j] < array[j-1]) {
                int tmp = array[j];
                array[j] = array[j-1];
                array[j-1] = tmp;
            }
        }
    }
}
// -----------------------------------------------------------------
// insertion sort, O(n) in the best case. O(n^2) in the average, worst case
void insertionSort(int array[], int n) {
    for (int i = 1; i < n; i++) {
        int key = array[i];
        int j = i - 1;
        while (array[j] > key && j >= 0) {
            array[j+1] = array[j];
            array[j] = key;
            j--; 
        }       
    }
}
//------------------------------------------------------------------------------
// Quick sort, O(nlogn) in the best case, average case. O(n^2) in the worst case
int paratition(int array[],int left, int right) {
    int pivot = array[left];
    int i = left + 1;
    int j = right;
    do {
        while (i <= j && array[i] <= pivot) i++;
        while (i <= j && array[j] >= pivot) j--;
        if (i < j) {
            int tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
    } while (i <= j);
    int tmp = array[left];
    array[left] = array[j];
    array[j] = tmp;
    return j;
} 

void quickSort(int array[], int left, int right) {
    int k;
    if (left < right) {
        k = paratition(array,left,right);
        quickSort(array, left, k-1);
        quickSort(array, k + 1, right);
    }
}
//-----------------------------------------------------------------------
// merge sort  O(nlogn) in the best, average, and worst case.
void merge(int array[], int left, int mid, int right) {
    int n = right - left + 1;
    int* array_merge = new int[n];
    int i = left, j = mid + 1;
    int k = 0;
    while (i < mid + 1 && j < right + 1) {
        if (array[i] > array[j]) {
            array_merge[k] = array[j];
            k++; j++;
        } else {
            array_merge[k] = array[i];
            i++; k++;
        }
    }
    while (i < mid + 1) {
        array_merge[k] = array[i];
        i++; k++;
    } 
    while (j < right + 1) {
        array_merge[k] = array[j];
        k++; j++;
    }
    i = left;
    for (int k = 0; k < n; k++) {
        array[i] = array_merge[k];
        i++;
    }
    delete[] array_merge;
} 
void mergeSort(int array[], int left, int right) {
    if (left < right) {
        int mid = (left + right)/2;
        mergeSort(array, left, mid);
        mergeSort(array, mid + 1, right);
        merge(array, left, mid,right);
    }
}
//---------------------------------------------------------------------
// Heap sort
void heapify(int array[], int n, int parent) {
    int k = parent;
    int left = parent * 2 + 1;
    int right = parent * 2 + 2;
    
    if ( left < n && array[left] > array[parent]) {
        parent = left; 
    } 
    if ( right < n && array[right] > array[parent]) {
        parent = right;
    }
    if (parent != k) {
        int tmp = array[parent];
        array[parent] = array[k];
        array[k] = tmp;
        heapify(array, n, parent);
    }
}
// heap sort
void heapSort(int array[], int n) {
    for (int i = n/2 -1; i >= 0; i--) {
        heapify(array, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        int tmp = array[0];
        array[0] = array[i];
        array[i] = tmp;
        heapify(array, i, 0);
    }
}
//-------------------------------------------------------------------
// Print array 
void printArray(int array[], int n) {
    for (int i = 0; i < n; i++) {
        cout << array[i] << "   ";
    }
}
//----------------------------------------------------------------------
int main() {
    printMenuCreatData();
    int choice_input;
    cin >> choice_input;
    int choice_algorithm;
// Input form keyboard if choice = 1
    if (choice_input == 1) {
        cout << "Enter the number of elements: ";
// Declare n is the number of elements
        int n; cin >> n;
// Delare array int
        int* arr = new int[n];
// Enter the value of each element
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
// Print menu to choose algorithm
        printMenuAlgorithm();
        cin >> choice_algorithm;
//  Buble sort if choice = 1
        if (choice_algorithm == 1) {
            bubleSort(arr, n);
            printArray(arr, n);
        }
// Insertion sort if choice = 2
        if (choice_algorithm == 2) {
            insertionSort(arr, n);
            printArray(arr, n);
        }
// Quick sort if choice = 3
        if (choice_algorithm == 3) {
            quickSort(arr,0,n-1);
            printArray(arr, n);
        }
// Merger sort if choice = 4
        if ( choice_algorithm == 4) {
            mergeSort(arr, 0, n-1);
            printArray(arr, n);
        }
// Heap sort if choice = 5
        if (choice_algorithm == 5) {
            heapSort(arr, n);
            printArray(arr, n);
        }
    delete[] arr;
    }
// Random data if choice_input = 2
    if (choice_input == 2 ) {
        cout << "Enter the number of elements: ";
        int n; cin >> n;
        int* arr = new int[n];
        srand(time(NULL));
        for (int i = 0; i < n; i++) {
	        arr[i] = rand();
        }
        printMenuAlgorithm();
        cin >> choice_algorithm;
       // clock_t t1 = clock();
//  Buble sort if choice = 1
        if (choice_algorithm == 1) {
            clock_t t1 = clock();
            bubleSort(arr, n);
            clock_t t2 = clock();
            double time_process = (double)(t2 - t1)/ CLOCKS_PER_SEC;
            cout << "\nTime Process: " << time_process << endl ;
            //printArray(arr, n);
        }
// Insertion sort if choice = 2
        if (choice_algorithm == 2) {
            insertionSort(arr, n);
           printArray(arr, n);
        }
// Quick sort if choice = 3
        if (choice_algorithm == 3) {
            quickSort(arr,0,n-1);
            printArray(arr, n);
        }
// Merger sort if choice = 4
        if ( choice_algorithm == 4) {
            mergeSort(arr, 0, n-1);
            printArray(arr, n);
        }
// Heap sort if choice = 5
        if (choice_algorithm == 5) {
            heapSort(arr, n);
            printArray(arr, n);
        }  
                  
        delete[] arr;
    }
// Input = file if choice = 3
    if (choice_input == 3) {
//Read file
        ifstream file;
        file.open("data.txt");
        int n;
        file >> n;
        int* arr = new int[n];
        for (int i = 0; i < n; i++) {
            file >> arr[i];
        }
//----------------------------------------------------------------------
        printMenuAlgorithm();
        cin >> choice_algorithm;
//  Buble sort if choice = 1
        if (choice_algorithm == 1) {
            bubleSort(arr, n);
            printArray(arr, n);
        }
        // Insertion sort if choice = 2
        if (choice_algorithm == 2) {
            insertionSort(arr, n);
            printArray(arr, n);
        }
// Quick sort if choice = 3
        if (choice_algorithm == 3) {
            quickSort(arr,0,n-1);
            printArray(arr, n);
        }
// Merger sort if choice = 4
        if ( choice_algorithm == 4) {
            mergeSort(arr, 0, n-1);
            printArray(arr, n);
        }
        if (choice_algorithm == 5) {
            heapSort(arr, n);
            printArray(arr, n);
        }
        file.close();
        delete[] arr; 

    }
}