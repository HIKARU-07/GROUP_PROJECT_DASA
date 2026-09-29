#include "ShowtimeService.h"

#include <algorithm>
#include <cctype>
#include <fstream>
using namespace std;

//Kiểm tra năm nhuận
bool isLeapYear(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

//Các ngày ứng với từng tháng
int daysInMonth(int y, int m) {
    static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && isLeapYear(y)) return 29;
    return days[m - 1];
}

//Kiểm tra đầu vào có toàn chữ số không
bool allDigits(const string& s, size_t from, size_t count) {
    for (size_t i = from; i < from + count; i++)
        if (!isdigit(static_cast<unsigned char>(s[i]))) return false;
    return true;
}


// YYYY-MM-DD, kiểm tra định dạng (tháng 1-12, ngày đúng theo tháng, năm nhuận)
bool validDate(const string& d) {
    if (d.size() != 10 || d[4] != '-' || d[7] != '-') return false;
    if (!allDigits(d, 0, 4) || !allDigits(d, 5, 2) || !allDigits(d, 8, 2)) return false;
    int y = stoi(d.substr(0, 4));
    int m = stoi(d.substr(5, 2));
    int day = stoi(d.substr(8, 2));
    if (y < 1 || m < 1 || m > 12) return false;
    return day >= 1 && day <= daysInMonth(y, m);
}


// Đổi dạng HH:MM sang 00:00, hoặc -1 nếu sai
int parseTime(const string& t) {
    if (t.size() != 5 || t[2] != ':') return -1;
    if (!allDigits(t, 0, 2) || !allDigits(t, 3, 2)) return -1;
    int h = stoi(t.substr(0, 2));
    int m = stoi(t.substr(3, 2));
    if (h > 23 || m > 59) return -1;
    return h * 60 + m;
}

//Đổi 00:00 -> HH:MM
string formatTime(int minutes) {
    char buf[16];
    snprintf(buf, sizeof(buf), "%02d:%02d", minutes / 60, minutes % 60);
    return buf;
}


// MovieID: 1-50 ký tự, không chứa khoảng trắng và '|'
bool validMovieId(const string& s) {
    if (s.empty() || s.size() > 50) return false;
    for (char c : s)
        if (isspace(static_cast<unsigned char>(c)) || c == '|') return false;
    return true;
}


// Tách chuỗi theo dấu phân cách, giữ cả phần tử rỗng
vector<string> split(const string& s, char sep) {
    vector<string> parts;
    size_t start = 0;
    while (true) {
        size_t pos = s.find(sep, start);
        if (pos == string::npos) {
            parts.push_back(s.substr(start));
            break;
        }
        parts.push_back(s.substr(start, pos - start));
        start = pos + 1;
    }
    return parts;
}

//Xóa kí tự /r ở cuối dòng
void stripCR(string& line) {
    if (!line.empty() && line.back() == '\r') line.pop_back();  // file kiểu Windows
}

//Kiểm tra chuỗi toàn chữ số
bool isNumber(const string& s) {
    return !s.empty() && allDigits(s, 0, s.size());
}

//Tạo khóa dạng movieID
string makeKey(const string& movieId, const string& date) {
    return movieId + '|' + date;
}


// Thứ tự trong một nhóm: StartTime, rồi ShowtimeID, rồi CinemaRoom
bool byStartIdRoom(const Showtime& a, const Showtime& b) {
    if (a.startMin != b.startMin) return a.startMin < b.startMin;
    if (a.id != b.id) return a.id < b.id;
    return a.room < b.room;
}

//Chuyển một xuất chiếu thành -> id|cinemaName|room|HH:MM|HH:MM
string Showtime::toLine() const {
    return id + '|' + cinemaName + '|' + room + '|' + formatTime(startMin) + '|' + formatTime(endMin);
}

