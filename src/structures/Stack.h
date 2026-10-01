#pragma once

#include <iostream>
using namespace std;

template <typename T>
class Stack
{
private:

    // Node của Linked List
    struct Node
    {
        T data;
        Node* next;

        Node(const T& value)
        {
            data = value;
            next = nullptr;
        }
    };

    // Node ở đầu Stack
    Node* topNode;

    // Số phần tử
    int count;

    // Tối đa 10 phần tử
    static const int MAX_SIZE = 10;

public:

    // Constructor
    Stack()
    {
        topNode = nullptr;
        count = 0;
    }

    // Destructor
    ~Stack()
    {
        clear();
    }

    // Thêm phần tử
    bool push(const T& value)
    {
        if (count == MAX_SIZE)
        {
            return false;
        }

        Node* newNode = new Node(value);

        newNode->next = topNode;
        topNode = newNode;

        count++;

        return true;
    }

    // Xóa phần tử đầu
    bool pop(T& value)
    {
        if (topNode == nullptr)
        {
            return false;
        }

        Node* temp = topNode;

        value = temp->data;
        topNode = topNode->next;

        delete temp;

        count--;

        return true;
    }

    // Xem phần tử đầu
    bool peek(T& value) const
    {
        if (topNode == nullptr)
        {
            return false;
        }

        value = topNode->data;

        return true;
    }

    // Kiểm tra rỗng
    bool empty() const
    {
        return topNode == nullptr;
    }

    // Kiểm tra đầy
    bool full() const
    {
        return count == MAX_SIZE;
    }

    // Lấy số phần tử
    int size() const
    {
        return count;
    }

    // Lấy phần tử theo vị trí
    bool get(int index, T& value) const
    {
        if (index < 0 || index >= count)
        {
            return false;
        }

        Node* current = topNode;

        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }

        value = current->data;

        return true;
    }

    // Xóa toàn bộ Stack
    void clear()
    {
        while (topNode != nullptr)
        {
            Node* temp = topNode;

            topNode = topNode->next;

            delete temp;
        }

        count = 0;
    }
};