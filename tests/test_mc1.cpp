#include "../src/services/TicketService.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string resultToString(CheckInResult res) {
    switch (res) {
        case CheckInResult::VALID:          return "VALID";
        case CheckInResult::USED:           return "USED";
        case CheckInResult::EXPIRED:        return "EXPIRED";
        case CheckInResult::NOT_FOUND:      return "NOT_FOUND";
        case CheckInResult::INVALID_FORMAT: return "INVALID_FORMAT";
        default:                            return "UNKNOWN";
    }
}

// Ticket có 8 field 
Ticket makeTicket(const string& id, const string& showtime, const string& status) {
    Ticket t;
    t.bookingId     = id;
    t.customerName  = "Nguyen Van Muoi";
    t.movieName     = "Phim MINIONS";
    t.showtime      = showtime;
    t.cinemaRoom    = "Room02";
    t.seats         = "A01";
    t.ticketStatus  = status;
    t.cinemaAddress = "THU DUC";
    return t;
}

struct TestCase {
    string bookingId;
    string currentTime;
    CheckInResult expected;
};

int main() {

    TicketService service(100);

    // Thêm các vé mẫu vào bảng băm
    service.addTicket(makeTicket("VN-CINEMA-00001A", "2026-09-30 18:00", "UNUSED"));
    service.addTicket(makeTicket("VN-CINEMA-00002B", "2026-09-30 18:00", "USED"));
    service.addTicket(makeTicket("VN-CINEMA-00003C", "2026-02-28 10:00", "UNUSED"));
    service.addTicket(makeTicket("VN-CINEMA-00004D", "2026-12-31 23:30", "UNUSED"));

    // Kiểm tra tính năng ghi đè vé trùng ID (UNUSED -> USED)
    service.addTicket(makeTicket("VN-CINEMA-00005E", "2026-09-30 18:00", "UNUSED"));
    service.addTicket(makeTicket("VN-CINEMA-00005E", "2026-09-30 18:00", "USED"));

    // Ghi đè không được làm tăng số lượng vé: 5 vé khác nhau
    cout << "ticketCount = " << service.getTicketCount() << " (mong đợi 5)\n\n";

    const CheckInResult V  = CheckInResult::VALID;
    const CheckInResult E  = CheckInResult::EXPIRED;
    const CheckInResult U  = CheckInResult::USED;
    const CheckInResult NF = CheckInResult::NOT_FOUND;
    const CheckInResult IF = CheckInResult::INVALID_FORMAT;

    vector<TestCase> tests = {
        // 1. HỢP LỆ (VALID)
        {"VN-CINEMA-00001A", "2026-09-30 18:00", V},  // Đúng giờ chiếu
        {"VN-CINEMA-00001A", "2026-09-30 19:30", V},  // Soát vé sau 1.5 giờ
        {"VN-CINEMA-00001A", "2026-09-30 21:00", V},  // Chạm đúng mốc 3 giờ (180 phút)
        {"VN-CINEMA-00001A", "2026-09-30 17:00", V},  // Soát vé sớm trước giờ chiếu
        {"VN-CINEMA-00003C", "2026-02-28 12:00", V},  // Ngày cuối tháng 02
        {"VN-CINEMA-00004D", "2027-01-01 01:30", V},  // Soát vé qua giao thừa năm mới

        // 2. HẾT HẠN (EXPIRED)
        {"VN-CINEMA-00001A", "2026-09-30 21:01", E},  // Quá 3 giờ 1 phút
        {"VN-CINEMA-00001A", "2026-10-01 18:00", E},  // Quá 1 ngày
        {"VN-CINEMA-00003C", "2026-03-01 10:00", E},  // Hết hạn sang tháng 03
        {"VN-CINEMA-00004D", "2027-01-01 03:00", E},  // Quá hạn sang năm mới
        {"VN-CINEMA-00002B", "2026-09-30 21:05", E},  // Vừa USED vừa EXPIRED (ưu tiên EXPIRED)

        // 3. ĐÃ SỬ DỤNG (USED)
        {"VN-CINEMA-00002B", "2026-09-30 18:30", U},  // Vé đã dùng còn trong thời hạn
        {"VN-CINEMA-00005E", "2026-09-30 18:30", U},  // Vé ghi đè trạng thái sang USED

        // 4. KHÔNG TÌM THẤY (NOT_FOUND)
        {"VN-CINEMA-99999Z", "2026-09-30 19:00", NF}, // Đúng định dạng nhưng không có trong DB
        {"VN-CINEMA-00000A", "2026-09-30 19:00", NF}, // Mã chưa từng được thêm

        // 5. SAI ĐỊNH DẠNG MÃ VÉ (INVALID_FORMAT)
        {"VN-CINEMA-1234",    "2026-09-30 19:00", IF}, // Quá ngắn
        {"VN-CINEMA-123456A", "2026-09-30 19:00", IF}, // Quá dài
        {"VN-CINEMA-12A45B",  "2026-09-30 19:00", IF}, // Có chữ trong cụm 5 số
        {"VN-CINEMA-12345#",  "2026-09-30 19:00", IF}, // Ký tự đặc biệt ở cuối
        {"XX-CINEMA-12345A",  "2026-09-30 19:00", IF}, // Sai tiền tố

        // 6. SAI ĐỊNH DẠNG THỜI GIAN (INVALID_FORMAT)
        {"VN-CINEMA-00001A", "2026-09-30 25:00", IF}, // Giờ > 23
        {"VN-CINEMA-00001A", "2026-09-30 20:60", IF}, // Phút > 59
        {"VN-CINEMA-00001A", "2026-02-29 10:00", IF}, // 29/02 không được hỗ trợ
        {"VN-CINEMA-00001A", "2026-04-31 10:00", IF}, // Tháng 4 chỉ có 30 ngày
        {"VN-CINEMA-00001A", "2026/09/30 19:00", IF}, // Sai ký tự phân cách
        {"VN-CINEMA-00001A", "2026-09-3019:00",  IF}  // Thiếu khoảng trắng
    };

    int failed = 0;

    for (const TestCase& tc : tests) {
        CheckInResult result = service.checkTicket(tc.bookingId, tc.currentTime);
        bool ok = (result == tc.expected);
        if (!ok) failed++;

        cout << tc.bookingId << "|" << tc.currentTime << "|"
             << resultToString(result);
        if (!ok)
            cout << "   <-- SAI, mong đợi " << resultToString(tc.expected);
        cout << '\n';
    }

    cout << "\nTong: " << tests.size() << " test, "
         << (tests.size() - failed) << " dung, "
         << failed << " sai\n";

    return failed == 0 ? 0 : 1;
}