/***
 * Function name: DSA_Sort.cpp
 * Purpose: Build different sort method and compare the performance.
 * Author: Johnny Lee
 * Date: 2020.05.15
***/

#include <iostream>
#include <string>
#include <time.h>

using namespace std;

#define SIZE (1024*3)
int Array[SIZE];
int Array_SS[SIZE];
int Array_BS[SIZE];
int Array_IS[SIZE];
int Array_QS[SIZE];

// Swap by reference
void swap(int &x, int &y){
	int temp;
	temp = x;
	x = y;
	y = temp;
}

// Array Initialize
void Array_Initialize(void){
 
    for (int i = 0; i < SIZE; i++)
        Array[i] = i;

    for (int i = 0; i < SIZE; i++)
        swap(Array[i], Array[rand() % SIZE + 1]);

    for (int i = 0; i < SIZE; i++)
    {
        Array_SS[i] = Array[i];
        Array_BS[i] = Array[i];
        Array_IS[i] = Array[i];
        Array_QS[i] = Array[i];
    }
}

//Print Array
void Print_Array(int *arr, int size){
    cout << "Array is ";
    for (int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

void swap_ref(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
// Selection Sort
void Selection_Sort(int *arr, int size){
    int i, j, min_index;
    for (i = 0; i < size-1; i++){
        min_index = i;                          // 從第0項開始比較
        for (j = i + 1; j < size; j++){
            if (arr[j] < arr[min_index]){
                min_index = j;                  // 透過j值遞增將第i向後的數值全部確認，將最小值與第i項互換
                swap(arr[i], arr[min_index]);
            }
        }
    }
}


// Bubble Sort
void Bubble_Sort(int *arr, int size){
    
    for(int i = size - 1; i > 0; i--){      // 最後一項不需比較，j迴圈計算完時即位最大值
        for (int j = 0; j < i; j++)         // j項需比較的數列依照i項需比較的
            if (arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
            }
    }
}


// Insertion Sort
void Insertion_Sort(int *arr, int size){
    int key, j;     // key為要插入的數值, j為與key比較矩陣數值的編號值

    for (int i = 1; i < size; i++){
        key = arr[i];
        j = i - 1;                      // 與前一項相比
        while (key < arr[j] && j >=0){
            arr[j + 1] = arr[j];        // 若key比arr[j]小，則arr[j]往後移動
            j--;                        // key繼續向前比較，因此while條件需限定j>=0
        }
        arr[j + 1] = key;               // 若key大於arr[j]則比較結束，key插入arr[j]後方
    }
}


// Quick Sort
int Partition(int *arr, int front, int end){
    int pivot = arr[end];               // pivot 從最後一個數開始  方便移動
    int i = front - 1;                  // j = 0, i = -1開始比較
    
    for (int j = front; j < end; j++){
        if (arr[j] <= pivot){       
            i++;     
            swap_ref(&arr[i], &arr[j]);       // 若pivot比arr[j]小，則
            
        }
    }
    swap_ref(&arr[i+1], &arr[end]);
    //swap(arr[i], pivot);
    // 若使用pivot與arr[i]交換的話  arr[end]沒有跟arr[i]交換
    // 則與上一個pivot相同 因此右邊的數列不會進行Partition
    return i+1;                           // 左右數列的陣列基準位置
}

void Quick_Sort(int *arr, int front, int end){

    if(front < end){
        int pivot_index = Partition(arr, front, end);
        Quick_Sort(arr, front, pivot_index - 1);        // Partition 左數列
        Quick_Sort(arr, pivot_index + 1, end);          // Partition 右數列
    }

}


int main(void)
{
    double START, END;
    cout << "Array Initialize..." << endl;
    Array_Initialize();

    START = clock();
    Selection_Sort(Array_SS,SIZE);
    END = clock();
    cout << endl << "Selection Sort進行運算所花費的時間：" << (END - START) / CLOCKS_PER_SEC << " S" << endl;

    START = clock();
    Bubble_Sort(Array_BS,SIZE);
    END = clock();
    cout << endl << "Bubble Sort進行運算所花費的時間：" << (END - START) / CLOCKS_PER_SEC << " S" << endl;

    START = clock();
    Insertion_Sort(Array_IS,SIZE);
    END = clock();
    cout << endl << "Insertion Sort進行運算所花費的時間：" << (END - START) / CLOCKS_PER_SEC << " S" << endl;

    START = clock();
    Quick_Sort(Array_QS, 0, SIZE-1);
    END = clock();
    cout << endl << "Quick Sort進行運算所花費的時間：" << (END - START) / CLOCKS_PER_SEC << " S" << endl;
   
    system("pause");
    return 0;
}