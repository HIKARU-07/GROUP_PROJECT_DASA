#pragma once

#include <vector>

using namespace std;

template <typename T>
class Stack //thiết kế stack bằng vector
{
private:
    vector<T> data;
    int capacity;

public:
    Stack(int cap = 10) //quy định chỉ chứa tối đa 10 lệnh thao tác
    {
        capacity = cap;
    }
    void push(const T& value)
    {
        data.push_back(value);

        if (data.size() > capacity)
            data.erase(data.begin());
    }
    bool pop(T& value)
    {
        if (data.empty())
            return false;

        value = data.back();
        data.pop_back();

        return true;
    }
    bool peek(T& value) const
    {
        if (data.empty())
            return false;

        value = data.back();
        return true;
    }
    bool empty() const
    {
        return data.empty();
    }
    int size() const
    {
        return data.size();
    }
};