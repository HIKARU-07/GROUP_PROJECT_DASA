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
    cout << "Added: " << added << "\n";
    assert(added == 6);
    assert(svc.size() == 6);

    // Test 1: lấy suất 09:00-20:00, sắp theo StartTime -> ID -> Room
    auto r = svc.search("M1", "2026-10-01", "09:00", "20:00");
    assert(r.size() == 3);
    assert(r[0].id == "S1");   // 09:00, S1 < S2
    assert(r[1].id == "S2");
    assert(r[2].id == "S3");   // 19:30

    // Test 2: T1 == T2, khớp đúng 2 suất 09:00
    assert(svc.search("M1", "2026-10-01", "09:00", "09:00").size() == 2);

    // Test 3: không có phim / T1 > T2 / ngày không có lịch -> rỗng
    assert(svc.search("M9", "2026-10-01", "00:00", "23:59").empty());
    assert(svc.search("M1", "2026-10-01", "20:00", "09:00").empty());
    assert(svc.search("M1", "2026-10-05", "00:00", "23:59").empty());

    // Test 4: suất qua đêm (endMin < startMin) vẫn in đúng
    auto n = svc.search("M1", "2026-10-01", "23:00", "23:59");
    assert(n.size() == 1 && n[0].toLine() == "S4|CGV|R3|23:00|01:00");

    // Test 5: thêm sau khi đã search -> phải sắp xếp lại
    svc.add("M1", "2026-10-01", "S0", "CGV", "R0", "08:00", "10:00");
    assert(svc.search("M1", "2026-10-01", "00:00", "23:59")[0].id == "S0");

    // Test 6: đọc từng dòng query từ file
    ifstream qin("D:/ITlord/DASA/GROUP_PROJECT_DASA/data/showtimes.txt");
    string line;
    while (getline(qin, line))
        for (auto& s : svc.searchFromLine(line)) cout << s.toLine() << "\n";

    cout << "ALL PASSED\n";
}