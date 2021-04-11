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
    int pivot = arr[end];               // pivot 從最後一個數開始  方便移動
    int i = front - 1;                  // j = 0, i = -1開始比較
    
    for (int j = front; j < end; j++){
        if (arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]);       // 若pivot比arr[j]小，則
        }
    }
    i++;
    swap(arr[i], arr[end]);
    // swap(arr[i], pivot);
    // 若使用pivot與arr[i]交換的話  arr[end]沒有跟arr[i]交換
    // 則與上一個pivot相同 因此右邊的數列不會進行Partition
    return i;                           // 左右數列的陣列基準位置
}

void Quick_Sort(int *arr, int front, int end){
    int pivot_index;

    if(front <end){
        pivot_index = Partition(arr, front, end);
        Quick_Sort(arr, front, pivot_index - 1);        // Partition 左數列
        Quick_Sort(arr, pivot_index + 1, end);          // Partition 右數列
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

    // 依照2的n次方為區隔進行搜尋，若第i次的數值大於目標值
    // 則目標值落在2^(i-1) 到2^i之間
    while (i < size && arr[i] <= target) 
        i = i*2; 

    // 進入 Binary Search
    int begin = i/2;
    int end = i;
    int mid = 0;

    // 若size < end 會將搜尋非array內的記憶體空間
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
    cout << "Linear_Search 運算所花費的時間：" << (END - START) / CLOCKS_PER_SEC << " S" << endl; 


    START = clock();
    Quick_Sort(Array_BS, 0, SIZE-1);
    result = Binary_Search(Array_BS, SIZE, Search_Num);
    END = clock();
    (result == -1)? printf("Element is not present in array") 
                 : printf("Element(%d) is present at index %d", Search_Num, result); 
    cout << endl;    result = 0;
    cout << "Binary Search 運算所花費的時間：" << (END - START) / CLOCKS_PER_SEC << " S" << endl; 
    

    START = clock();
    Quick_Sort(Array_ES, 0, SIZE-1);
    result =  Exponential_Search(Array_ES, SIZE, Search_Num);
    END = clock();
    (result == -1)? printf("Element is not present in array") 
                 : printf("Element(%d) is present at index %d", Search_Num, result); 
    cout << endl;    result = 0;
    cout << "Exponential Search 運算所花費的時間：" << (END - START) / CLOCKS_PER_SEC << " S" << endl; 


    system("pause");
    return 0;
}