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
        
        void PrintList();           // �L�Xlist���Ҧ����
        void Push_front(int x);     // �blist���}�Y�s�Wnode
        void Push_back(int x);      // �blist�����ڷs�Wnode

        ListNode* getfirst();
        ListNode* FindPosition(ListNode *p,int n);
        void Add_After(ListNode *p, int x);         // �bp��mnode ��[�Wx node   
        void Add_Before(ListNode *p, int x);        // �bp��mnode �e�[�Wx node
        void Delete_Here(ListNode *p);              // �R��p��mnode

        void Delete(int x);         // �R��list���� int x
        void Clear();               // ����list�R��
        void Reverse();             // �Nlist����
};

void DoubleLinkedList :: PrintList(){
    if (first == nullptr) {
        cout << "List is empty. \n";
        return;
    }

    ListNode *current = first;
    while (current != nullptr){                 // �Ycurrent(��eNode)��Null�h���X�j�餣print
        cout << current->data << " ";
        current = current -> next;
    }
    cout << endl;
}

void DoubleLinkedList :: Push_front(int value){    
    //ListNode *current = first;                  // �p�G�ϥ�*current �ӫDfirst �h�L�k�NNode Link�_��
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

    ListNode *current = first;                  // �������ŧi��First ��current �q�Y�}�l��
    while (current -> next != nullptr){         // �Ycurrent->next(�U�@��Node)��NULL
        current = current->next;                // �hcurrent��List����
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
        newNode->next->prev = newNode;      // �Y�U�@�ӨëDList�����A�h�����U�@��node��prev���Ы��V�ۤv
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

    // �ݦҼ{node_position�e���m�~��i����N
    if (node_position->next != nullptr){
         node_position->next->prev = node_position->prev;  // �U�@��node��prev���Vprev 
    }
    if (node_position->prev != nullptr){
         node_position->prev->next = node_position->next;  // �W�@��node��next���Vnext
    }

    delete node_position;
}
ListNode* DoubleLinkedList::getfirst(){     //�^��first��m�קKfirst�b��L�a��Q�ק�
    return first;
}  

// ����n��node����m
ListNode* DoubleLinkedList::FindPosition(ListNode *node_position, int n){     //�����^��ListNode�����Ф~�|�O����list��������m
    //cout << "Orininal node add = " << node_position << endl;         //�Y�^��ListNode����h main ����currentnode�N�|�гy�@�ӷs���O�����m
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
    // List���S����ƩζȦ��@�Ӽƭ�
    if (first == nullptr || first->next == nullptr) {
        return;
    }

    ListNode *temp = nullptr,
             *current = first;          // �إ�temp node �@���洫��node
                                        // current �T�{�洫�ܭ��@��
    while (current != nullptr) {
        temp = current->prev;           // temp �x�s current prev����
        current->prev = current->next;  // current prev�Pnext���Ф���
        current->next = temp;           // current nextŪ�� temp�Ҧs��prev���� 

        current = current->prev;        // �ѩ�쥻��next�w�ܬ�prev, current���Vprev�����U�@��Node�~��洫prev �P next
    }                                   // current��s��NULL�Y���Xwhile loop
    
    if(temp != nullptr){
        first = temp->prev;
    }
}


int main(void)
{
    DoubleLinkedList list;      // �إ�LinkedList��object
    
    list.PrintList();           // �ثelist�O�Ū�
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