/***
 * Function name: DSA_LinkedList.cpp
 * Purpose: Build a Linked List and test the funciton.
 * Author: Johnny Lee
 * Date: 2020.04.15
***/
#include <iostream>
#include <string>

using namespace std;

class LinkedList;

class ListNode{
    private:
        int data;
        ListNode *next;
    public:
        ListNode() : data(0), next(0){};
        ListNode(int a) : data(a), next(0){};

        friend class LinkedList;        
        //ListNode宣告LinkedList為朋友，因此LinkedList可讀取ListNode內data與*next
};

class LinkedList{
    private:
        ListNode *first;
    public:
        LinkedList() : first(0){};
        void PrintList();           // 印出list的所有資料
        void Push_front(int x);     // 在list的開頭新增node
        void Push_back(int x);      // 在list的尾巴新增node
        void Delete(int x);         // 刪除list中的 int x
        void Clear();               // 把整串list刪除
        void Reverse();             // 將list反轉
        int GetMiddleNode();        // 取得正中間的node值
};

void LinkedList :: PrintList(){
    if (first == nullptr) {
        cout << "List is empty. \n";
        return;
    }

    ListNode *current = first;
    while (current != nullptr){                 // 若current(當前Node)為Null則跳出迴圈不print
        cout << current->data << " ";
        current = current -> next;
    }
    cout << endl;
}

void LinkedList :: Push_front(int value){
    ListNode *newNode = new ListNode(value);    // 配置新的記憶體
    newNode->next = first;                      // 先把first接在newNode後面
    first = newNode;                            // 再把first指向newNode所指向的記憶體位置
}

void LinkedList :: Push_back(int value){
    ListNode *newNode = new ListNode(value);
    
    if(first == nullptr){
        first = newNode;
        return;
    }

    ListNode *current = first;                  // 必須先宣告為First 讓current 從頭開始找
    while (current -> next != nullptr){         // 若current->next(下一個Node)為NULL
        current = current->next;                // 則current為List結尾
    }

    current->next = newNode;
}

void LinkedList :: Delete(int value){
    ListNode *current = first,
             *previous = nullptr;

    // 在list中使用while搜尋直到指向NULL(List中沒有value值)或
    // 找到欲刪除的value為current
    // previous 為上一步的current
    while (current != nullptr && current->data != value){
        previous = current;
        current = current->next;
    }

    // Linked List中沒有要刪除的node 
    if (current == nullptr){
        cout << "There is no " << value << " in the list.\n";
    }
    // 欲刪除的Node位於List中的第一個，因為Previous為null故須特別處理
    else if(current == first){
        first = current->next;
        delete current;
        current = nullptr;
    }
    else {
        previous->next = current->next;
        delete current;
        current = nullptr;
    }
    new ListNode(value);
}

void LinkedList:: Clear(){

    while(first != nullptr){
        ListNode *current = first;
        first = first->next;
        delete current;
        current = nullptr;
    }
}
void LinkedList::Reverse(){

    // List內沒有資料或僅有一個數值
    if (first == nullptr || first->next == nullptr) {
        return;
    }

    ListNode *previous = nullptr,
             *current = first,
             *preceding = first->next;

    while (preceding != nullptr) {
        current->next = previous;      // 把current->next轉向
        previous = current;            // previous往後挪
        current = preceding;           // current往後挪
        preceding = preceding->next;   // preceding往後挪
    }                                  // preceding更新成NULL即跳出while loop

    current->next = previous;          // 此時current位於最後一個node, 將current->next轉向
    first = current;                   // 更新first為current
}

int LinkedList :: GetMiddleNode(){
    ListNode *Slow_ptr = first;
    ListNode *Fast_ptr = first;

    if (first == nullptr){
        cout << "The LinkedList is empty.";
        return 0;
    }

    if (first -> next == nullptr){
        return first->data;
    }

    // 設計兩個指標，快的是慢的兩倍速度進行搜尋，當快指標指向結尾時
    // 慢指標即位在LinkedList中間
    while (Fast_ptr != nullptr && Fast_ptr->next != nullptr){   
        // 若Fast為null則到達結尾，若Fast->next為null亦為結尾，
        // 若不是&&則可能發生沒有Fast->next->next的狀態造成程式無法執行
        Fast_ptr = Fast_ptr->next->next;
        Slow_ptr = Slow_ptr->next;
    }
    return Slow_ptr->data;
}


int main(void)
{
    LinkedList list;     // 建立LinkedList的object
    list.PrintList();    // 目前list是空的
     
    list.Push_front(5);
    list.Push_back(2);
    list.Push_front(9);
    list.Push_back(7);
    list.PrintList();
    list.Delete(8);
    list.Delete(9);
    list.PrintList();
    list.Push_front(9);
    list.Push_back(16);
    list.PrintList();
    list.Reverse();
    list.PrintList();
    cout << "The middle node is " << list.GetMiddleNode() << endl;
    list.Clear();
    list.PrintList();

    system("pause");
    return 0;
}