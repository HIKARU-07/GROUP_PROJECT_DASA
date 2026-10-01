#include "RecentlyViewedService.h"
#include <iostream>

// Khách vừa xem một bộ phim
void RecentlyViewedService::view(const Movie& movie){
    bool inList = (recentList.Search(movie) != nullptr);
    if (inList){
        recentList.Delete(movie);
    } else if (recentList.getSize() >= MAX){
        recentList.popBack();
    }
    recentList.pushFront(movie);
}

// Nạp lịch sử ban đầu
void RecentlyViewedService::append(const Movie& movie){
    recentList.pushBack(movie);
}

// Kiểm tra rỗng
bool RecentlyViewedService::isEmpty() const {
    return recentList.isEmpty();
}   

// Trả về kích thước
int RecentlyViewedService::getSize() const {
    return recentList.getSize();
}

// Xóa lịch sử xem gần đây
void RecentlyViewedService::clear(){
    recentList.clear();
}

// Lấy movieId của phim ở vị trí index
string RecentlyViewedService::getMovieId(int index) const {
    if (index < 0 || index >= getSize()){
        return "";
    }
    Movie movie = recentList.getAt(index);
    return movie.movieId;
}

// In kết quả ra màn hình
void RecentlyViewedService::print() const {
    if (isEmpty()){
        cout <<"Khong co lich su xem phim gan day\n";
        return; 
    }

    for (int i = 0; i < getSize(); i++){
        cout << getMovieId(i) << "\n";
    }
}

// Đọc input, xử lý, in output
void RecentlyViewedService::run() {
    clear();

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++){
        Movie movie;
        cin >> movie.movieId;
        append(movie);
    }

    for (int i = 0; i < m; i++){
        Movie movie;
        cin >> movie.movieId;
        view(movie);
    }

    print();
}