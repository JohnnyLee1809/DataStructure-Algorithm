/***
 * Function name: DSA_Heap.cpp
 * Purpose: Build a minmum heap and test the funciton.
 * Author: Johnny Lee
 * Date: 2020.07.11
***/

#include <iostream>
#include <string>
#include <vector>
#include <climits>

class HeapNode{
    public:
        int key;             // key: node priority
        char element;        // element: node data
        HeapNode() : key(0), element(0){};
        HeapNode(int key, int data) : key(key), element(data){};

};

class BinaryHeap{
private:
    std::vector<HeapNode> heap_array;
    void Swap(class HeapNode &p1, class HeapNode &p2);
    //int *heap_array;
    int capacity;
    int heap_size = 0;          

public:
    BinaryHeap(){ heap_array.resize(1); }
    BinaryHeap(int capacity){ heap_array.resize(capacity + 1); }

    bool IsHeapEmpty() { return (heap_array.size() < 1); };
    
    int parent(int i) { return (i-1)/2; } 
    int left(int i) { return (2*i + 1); } 
    int right(int i) { return (2*i + 2); } 

    void PrintHeap(void);
    void Insert(HeapNode node);   
    void Delete(HeapNode node);

    void DecreaseKey(int node_idx, int newKey);
    int FindPosition(HeapNode node); 

    char ExtractMin();
    void MinHeapify(int node);


};

void BinaryHeap::PrintHeap(void){
    if ( heap_size == 0){
        std::cout << "The Heap is empty." << std::endl;
        return;
    }
    std::cout << std::endl;
    std::cout << "Print Heap :" << std::endl;
    for (int i = 0; i < heap_size;i++){
        std::cout << "[key: " << heap_array[i].key << ", element:" 
        << heap_array[i].element <<"]" << std::endl;
    }
    return;
}

void BinaryHeap::Insert(HeapNode node){
    if(heap_size == capacity){
        std::cout << "Heap is full!" << std::endl;
        return;
    }

    heap_size++;
    int i = heap_size - 1;
    heap_array[i].key = node.key;
    heap_array[i].element = node.element;

    // Arrange the heap order
    while(i != 0 && heap_array[parent(i)].key > heap_array[i].key){
        BinaryHeap::Swap(heap_array[i], heap_array[parent(i)]);
        i = parent(i);
    }
}

int BinaryHeap::FindPosition(HeapNode node){
    int index = -1;
    for (int i = 0; i < heap_size; i++)    {
        if(heap_array[i].element == node.element){
            index = i;
        }
    }
    if (index == -1){
        std::cout << "The node is not in this heap" << std::endl;
        return -1;
    }else{
        return index;
    }
}


void BinaryHeap::DecreaseKey(int node_idx, int newKey){
    heap_array[node_idx].key = newKey;
    
    int i = node_idx;

    // Arrange the heap order
    while(i != 0 && heap_array[parent(i)].key > heap_array[i].key){
        BinaryHeap::Swap(heap_array[i], heap_array[parent(i)]);
        i = parent(i);
    }
}

char BinaryHeap::ExtractMin(){
    if(IsHeapEmpty() == true){
        std::cout << "Heap is empty" << std::endl;
        exit(-1);
    }

    char min = heap_array[0].element;

    heap_array[0] = heap_array[heap_size - 1];
    heap_size--;

    MinHeapify(0);

    return min;
}

void BinaryHeap::MinHeapify(int node){
    int i = node, smallest = node;

    if (left(i) <= heap_size && heap_array[left(i)].key < heap_array[node].key)
        smallest = left(i);
    else
        smallest = node;
    
    if (right(i) <= heap_size  && heap_array[right(i)].key < heap_array[smallest].key)
        smallest = right(i);

    if(smallest != node){
        Swap(heap_array[node], heap_array[smallest]);
        MinHeapify(smallest);
    }
}

void BinaryHeap::Delete(HeapNode node){
    int i = FindPosition(node);
    DecreaseKey(i, INT_MIN);
    ExtractMin();

}


void BinaryHeap::Swap(HeapNode & a, HeapNode & b){
    class HeapNode tmp;
    tmp = a;
    a = b;
    b = tmp;
}


int main(void)
{
    HeapNode node1(72, 'K');
    HeapNode node2(13, 'J'); 
    HeapNode node3(67, 'B'); 
    HeapNode node4(3, 'A');
    HeapNode node5(46, 'Z');

    BinaryHeap H(12);
    H.PrintHeap();
    H.Insert(node1);
    H.Insert(node2);
    H.Insert(node3);
    H.PrintHeap();
    H.Insert(node4);
    H.Insert(node5);
    H.PrintHeap();
    std::cout << "The position of the element " << node3.element << " is " << H.FindPosition(node3) << std ::endl;
    H.DecreaseKey(2, 1);
    H.PrintHeap();
    std::cout << std::endl << "Extract Min element is " << H.ExtractMin() << std::endl;
    H.PrintHeap();
    H.Delete(node4);
    H.PrintHeap();

    system("pause");
    return 0;
}