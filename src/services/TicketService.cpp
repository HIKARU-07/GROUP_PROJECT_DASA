#include "TicketService.h"
#include <functional>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
 
using namespace std;
 
// Số phút vé còn hiệu lực sau giờ chiếu 
static const long long EXPIRE_MINUTES = 3 * 60;
 
// Hàm phụ này dùng để chuyển đổi số dạng chữ trên vé thành số nguyên
static int readInt(const string& s, int pos, int len)
{
    int value = 0;
    for (int i = pos; i < pos + len; i++)
        value = value * 10 + (s[i] - '0');
    return value;
}

// Hàm khởi tạo
// Cấp sẵn expectedN / 0.75 bucket 
TicketService::TicketService(size_t expectedN)
    : buckets(static_cast<size_t>(expectedN / 0.75) + 1), ticketCount(0)
{
}
 
// Khởi tạo mảng băm
size_t TicketService::hash_ticket(const string& key) const
{
    return std::hash<string>{}(key);
}
 
// Đổi mã băm thành vị trí bucket bằng phép chia lấy dư.
size_t TicketService::bucketIndex(const string& key) const
{
    return hash_ticket(key) % buckets.size();
}
 
// checkId
// VN-CINEMA-XXXXXY
bool TicketService::checkId(const string& id) const
{
    if (id.size() != 16)
        return false;
    // Kiểm tra lần lượt VN-CINEMA-
    if (id.compare(0, 10, "VN-CINEMA-") != 0)
        return false;

    // Kiểm tra XXXXX ( trong đó X là các số )
    for (size_t i = 10; i < 15; i++)
    {
        if (id[i] < '0' || id[i] > '9')
            return false;
    }

    // Kiểm tra Y ( trong đó Y là chữ cái )
    if (!isalpha(static_cast<unsigned char>(id[15])))
        return false;

    return true;
}
 
// Trả về số ngày của tháng 
int TicketService::getDaysInMonth(int month, int year) const
{
    static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[month - 1];
}

// Kiểm tra chuỗi có đúng dạng "YYYY-MM-DD HH:MM" và giá trị hợp lệ không
// (tháng 1-12, ngày đúng theo tháng, giờ 0-23, phút 0-59)
bool TicketService::checkTime(const string& dt) const
{
    // Độ dài cố định 16 ký tự
    if (dt.size() != 16)
        return false;
 
    // Các ký tự phân cách phải đúng vị trí
    if (dt[4] != '-' || dt[7] != '-' || dt[10] != ' ' || dt[13] != ':')
        return false;
 
    // Các vị trí còn lại phải là chữ số
    for (int i = 0; i < 16; i++)
    {
        if (i == 4 || i == 7 || i == 10 || i == 13)
            continue;
        if (dt[i] < '0' || dt[i] > '9')
            return false;
    }
 
    int year   = readInt(dt, 0, 4);
    int month  = readInt(dt, 5, 2);
    int day    = readInt(dt, 8, 2);
    int hour   = readInt(dt, 11, 2);
    int minute = readInt(dt, 14, 2);
 
    if (year < 1 || month < 1 || month > 12)
        return false;
    if (day < 1 || day > getDaysInMonth(month, year))
        return false;
    if (hour > 23 || minute > 59)
        return false;
 
    return true;
}
 
// toMinutes
// Đổi thời gian thành tổng số phút tính từ năm 1 để so sánh hai mốc.
long long TicketService::toMinutes(const string& dt) const
{
    int year   = readInt(dt, 0, 4);
    int month  = readInt(dt, 5, 2);
    int day    = readInt(dt, 8, 2);
    int hour   = readInt(dt, 11, 2);
    int minute = readInt(dt, 14, 2);

    // Mỗi năm cố định 365 ngày
    long long days = 365LL * (year - 1);

    // Cộng số ngày của các tháng trước trong năm
    for (int m = 1; m < month; m++)
        days += getDaysInMonth(m, year);

    days += day - 1;

    return days * 24 * 60 + hour * 60 + minute;
}

// checkDate
// Trả về true nếu vé ĐÃ HẾT HẠN: currentTime > showtime + 3 giờ.
// Nếu một trong hai chuỗi thời gian sai định dạng thì trả về false
bool TicketService::checkDate(const string& showtime, const string& currentTime) const
{
    if (!checkTime(showtime) || !checkTime(currentTime))
        return false;
 
    return toMinutes(currentTime) > toMinutes(showtime) + EXPIRE_MINUTES;
}

