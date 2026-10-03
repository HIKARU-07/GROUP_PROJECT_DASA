#include "main.h"

using namespace std;

void showMenu(){
    cout << "\n========== MENU ==========\n";
    cout << "1. Kiem tra ve (Ticket)\n";
    cout << "2. Tim suat chieu (Showtime)\n";
    cout << "3. Hoan tac thao tac (Undo)\n";
    cout << "4. Phim xem gan day (Recently Viewed)\n";
    cout << "5. Dat ghe (Booking)\n";
    cout << "0. Thoat\n";
    cout << "Chon (0-5): ";
}

void clearInputBuffer(){
    cin.clear();                                          // bỏ trạng thái lỗi của cin
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // bỏ phần còn lại của dòng
}

int main(){
    int choice;

    do{
        showMenu();
        if (!(cin >> choice)){
            clearInputBuffer();
            choice = -1;            
        }
        switch (choice)
        {
            case 1: { TicketService service;         service.run(); break; }
            case 2: { ShowtimeService service;       service.run(); break; }
            case 3: { UndoService service;           service.run(); break; }
            case 4: { RecentlyViewedService service; service.run(); break; }
            case 5: { BookingService service;        service.run(); break; }
            case 0: cout << "Tam biet!\n"; break;
            default: cout << "Lua chon khong hop le, hay nhap lai.\n";
        }

    } while (choice != 0);
    return 0;
}