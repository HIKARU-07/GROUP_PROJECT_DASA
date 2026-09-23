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
    bool contains

    // Trả về kích thước list
    long long getSize() const {
        return sizeList;
    }
};
