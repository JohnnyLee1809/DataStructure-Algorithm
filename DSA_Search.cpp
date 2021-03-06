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
    int pivot = arr[end];               // pivot 眖程计秨﹍  よ獽簿笆
    int i = front - 1;                  // j = 0, i = -1秨﹍ゑ耕
    
    for (int j = front; j < end; j++){
        if (arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]);       // 璝pivotゑarr[j]玥
        }
    }
    i++;
    swap(arr[i], arr[end]);
    // swap(arr[i], pivot);
    // 璝ㄏノpivot籔arr[i]ユ传杠  arr[end]⊿Τ蛤arr[i]ユ传
    // 玥籔pivot 娩计ぃ穦秈︽Partition
    return i;                           // オ计皚膀非竚
}

void Quick_Sort(int *arr, int front, int end){
    int pivot_index;

    if(front <end){
        pivot_index = Partition(arr, front, end);
        Quick_Sort(arr, front, pivot_index - 1);        // Partition オ计
        Quick_Sort(arr, pivot_index + 1, end);          // Partition 计
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

    // ㄌ酚2nΩよ跋筳秈︽穓碝璝材iΩ计ヘ夹
    // 玥ヘ夹辅2^(i-1) 2^iぇ丁
    while (i < size && arr[i] <= target) 
        i = i*2; 

    // 秈 Binary Search
    int begin = i/2;
    int end = i;
    int mid = 0;

    // 璝size < end 穦盢穓碝獶arrayず癘拘砰丁
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
    cout << "Linear_Search 笲衡┮禣丁" << (END - START) / CLOCKS_PER_SEC << " S" << endl; 


    START = clock();
    Quick_Sort(Array_BS, 0, SIZE-1);
    result = Binary_Search(Array_BS, SIZE, Search_Num);
    END = clock();
    (result == -1)? printf("Element is not present in array") 
                 : printf("Element(%d) is present at index %d", Search_Num, result); 
    cout << endl;    result = 0;
    cout << "Binary Search 笲衡┮禣丁" << (END - START) / CLOCKS_PER_SEC << " S" << endl; 
    

    START = clock();
    Quick_Sort(Array_ES, 0, SIZE-1);
    result =  Exponential_Search(Array_ES, SIZE, Search_Num);
    END = clock();
    (result == -1)? printf("Element is not present in array") 
                 : printf("Element(%d) is present at index %d", Search_Num, result); 
    cout << endl;    result = 0;
    cout << "Exponential Search 笲衡┮禣丁" << (END - START) / CLOCKS_PER_SEC << " S" << endl; 


    system("pause");
    return 0;
}