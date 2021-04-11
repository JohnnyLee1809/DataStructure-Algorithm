/***
 * Function name: DSA_DoublyLinkedList.cpp
 * Purpose: Build a Doubly Linked List and test the funciton.
 * Author: Johnny Lee
 * Date: 2020.05.27
***/
#include <iostream>
#include <string>

using namespace std;

class DoubleLinkedList;

class ListNode{
    private:
        int data;
        ListNode *prev;
        ListNode *next;
    public:
        ListNode() : data(0), prev(0), next(0){};
        ListNode(int a) : data(a), prev(0), next(0){};
        int getdata();
        friend class DoubleLinkedList;
};

int ListNode::getdata(){
    return data;
}

class DoubleLinkedList{
    private:
        ListNode *first;
    public:
        DoubleLinkedList() : first(0){};
        
        void PrintList();           // 印出list的所有資料
        void Push_front(int x);     // 在list的開頭新增node
        void Push_back(int x);      // 在list的尾巴新增node

        ListNode* getfirst();
        ListNode* FindPosition(ListNode *p,int n);
        void Add_After(ListNode *p, int x);         // 在p位置node 後加上x node   
        void Add_Before(ListNode *p, int x);        // 在p位置node 前加上x node
        void Delete_Here(ListNode *p);              // 刪除p位置node

        void Delete(int x);         // 刪除list中的 int x
        void Clear();               // 把整串list刪除
        void Reverse();             // 將list反轉
};

void DoubleLinkedList :: PrintList(){
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

void DoubleLinkedList :: Push_front(int value){    
    //ListNode *current = first;                  // 如果使用*current 而非first 則無法將Node Link起來
    ListNode *newNode = new ListNode(value);        
 
    newNode->next = first;
    newNode->prev = nullptr;

    if (first != nullptr)
        first->prev = newNode;
    
    first = newNode;
}

void DoubleLinkedList :: Push_back(int value){
    ListNode *newNode = new ListNode(value);

    if(first == nullptr){
        newNode->prev = nullptr;
        first = newNode;
        return;
    }

    ListNode *current = first;                  // 必須先宣告為First 讓current 從頭開始找
    while (current -> next != nullptr){         // 若current->next(下一個Node)為NULL
        current = current->next;                // 則current為List結尾
    }
    current->next = newNode;
    newNode->prev = current;
}

void DoubleLinkedList :: Add_After(ListNode *node_position, int value){
    if (node_position == nullptr){
        cout << "Previous node position cannot be NULL." << endl;
        return;
    }
    
    ListNode *newNode = new ListNode(value);

    newNode->next = node_position->next;
    node_position->next = newNode;
    newNode->prev = node_position;

    if(newNode->next != nullptr){
        newNode->next->prev = newNode;      // 若下一個並非List結尾，則須讓下一個node的prev指標指向自己
    }
}

void DoubleLinkedList :: Delete_Here(ListNode *node_position){
    if (node_position == nullptr){
        cout << "Previous node position cannot be NULL." << endl;
        return;
    }

    if (first == node_position){
        first = node_position->next;
    }   

    // 需考慮node_position前後位置才能進行取代
    if (node_position->next != nullptr){
         node_position->next->prev = node_position->prev;  // 下一個node的prev指向prev 
    }
    if (node_position->prev != nullptr){
         node_position->prev->next = node_position->next;  // 上一個node的next指向next
    }

    delete node_position;
}
ListNode* DoubleLinkedList::getfirst(){     //回傳first位置避免first在其他地方被修改
    return first;
}  

// 找到第n個node的位置
ListNode* DoubleLinkedList::FindPosition(ListNode *node_position, int n){     //必須回傳ListNode的指標才會是找到該list內部的位置
    //cout << "Orininal node add = " << node_position << endl;         //若回傳ListNode物件則 main 中的currentnode將會創造一個新的記憶體位置
    if (node_position == nullptr){
        cout << "There is no node." << endl;
        return 0;
    }
    if (node_position->next == nullptr){
        cout << "There is no next node." << endl;
        return node_position;
    }

    for (int i = 0; i < n; i++){
        node_position = node_position->next;
    }
    //cout << "after change node add = " << node_position << endl;
    return node_position;
}  

void DoubleLinkedList::Reverse(){
    // List內沒有資料或僅有一個數值
    if (first == nullptr || first->next == nullptr) {
        return;
    }

    ListNode *temp = nullptr,
             *current = first;          // 建立temp node 作為交換空node
                                        // current 確認交換至哪一個
    while (current != nullptr) {
        temp = current->prev;           // temp 儲存 current prev指標
        current->prev = current->next;  // current prev與next指標互換
        current->next = temp;           // current next讀取 temp所存的prev指標 

        current = current->prev;        // 由於原本的next已變為prev, current指向prev換為下一個Node繼續交換prev 與 next
    }                                   // current更新成NULL即跳出while loop
    
    if(temp != nullptr){
        first = temp->prev;
    }
}


int main(void)
{
    DoubleLinkedList list;      // 建立LinkedList的object
    
    list.PrintList();           // 目前list是空的
    list.Push_front(5);
    list.Push_front(9);
    list.PrintList();           // list: 9 5
    list.Push_back(13);
    list.PrintList();           // list: 9 5 13

    ListNode *current_node;
    current_node = list.FindPosition(list.getfirst(), 1);     // current node = 5
    cout << "Address is " << current_node << "; Data is " << current_node->getdata() << endl;

    list.Add_After(current_node, 50);               // list: 9 5 50 13
    list.PrintList();

    current_node = list.FindPosition(list.getfirst(), 2);     // current node = 50
    cout << "Address is " << current_node << "; Data is " << current_node->getdata() << endl;

    list.Delete_Here(current_node);                 // list: 9 5 13
    list.PrintList();
    list.Reverse();
    list.PrintList();

    system("pause");
    return 0;
}