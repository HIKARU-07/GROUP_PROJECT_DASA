#pragma once

#include <string>
#include <ctime>
#include "../models/UndoAction.h"
#include "../structures/Stack.h"
using namespace std;
class UndoService
{
private:
    // Stack lưu lịch sử Undo
    Stack<UndoAction> undoStack;

    // Thời gian hiện tại
    string currentTime;

    // Chuyển YYYY-MM-DD HH:MM thành time_t
    time_t toTime(const string& timestamp) const;

    // Kiểm tra action có quá 15 phút không
    bool over15Minutes(const string& timestamp) const;

public:
    // Đọc dữ liệu từ input.txt
    void loadInput(const string& filename);

    // Thực hiện một lệnh UNDO
    void undo();

    // In Stack sau khi thực hiện hành động
    void printStack() const;

    void run();
};