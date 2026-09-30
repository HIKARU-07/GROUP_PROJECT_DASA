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
        size = 0;
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
        size++;     
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
        size++;
    }
    // Xóa phần tử cuối danh sách, trả về false nếu danh sách rỗng
    bool popBack(){
        if (tail == nullptr) return false;
        Node* target = tail;
        tail = tail->prev;
        if (tail != nullptr){
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete target;
        size--;
        return true;
    }

    // Xóa phần tử bất kỳ trong danh sách
    void Delete(const T& val) {
        if (head == nullptr) return;

        if (head->value == val) {
            Node* target = head;
            head = head->next;

            if (head != nullptr) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            delete target;
            size--;
            return;
        }
        Node* target = head->next;
        while (target != nullptr && target->value != val) {
            target = target->next;
        }
        if (target == nullptr) {
            return;
        }
        target->prev->next = target->next;
        if (target->next != nullptr) {
            target->next->prev = target->prev;
        } else {
            tail = target->prev;
        }
        delete target;
        size--;
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

    // Trả về phần tử thứ k trong danh sách (0 là phần tử đầu tiên)
    T getAt(long long index) const {
        Node* cur = head;
        for (long long i = 0; i < index; i++){
            cur = cur->next;
        }
        return cur->value;
    }

    // Trả về kích thước list
    long long getSize() const {
        return size;
    }

    // Kiểm tra rỗng
    bool isEmpty(){
        return sizeList == 0;
    }
};
