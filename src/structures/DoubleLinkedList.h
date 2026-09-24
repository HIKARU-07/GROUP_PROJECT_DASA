#pragma once

#include <vector>

template <typename T>
class DoubleLinkedList
{
private:
    //cấu trúc Node:
    struct Node
    {
        T value;
        Node* prev;
        Node* next;

        Node(const T& value)
        {
            this->value = value;
            this->prev = nullptr;
            this->next = nullptr;
        }
    };

    Node* head;
    Node* tail;
    long long size;

public:
    // Hàm dựng 
    DoubleLinkedList(){
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    // Hàm hủy 
    ~DoubleLinkedList(){
        clear();
    }

    // Xóa danh sách
    void clear(){
        Node* cur = head;
        while (cur != nullptr){
            Node* nextNode = cur->next;
            delete cur;
            cur = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        sizeList = 0;
    }

    // Thêm phần tử vào đầu danh sách
    void pushFront(const T& val){
        Node* newNode = new Node(val);

        newNode->next = head;

        if (head != nullptr){
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        sizeList++;     
    }

    // Thêm phần tử vào cuối danh sách
    void pushBack(const T& val){
        Node* newNode = new Node(val);
        if (head == nullptr){
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        sizeList++;
    }
    // Tìm phần tử có trong List hay không

    // Xóa phần tử bất kỳ trong danh sách
    void Delete( const T& val){
        if (head == nullptr) return;
        if (head->value == val)
        {
            Node *target = head;
            head = head->next;

            if (head == nullptr){
                tail = nullptr;
            }
            delete target;
            return;
        }
        Node *temp = head;
        while ( temp->next != nullptr && temp-> next-> value != val){
            temp= temp -> next;
        }
        if (temp->next == nullptr) {
            return; 
        }
        Node *target = temp-> next;
        temp -> next = target-> next;
        if (target == tail)
            {
                tail = temp;
            }
        delete target;
    }

    // Trả về vị trí của phần tử cần tìm trong danh sách
    Node* Search( const T& value){
        Node *temp = head;
        while (temp != nullptr)
        {
            if (temp->value == value)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    // Trả về kích thước list
    long long getSize() const {
        return sizeList;
    }
};
