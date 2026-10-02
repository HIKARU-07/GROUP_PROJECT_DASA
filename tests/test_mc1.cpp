//   g++ -std=c++17 -O2 test_mc1.cpp ../src/services/TicketService.cpp -o test_mc1
//   ./test_mc1
//
// data/tickets.txt:        dong 1 = so dong ve, cac dong sau co 8 truong ngan cach bang '|'
//   bookingId|customerName|movieName|showtime|cinemaRoom|seats|ticketStatus|cinemaAddress
// data/mc1_testcases.txt:  dong 1 = so test, cac dong sau:
//   bookingId|currentTime|KET_QUA_MONG_DOI
 
#include "../src/services/TicketService.h"
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
 
using namespace std;
 
// Duong dan toi 2 file txt 
const string TICKET_FILE = "D:/DSA/DO_AN_CUOI_KY/GROUP_PROJECT_DASA-main/data/tickets.txt";
const string TESTCASE_FILE = "D:/DSA/DO_AN_CUOI_KY/GROUP_PROJECT_DASA-main/data/mc1_testcases.txt";
 
string resultToString(CheckInResult res) {
    switch (res) {
        case CheckInResult::VALID:          return "VALID";
        case CheckInResult::USED:           return "USED";
        case CheckInResult::EXPIRED:        return "EXPIRED";
        case CheckInResult::NOT_FOUND:      return "NOT_FOUND";
        case CheckInResult::INVALID_FORMAT: return "INVALID_FORMAT";
    }
    return "UNKNOWN";
}
 
// Tach mot dong theo dau '|'
vector<string> split(const string& line) {
    vector<string> parts;
    stringstream ss(line);
    string item;
    while (getline(ss, item, '|')) parts.push_back(item);
    if (!line.empty() && line.back() == '|') parts.push_back("");
    return parts;
}
 
// Doc file, tra ve cac dong du lieu (bo dong dau, dong trong, dong '#')
vector<string> readLines(const string& path) {
    vector<string> lines;
    ifstream fin(path);
    if (!fin) return lines;
 
    string line;
    bool firstLine = true;
    while (getline(fin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty() || line[0] == '#') continue;
        if (firstLine) { firstLine = false; continue; }   // dong dau = so luong
        lines.push_back(line);
    }
    return lines;
}
 
int main() {
    // 1. Doc file ve
    vector<string> ticketLines = readLines(TICKET_FILE);
    if (ticketLines.empty()) {
        cout << "Khong doc duoc " << TICKET_FILE << "\n";
        return 2;
    }
 
    TicketService service(ticketLines.size());
    for (const string& line : ticketLines) {
        vector<string> f = split(line);
        if (f.size() != 8) continue;
        service.addTicket(Ticket{f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7]});
    }
    cout << "Doc " << ticketLines.size() << " dong ve, ticketCount = "
         << service.getTicketCount() << "\n";
 
    // 2. Doc file test va chay
    vector<string> testLines = readLines(TESTCASE_FILE);
    if (testLines.empty()) {
        cout << "Khong doc duoc " << TESTCASE_FILE << "\n";
        return 2;
    }
 
    int failed = 0;
    for (const string& line : testLines) {
        vector<string> f = split(line);
        if (f.size() != 3) continue;
 
        string result = resultToString(service.checkTicket(f[0], f[1]));
        if (result != f[2]) {
            failed++;
            cout << "SAI: " << f[0] << "|" << f[1]
                 << " -> " << result << " (mong doi " << f[2] << ")\n";
        }
    }
 
    cout << "\nTong: " << testLines.size() << " test, "
         << (testLines.size() - failed) << " dung, " << failed << " sai\n";
    return failed == 0 ? 0 : 1;
}
 