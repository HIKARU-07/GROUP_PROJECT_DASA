#pragma once

#include <istream>
#include <string>
#include <vector>
#include "../structures/HashTable.h"
using namespace std;

// Một suất chiếu.
struct Showtime {
    string id;          // ShowtimeID
    string cinemaName;  // CinemaName
    string room;        // CinemaRoom
    int startMin = 0;   // StartTime, tính bằng phút, từ 00:00
    int endMin = 0;     // EndTime (có thể < startMin nếu phim kết thúc qua ngày hôm sau)

    // Dòng kết quả: ShowtimeID|CinemaName|CinemaRoom|StartTime|EndTime
    string toLine() const;
};


class ShowtimeService {
public:
    // Thêm một suất chiếu. Trả về false nếu dữ liệu không hợp lệ (suất đó bị bỏ qua)
    bool add(const string& movieId, const string& date,
             const string& showtimeId, const string& cinemaName,
             const string& room, const string& startTime,
             const string& endTime);

    //Đọc file suất chiếu
    long long loadFromFile(const string& path);

    // Các suất của movieId trong ngày date có t1 <= StartTime <= t2 đã sắp theo StartTime -> ShowtimeID -> CinemaRoom.
    vector<Showtime> search(const string& movieId, const string& date, const string& t1, const string& t2) const;

    // Tổng số suất chiếu hợp lệ đang lưu
    long long size() const { return total_; }

private:
    mutable vector<vector<Showtime>> groups_;
    mutable vector<char> sorted_;

    HashTable<int> index_;   // "MovieID|Date" -> chỉ số nhóm trong groups_
    long long total_ = 0;
};