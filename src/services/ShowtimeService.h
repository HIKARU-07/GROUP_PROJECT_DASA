#pragma once

#include <istream>
#include <string>
#include <vector>
#include "HashTable.h"
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
    bool add(string& movieId, const std::string& date,
             string& showtimeId, const std::string& cinemaName,
             string& room, const std::string& startTime,
             string& endTime);

    // Thêm dòng: MovieID|Date|ShowtimeID|CinemaName|CinemaRoom|StartTime|EndTime
    bool addFromLine(string& line);

    // Đọc n dòng suất chiếu từ luồng
    // Trả về số suất đã thêm
    long long loadFromStream(istream& in, long long n);

    // Đọc file
    // Trả về số suất hợp lệ đã thêm
    long long loadFromFile(string& path);

    // Các suất của movieId trong ngày date có t1 <= StartTime <= t2 đã sắp theo StartTime -> ShowtimeID -> CinemaRoom.
    vector<Showtime> search(string& movieId, string& date, string& t1, string& t2) const;

    // Như search nhưng nhận một dòng: MovieID|Date|T1|T2
    vector<Showtime> searchFromLine(string& line) const;

    // Tổng số suất chiếu hợp lệ đang lưu
    long long size() const { return total_; }

private:
    mutable vector<std::vector<Showtime>> groups_;
    mutable vector<char> sorted_;

    HashTable<int> index_;   // "MovieID|Date" -> chỉ số nhóm trong groups_
    long long total_ = 0;
};