// addTicket
// Thêm vé vào bảng băm
// Nếu bookingId đã có thì ghi đè vé cũ
void TicketService::addTicket(const Ticket& ticket)
{
    DoubleLinkedList<Ticket>& bucket =
        buckets[bucketIndex(ticket.bookingId)];

    for (long long i = 0; i < bucket.getSize(); i++)
    {
        Ticket& t = bucket.getAt(i);

        if (t.bookingId == ticket.bookingId)
        {
            t = ticket;
            return;
        }
    }

    bucket.pushBack(ticket);
    ticketCount++;
}

// findTicket
// Tìm vé theo bookingId
const Ticket* TicketService::findTicket(const string& bookingId) const
{
    const DoubleLinkedList<Ticket>& bucket =
        buckets[bucketIndex(bookingId)];

    for (long long i = 0; i < bucket.getSize(); i++)
    {
        const Ticket& t = bucket.getAt(i);

        if (t.bookingId == bookingId)
        {
            return &t;
        }
    }

    return nullptr;
}
 
// checkTicket
// Thứ tự: định dạng -> tồn tại -> hết hạn -> đã dùng -> hợp lệ
CheckInResult TicketService::checkTicket(const string& bookingId, const string& currentTime) const
{
    // 1. Sai định dạng
    if (!checkId(bookingId) || !checkTime(currentTime) )
        return CheckInResult::INVALID_FORMAT;
 
    // 2. Không tìm thấy
    const Ticket* ticket = findTicket(bookingId);
    if (ticket == nullptr)
        return CheckInResult::NOT_FOUND;
 
    // 3. Hết hạn
    if (checkDate(ticket->showtime, currentTime))
        return CheckInResult::EXPIRED;
 
    // 4. Đã sử dụng
    if (ticket->ticketStatus == "USED")
        return CheckInResult::USED;
 
    // 5. Hợp lệ
    return CheckInResult::VALID;
}

void TicketService::run(){
    string filename;

    cout << "\n===== TICKET CHECK-IN =====\n";
    cout << "Nhap ten file: ";
    cin >> filename;
    cin.ignore();

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Khong the mo file.\n";
        return;
    }

    int n; 
    file >> n;
    file.ignore();

    for (int i = 0; i < n; i++){
        string line;
        getline(file, line);

        stringstream ss(line);

        Ticket ticket;

        getline(ss, ticket.bookingId, '|');
        getline(ss, ticket.customerName, '|');
        getline(ss, ticket.movieName, '|');
        getline(ss, ticket.showtime, '|');
        getline(ss, ticket.cinemaRoom, '|');
        getline(ss, ticket.seats, '|');
        getline(ss, ticket.ticketStatus, '|');
        getline(ss, ticket.cinemaAddress, '|');

        addTicket(ticket);
    }
    file.close();

    cout << "Da nap " << n << " ticket.\n";

    string choice;
    do {
        cout << "\n----- TICKET MENU -----\n";
        cout << "1. Check-in\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        getline(cin >> ws, choice);

        if (choice == "1") {
            string bookingId, currentTime;

            cout << "Nhap Booking ID: ";
            getline(cin >> ws, bookingId);

            cout << "Nhap thoi gian hien tai (YYYY-MM-DD HH:MM): ";
            getline(cin >> ws, currentTime);

            CheckInResult result = checkTicket(bookingId, currentTime);

            cout << "\n===== KET QUA =====\n";
            switch (result) {
                case CheckInResult::INVALID_FORMAT: cout << "INVALID_FORMAT\n"; break;
                case CheckInResult::NOT_FOUND:      cout << "NOT_FOUND\n";      break;
                case CheckInResult::EXPIRED:        cout << "EXPIRED\n";        break;
                case CheckInResult::USED:           cout << "USED\n";           break;
                case CheckInResult::VALID:          cout << "VALID\n";          break;
            }
        } else if (choice == "0") {
            cout << "Thoat Ticket Service.\n";
        } else {
            cout << "Lua chon khong hop le.\n";
        }
    } while (choice != "0");
}