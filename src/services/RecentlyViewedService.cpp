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
    int choice;
    do {
        cout << "\n===== RECENTLY VIEWED =====\n";
        cout << "1. Xem phim\n";
        cout << "2. Xem lich su xem phim\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;

        if (choice == 1) {
            Movie movie;

            cout << "Nhap movie ID: ";
            cin >> movie.movieId;

            view(movie);

            cout << "Da xem phim: "
                 << movie.movieId << "\n";
        }
        else if (choice == 2) {
            cout << "\nLich su xem phim gan day:\n";
            print();
        }
        else if (choice == 0) {
            cout << "Thoat Recently Viewed.\n";
        }
        else {
            cout << "Lua chon khong hop le.\n";
        }

    } while (choice != 0);
}