/***
 * Function name: DSA_Search.cpp
 * Purpose: Build different search method and compare the performance.
 * Author: Johnny Lee
 * Date: 2020.05.21
***/

#include <iostream>
#include <string>
#include <time.h>

using namespace std;


#define SIZE (1024*1024*3)
int Array[SIZE];
int Array_LS[SIZE];
int Array_BS[SIZE];
int Array_ES[SIZE];

// swap x & y
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
        Array_LS[i] = Array[i];
        Array_BS[i] = Array[i];
        Array_ES[i] = Array[i];
    }
}

//Print Array
void Print_Array(int *arr, int size){
    cout << "Array is ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Quick Sort
int Partition(int *arr, int front, int end){
    int pivot = arr[end];               // pivot �q�̫�@�Ӽƶ}�l  ��K����
    int i = front - 1;                  // j = 0, i = -1�}�l���
    
    for (int j = front; j < end; j++){
        if (arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]);       // �Ypivot��arr[j]�p�A�h
        }
    }
    i++;
    swap(arr[i], arr[end]);
    // swap(arr[i], pivot);
    // �Y�ϥ�pivot�Parr[i]�洫����  arr[end]�S����arr[i]�洫
    // �h�P�W�@��pivot�ۦP �]���k�䪺�ƦC���|�i��Partition
    return i;                           // ���k�ƦC���}�C��Ǧ�m
}

void Quick_Sort(int *arr, int front, int end){
    int pivot_index;

    if(front <end){
        pivot_index = Partition(arr, front, end);
        Quick_Sort(arr, front, pivot_index - 1);        // Partition ���ƦC
        Quick_Sort(arr, pivot_index + 1, end);          // Partition �k�ƦC
    }

}

// Linear Search (Sequential Search)
int Linear_Search(int *arr, int size, int target){
    for (int i = 0; i <= size; i++){
        if (arr[i] == target){
            return i;
            
        }
    }
    return -1;
}

// Binary Search
int Binary_Search(int *arr, int size, int target){
	int begin = 0;
	int end = size;
    int mid;
    while(begin < end){
        mid = (begin + end)/2;

        if (arr[mid] == target)
            return mid;
        else if (arr[mid] > target)
            end = mid - 1;
        else if (arr[mid] < target)
            begin = mid + 1;
    }
	return -1;
}

// Exponential Search
int Exponential_Search(int *arr, int size, int target){
    int i = 1;

    // �̷�2��n���謰�Ϲj�i��j�M�A�Y��i�����ƭȤj��ؼЭ�
    // �h�ؼЭȸ��b2^(i-1) ��2^i����
    while (i < size && arr[i] <= target) 
        i = i*2; 

    // �i�J Binary Search
    int begin = i/2;
    int end = i;
    int mid = 0;

    // �Ysize < end �|�N�j�M�Darray�����O����Ŷ�
    if (size < end)
        end = size;

    while(begin < end){
        mid = (begin + end)/2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] > target)
            end = mid - 1;
        else if (arr[mid] < target)
            begin = mid + 1;
    }
	return -1;
}


int main(void)
{
    double START, END;
    cout << "Array Initialize..." << endl;
    Array_Initialize();

    int result = 0;
    int Search_Num = rand() % SIZE + 1;
    cout << "Searching number is " << Search_Num << endl;

    START = clock();
    result = Linear_Search(Array_LS, SIZE, Search_Num);
    END = clock();
    (result == -1)? printf("Element is not present in array") 
                 : printf("Element(%d) is present at index %d", Search_Num, result);
    cout << endl;    result = 0;
    cout << "Linear_Search �B��Ҫ�O���ɶ��G" << (END - START) / CLOCKS_PER_SEC << " S" << endl; 


    START = clock();
    Quick_Sort(Array_BS, 0, SIZE-1);
    result = Binary_Search(Array_BS, SIZE, Search_Num);
    END = clock();
    (result == -1)? printf("Element is not present in array") 
                 : printf("Element(%d) is present at index %d", Search_Num, result); 
    cout << endl;    result = 0;
    cout << "Binary Search �B��Ҫ�O���ɶ��G" << (END - START) / CLOCKS_PER_SEC << " S" << endl; 
    

    START = clock();
    Quick_Sort(Array_ES, 0, SIZE-1);
    result =  Exponential_Search(Array_ES, SIZE, Search_Num);
    END = clock();
    (result == -1)? printf("Element is not present in array") 
                 : printf("Element(%d) is present at index %d", Search_Num, result); 
    cout << endl;    result = 0;
    cout << "Exponential Search �B��Ҫ�O���ɶ��G" << (END - START) / CLOCKS_PER_SEC << " S" << endl; 


    system("pause");
    return 0;
}