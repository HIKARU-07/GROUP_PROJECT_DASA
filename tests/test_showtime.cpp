#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include "../src/services/ShowtimeService.h"
using namespace std;

int main() {
    ShowtimeService svc;
    long long added = svc.loadFromFile("D:/ITlord/DASA/GROUP_PROJECT_DASA/data/showtimes.txt");
    if (added < 0){
        cout << "Khong mo duoc file" << endl;
        return -1;
    }
    cout << "Da nap thanh cong so suat chieu: " << added << endl;

    ifstream qin("D:/ITlord/DASA/GROUP_PROJECT_DASA/data/showtimes.txt");
    if (!qin){
        cout << "Khong mo duoc file truy van" << endl;
        return -1;
    }

    string line;
    while (getline(qin, line))
        for (auto& s : svc.searchFromLine(line)) cout << s.toLine() << endl;
    cout << "ALL PASSED" << endl;
}