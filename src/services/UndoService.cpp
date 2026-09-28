#include "UndoService.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;
//Xử lý thông tin đọc input timestamp
//Input: YYYY-mm-dd HH:MM
time_t UndoService::toTime(const string& timestamp) const{
    tm t = {};
    istringstream ss(timestamp);
    ss >> get_time(&t, "%Y-%m-%d %H:%M");
    if (ss.fail()){
        return -1;
    }
    return mktime(&t);
}
//Kiểm tra hành động có quá 15 phút hay không 
bool UndoService::over15Minutes(const string& timestamp) const {
    time_t current = toTime(currentTime); //thời gian xét 
    time_t action = toTime(timestamp); //thời gian thực hiện hành động
    
    //timestamp không hợp lê
    if (current == -1 || action == -1) return false;
    
    double diff = difftime(current, action); //tính khoảng cách thời gian
    return diff > 15 * 60;
}
//Đọc dữ liệu input từ file .txt
void UndoService::loadInput(const string& filename){
    ifstream file(filename);
    if(!file.is_open()){
        cout << "Can't open file." << endl;
        return;
    }
    int N;
    file >> N;
    file.ignore();
    //Đọc thời gian hiện tại
    getline(file, currentTime);
    for (int i = 0; i < N; i++){
        string line;
        getline(file, line);
        // Tìm dấu |
        size_t pos = line.find('|');
        UndoAction action;
        // Không tìm thấy |
        if (pos == string::npos)
        {
            continue;
        }
        //Bên trái |
        action.operation = line.substr(0, pos);
        //Bên phải |
        action.timestamp = line.substr(pos + 1);
        //Xóa khoảng tráng bên timestamp
        if (!action.timestamp.empty() && action.timestamp[0] == ' '){
            action.timestamp.erase(0, 1);
        }
        //Đưa hành động vào stack
        undoStack.push(action);
    }  
    file.close();  
}
//Thực hiên Undo theo LIFO
void UndoService::undo(){
    //Xét stack rỗng
    if (undoStack.empty()){
        cout << "FAILED DATA" << '\n';
        return;
    }
    UndoAction action;
    undoStack.peek(action);
    time_t current = toTime(currentTime);
    time_t actionTime = toTime(action.timestamp);
    //Xử lí timestamp không hợp lệ
    if (current == -1 || actionTime == -1){
        undoStack.pop(action);
        cout << "FAILED DATA" << endl;
        return;
    }
    //Xử lí khi hành động vượt quá 15 phút
    if (over15Minutes(action.timestamp)){
        undoStack.pop(action);
        cout << "FAILED DATA" << endl;
        return;
    }
    //Hành động hợp lệ 
    undoStack.pop(action);
    
    //Thực hiện Undo

    stringstream ss(action.operation);

    string command;
    string target;
    
    ss >> command >> target;

    if (command == "SELECT_SEAT"){
        cout << "Undo SELECT_SEAT: "
             << target << endl;
        cout << "SUCCESSFUL OPERATION" << endl;

        return;
    }

    if (command == "ADD_COMBO")
    {
        cout << "Undo ADD_COMBO: "
             << target << endl;

        cout << "SUCCESSFUL OPERATION" << endl;

        return;
    }
    // Operation không hợp lệ
    cout << "FAILED DATA" << endl;
}
void UndoService::printStack() const
{
    cout << "\nCurrent Stack:" << endl;

    if (undoStack.empty())
    {
        cout << "STACK EMPTY" << endl;
        return;
    }

    undoStack.print();
}