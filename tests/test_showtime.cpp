#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include "../src/services/ShowtimeService.h"
using namespace std;


// Đọc '\r' ở cuối dòng
static void stripCR(string& line) {
    if (!line.empty() && line.back() == '\r') line.pop_back();
}


int main() {
    ShowtimeService svc;

    long long added = svc.loadFromFile("D:/ITlord/DASA/GROUP_PROJECT_DASA/data/showtimes.txt");
    if (added < 0) {
        cout << "Khong mo duoc file" << endl;
        return -1;
    }
    cout << "Da nap thanh cong so suat chieu: " << added << endl;
 
    // Truy vấn nhập từ bàn phím
    while (true) {
        string movieId, date, t1, t2;
 
        cout << "\nNhap MovieID (hoac 'exit' de thoat): ";
        cin >> movieId;
        if (movieId == "exit") break;
 
        cout << "Nhap ngay (YYYY-MM-DD): ";
        cin >> date;
        cout << "Nhap gio bat dau T1 (HH:MM): ";
        cin >> t1;
        cout << "Nhap gio ket thuc T2 (HH:MM): ";
        cin >> t2;
 
        vector<Showtime> result = svc.search(movieId, date, t1, t2);
        if (result.empty()) {
            cout << "NOT FOUND!!" << endl;
        } else {
            for (const Showtime& s : result)
                cout << s.toLine() << endl;
        }
    }
    return 0;
}