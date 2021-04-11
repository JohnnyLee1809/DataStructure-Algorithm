/***
 * Function name: DSA_Stack.cpp
 * Purpose: Build two type of stack(array and linkedlist) and test the funciton.
 * Author: Johnny Lee
 * Date: 2020.05.15
***/

#include <iostream>
#include <string>

using namespace std;

// Array 實作 Stack
class StackArray{
    private:
        int top;
        int capacity;
        int *stack;
        void IncreaseCapacity();
    
    public:
        StackArray():top(-1), capacity(1){
            stack = new int[capacity];
        }
        void Push(int x);
        void Pop();
        bool IsEmpty();
        void PrintInformation();
        int Top();
};

void StackArray :: IncreaseCapacity(){
    if (capacity < 100) {
        capacity *= 2;
    }
    else{
        capacity += 100;
    }

    int *newCapacity = new int[capacity];

    for (int i = 0; i < capacity / 2; i++){
        newCapacity[i] = stack[i];
    }

    delete [] stack;
    stack = newCapacity;
}

void StackArray :: Push(int x){
    if(top == capacity -1){
        IncreaseCapacity();
    }
    stack[++top] = x;
}

bool StackArray :: IsEmpty(){
    if (top == -1){
        cout << "Stack is Empty.\n";
    }

    return (top == -1);
}


void StackArray :: Pop(){
    if (IsEmpty()){
        cout << "No need to Pop.\n";
        return;
    }
    stack[top] = 0;
    top--;
}


int StackArray ::Top(){
    return stack[top];
}

void StackArray :: PrintInformation(){
    if (IsEmpty()){
        return;
    }
    cout << "Top value is " << stack[top] << ". Stack size is " << top + 1  << ".\n";
}



// LinkedList 實作 Stack
class StackList;

class StackNode{
    private:
        int data;
        StackNode *next;
    public:
        StackNode(): data(0) { next = nullptr; }
        StackNode(int x) : data(x) { next = nullptr; }
        StackNode(int x, StackNode *nextNode) : data(x), next(nextNode){};
        // StackList是StackNode的friend, 則StackList可讀取StackNode內的值
        friend class StackList;

};

class StackList{
    private:
        StackNode *top;
        int size;
    public:
        StackList() : size(0), top(nullptr){};
        void Push(int x);
        void Pop();
        bool IsEmpty();
        void PrintInformation();
};

void StackList::Push(int x){
    if(IsEmpty()){
        top = new StackNode(x);
        size++;
        return;
    }

    StackNode *newnode = new StackNode(x);
    newnode->next = top;        // a->b 等於 (*a).b
    top = newnode;
    size++;
}

void StackList::Pop(){
    if (IsEmpty()){
        cout << "No need to Pop.\n";
        return;
    }

    StackNode *deletenode = top;
    top = top->next;
    delete deletenode;
    deletenode = 0;
    size--;
}


bool StackList :: IsEmpty(){
    if (size == 0){
        cout << "Stack is Empty.\n";
    }

    return (size == 0);
}

void StackList :: PrintInformation(){
    if (IsEmpty()){
        return;
    }
    cout << "Top value is " << top->data << ". Stack size is " << size << ".\n";
}


int main(void)
{
    cout << "StackArray \n";
    StackArray s_a;
    s_a.PrintInformation();
    s_a.Push(5);
    s_a.PrintInformation();
    s_a.Push(92);
    s_a.PrintInformation();
    s_a.Pop();
    s_a.PrintInformation();
    s_a.Push(23);
    s_a.PrintInformation();
    s_a.Pop();    
    s_a.Pop();
    s_a.PrintInformation();

    cout << "StackList \n";
    StackList s_l;
    s_l.PrintInformation();
    s_l.Push(5);
    s_l.PrintInformation();
    s_l.Push(92);
    s_l.PrintInformation();
    s_l.Pop();
    s_l.PrintInformation();
    s_l.Push(23);
    s_l.PrintInformation();
    s_l.Pop();    
    s_l.Pop();
    s_l.PrintInformation();    

    system("pause");
    return 0;
}