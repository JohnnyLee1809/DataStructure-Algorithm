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
        min_index = i;                          // �q��0���}�l���
        for (j = i + 1; j < size; j++){
            if (arr[j] < arr[min_index]){
                min_index = j;                  // �z�Lj�Ȼ��W�N��i�V�᪺�ƭȥ����T�{�A�N�̤p�ȻP��i������
                swap(arr[i], arr[min_index]);
            }
        }
    }
}


// Bubble Sort
void Bubble_Sort(int *arr, int size){
    
    for(int i = size - 1; i > 0; i--){      // �̫�@�����ݤ���Aj�j��p�⧹�ɧY��̤j��
        for (int j = 0; j < i; j++)         // j���ݤ�����ƦC�̷�i���ݤ����
            if (arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
            }
    }
}


// Insertion Sort
void Insertion_Sort(int *arr, int size){
    int key, j;     // key���n���J���ƭ�, j���Pkey����x�}�ƭȪ��s����

    for (int i = 1; i < size; i++){
        key = arr[i];
        j = i - 1;                      // �P�e�@���ۤ�
        while (key < arr[j] && j >=0){
            arr[j + 1] = arr[j];        // �Ykey��arr[j]�p�A�harr[j]���Ჾ��
            j--;                        // key�~��V�e����A�]��while����ݭ��wj>=0
        }
        arr[j + 1] = key;               // �Ykey�j��arr[j]�h��������Akey���Jarr[j]���
    }
}


// Quick Sort
int Partition(int *arr, int front, int end){
    int pivot = arr[end];               // pivot �q�̫�@�Ӽƶ}�l  ��K����
    int i = front - 1;                  // j = 0, i = -1�}�l���
    
    for (int j = front; j < end; j++){
        if (arr[j] <= pivot){       
            i++;     
            swap_ref(&arr[i], &arr[j]);       // �Ypivot��arr[j]�p�A�h
            
        }
    }
    swap_ref(&arr[i+1], &arr[end]);
    //swap(arr[i], pivot);
    // �Y�ϥ�pivot�Parr[i]�洫����  arr[end]�S����arr[i]�洫
    // �h�P�W�@��pivot�ۦP �]���k�䪺�ƦC���|�i��Partition
    return i+1;                           // ���k�ƦC���}�C��Ǧ�m
}

void Quick_Sort(int *arr, int front, int end){

    if(front < end){
        int pivot_index = Partition(arr, front, end);
        Quick_Sort(arr, front, pivot_index - 1);        // Partition ���ƦC
        Quick_Sort(arr, pivot_index + 1, end);          // Partition �k�ƦC
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
    cout << endl << "Selection Sort�i��B��Ҫ�O���ɶ��G" << (END - START) / CLOCKS_PER_SEC << " S" << endl;

    START = clock();
    Bubble_Sort(Array_BS,SIZE);
    END = clock();
    cout << endl << "Bubble Sort�i��B��Ҫ�O���ɶ��G" << (END - START) / CLOCKS_PER_SEC << " S" << endl;

    START = clock();
    Insertion_Sort(Array_IS,SIZE);
    END = clock();
    cout << endl << "Insertion Sort�i��B��Ҫ�O���ɶ��G" << (END - START) / CLOCKS_PER_SEC << " S" << endl;

    START = clock();
    Quick_Sort(Array_QS, 0, SIZE-1);
    END = clock();
    cout << endl << "Quick Sort�i��B��Ҫ�O���ɶ��G" << (END - START) / CLOCKS_PER_SEC << " S" << endl;
   
    system("pause");
    return 0;
}