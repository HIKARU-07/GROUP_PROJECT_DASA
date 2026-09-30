#ifndef RECENTLY_VIEWED_SERVICE_H
#define RECENTLY_VIEWED_SERVICE_H

#include "../models/Movied.h"
#include "../structures/DoubleLinkedList.h"


#include <string>
#include <iostream>


using namespace std;

const int MAX = 5;

class RecentlyViewedService {
private:
    DoubleLinkedList<Movie> recentList;

public:
    // Khách vừa xem bộ phim
    void view(const Movie& movie);

    // Dùng để nạp lịch sử ban đầu 
    void append(const Movie& movie);

    // Danh sách có rỗng hay không;
    bool isEmpty() const;

    // Số lượng phim hiện có trong danh sách
    int getSize() const;

    // Xóa lịch sử xem gần đây
    void clear();

    // Lấy movieId của phim ở vị trí index
    string getMovieId(int index) const;

    // In kết quả ra màn hình
    void print() const;

    void run();
};

#endif