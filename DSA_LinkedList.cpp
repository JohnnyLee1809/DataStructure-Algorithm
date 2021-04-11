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
        //ListNode�ŧiLinkedList���B�͡A�]��LinkedList�iŪ��ListNode��data�P*next
};

class LinkedList{
    private:
        ListNode *first;
    public:
        LinkedList() : first(0){};
        void PrintList();           // �L�Xlist���Ҧ����
        void Push_front(int x);     // �blist���}�Y�s�Wnode
        void Push_back(int x);      // �blist�����ڷs�Wnode
        void Delete(int x);         // �R��list���� int x
        void Clear();               // ����list�R��
        void Reverse();             // �Nlist����
        int GetMiddleNode();        // ���o��������node��
};

void LinkedList :: PrintList(){
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

void LinkedList :: Push_front(int value){
    ListNode *newNode = new ListNode(value);    // �t�m�s���O����
    newNode->next = first;                      // ����first���bnewNode�᭱
    first = newNode;                            // �A��first���VnewNode�ҫ��V���O�����m
}

void LinkedList :: Push_back(int value){
    ListNode *newNode = new ListNode(value);
    
    if(first == nullptr){
        first = newNode;
        return;
    }

    ListNode *current = first;                  // �������ŧi��First ��current �q�Y�}�l��
    while (current -> next != nullptr){         // �Ycurrent->next(�U�@��Node)��NULL
        current = current->next;                // �hcurrent��List����
    }

    current->next = newNode;
}

void LinkedList :: Delete(int value){
    ListNode *current = first,
             *previous = nullptr;

    // �blist���ϥ�while�j�M������VNULL(List���S��value��)��
    // �����R����value��current
    // previous ���W�@�B��current
    while (current != nullptr && current->data != value){
        previous = current;
        current = current->next;
    }

    // Linked List���S���n�R����node 
    if (current == nullptr){
        cout << "There is no " << value << " in the list.\n";
    }
    // ���R����Node���List�����Ĥ@�ӡA�]��Previous��null�G���S�O�B�z
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

    // List���S����ƩζȦ��@�Ӽƭ�
    if (first == nullptr || first->next == nullptr) {
        return;
    }

    ListNode *previous = nullptr,
             *current = first,
             *preceding = first->next;

    while (preceding != nullptr) {
        current->next = previous;      // ��current->next��V
        previous = current;            // previous���ᮿ
        current = preceding;           // current���ᮿ
        preceding = preceding->next;   // preceding���ᮿ
    }                                  // preceding��s��NULL�Y���Xwhile loop

    current->next = previous;          // ����current���̫�@��node, �Ncurrent->next��V
    first = current;                   // ��sfirst��current
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

    // �]�p��ӫ��СA�֪��O�C���⭿�t�׶i��j�M�A��֫��Ы��V������
    // �C���ЧY��bLinkedList����
    while (Fast_ptr != nullptr && Fast_ptr->next != nullptr){   
        // �YFast��null�h��F�����A�YFast->next��null�笰�����A
        // �Y���O&&�h�i��o�ͨS��Fast->next->next�����A�y���{���L�k����
        Fast_ptr = Fast_ptr->next->next;
        Slow_ptr = Slow_ptr->next;
    }
    return Slow_ptr->data;
}


int main(void)
{
    LinkedList list;     // �إ�LinkedList��object
    list.PrintList();    // �ثelist�O�Ū�
     
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