//Thêm một suất chiếu vào hệ thống
bool ShowtimeService::add(const string& movieId, const string& date,
                          const string& showtimeId, const string& cinemaName,
                          const string& room, const string& startTime,
                          const string& endTime) {
    if (!validMovieId(movieId) || !validDate(date)) return false;
    if (showtimeId.empty() || cinemaName.empty() || room.empty()) return false;

    int start = parseTime(startTime);
    int end = parseTime(endTime);
    if (start < 0 || end < 0) return false;

    Showtime s;
    s.id = showtimeId;
    s.cinemaName = cinemaName;
    s.room = room;
    s.startMin = start;
    s.endMin = end;

    // Tìm nhóm (MovieID, Date), chưa có thì tạo mới
    const std::string key = makeKey(movieId, date);
    int group;
    const int* found = index_.find(key);
    if (found != nullptr) {
        group = *found;
    } else {
        group = static_cast<int>(groups_.size());
        groups_.emplace_back();
        sorted_.push_back(1);
        index_.put(key, group);
    }

    groups_[group].push_back(s);
    sorted_[group] = 0;  // nhóm cần sắp xếp lại trước lần tìm kế tiếp
    total_++;
    return true;
}

//Đọc một dòng dạng MovieID|Date|ShowtimeID|Cinema|Room|Start|End
bool ShowtimeService::addFromLine(const string& rawLine) {
    std::string line = rawLine;
    stripCR(line);

    vector<string> f = split(line, '|');
    if (f.size() != 7) return false;
    return add(f[0], f[1], f[2], f[3], f[4], f[5], f[6]);
}

//Đọc tối đa n dòng từ một luồng và trả về số dòng thêm thành công
long long ShowtimeService::loadFromStream(istream& in, long long n) {
    long long added = 0;
    string line;
    for (long long i = 0; i < n && getline(in, line); i++) {
        if (addFromLine(line)) added++;
    }
    return added;
}

//Đọc dữ liệu từ file
long long ShowtimeService::loadFromFile(const string& path) {
    ifstream in(path);
    if (!in) return -1;

    long long added = 0;
    bool first = true;
    string line;
    while (getline(in, line)) {
        stripCR(line);
        if (line.empty()) continue;
        if (first) {
            first = false;
            if (isNumber(line)) continue;  // dòng đầu là N, bỏ qua
        }
        if (addFromLine(line)) added++;
    }
    return added;
}

//Tìm các suất chiếu của một phim trong một ngày, có giờ bắt đầu nằm trong khoảng [t1, t2]
vector<Showtime> ShowtimeService::search(const string& movieId, const string& date,
                                              const string& t1, const string& t2) const {
    vector<Showtime> result;

    if (!validMovieId(movieId) || !validDate(date)) return result;
    int lo = parseTime(t1);
    int hi = parseTime(t2);
    if (lo < 0 || hi < 0 || lo > hi) return result;

    const int* found = index_.find(makeKey(movieId, date));
    if (found == nullptr) return result;  // movie không tồn tại hoặc ngày đó không có lịch chiếu

    vector<Showtime>& group = groups_[*found];
    if (!sorted_[*found]) {
        sort(group.begin(), group.end(), byStartIdRoom);
        sorted_[*found] = 1;
    }

    // Tìm suất đầu tiên có StartTime >= T1, rồi lấy đến khi StartTime > T2
    auto it = lower_bound(group.begin(), group.end(), lo,
                               [](const Showtime& s, int value) { return s.startMin < value; });
    for (; it != group.end() && it->startMin <= hi; ++it) {
        result.push_back(*it);
    }
    return result;
}

//Đọc một dòng truy vấn dạng MovieID|Date|T1|T2
vector<Showtime> ShowtimeService::searchFromLine(const string& rawLine) const {
    string line = rawLine;
    stripCR(line);

    vector<string> f = split(line, '|');
    if (f.size() != 4) return vector<Showtime>();
    return search(f[0], f[1], f[2], f[3]);
}