#include "../src/services/TicketService.h"

#include <iostream>
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

int main() {

    TicketService service(100);

    // Thêm các vé mẫu vào bảng băm
    service.addTicket(
        Ticket{
            "VN-CINEMA-00001A",
            "2026-09-30 18:00",
            "UNUSED"
        }
    );

    service.addTicket(
        Ticket{
            "VN-CINEMA-00002B",
            "2026-09-30 18:00",
            "USED"
        }
    );

    service.addTicket(
        Ticket{
            "VN-CINEMA-00003C",
            "2026-02-28 10:00",
            "UNUSED"
        }
    );

    service.addTicket(
        Ticket{
            "VN-CINEMA-00004D",
            "2026-12-31 23:30",
            "UNUSED"
        }
    );

    // Kiểm tra tính năng ghi đè vé trùng ID
    service.addTicket(
        Ticket{
            "VN-CINEMA-00005E",
            "2026-09-30 18:00",
            "UNUSED"
        }
    );
    service.addTicket(
        Ticket{
            "VN-CINEMA-00005E",
            "2026-09-30 18:00",
            "USED"
        }
    );

    struct CheckInRequest {
        string bookingId;
        string currentTime;
    };

    vector<CheckInRequest> requests = {
        // 1. HỢP LỆ (VALID)
        {"VN-CINEMA-00001A", "2026-09-30 18:00"}, // Đúng giờ chiếu
        {"VN-CINEMA-00001A", "2026-09-30 19:30"}, // Soát vé sau 1.5 giờ
        {"VN-CINEMA-00001A", "2026-09-30 21:00"}, // Chạm đúng mốc 3 giờ (180 phút)
        {"VN-CINEMA-00001A", "2026-09-30 17:00"}, // Soát vé sớm trước giờ chiếu
        {"VN-CINEMA-00003C", "2026-02-28 12:00"}, // Ngày cuối tháng 02
        {"VN-CINEMA-00004D", "2027-01-01 01:30"}, // Soát vé qua giao thừa năm mới

        // 2. HẾT HẠN (EXPIRED)
        {"VN-CINEMA-00001A", "2026-09-30 21:01"}, // Quá 3 giờ 1 phút
        {"VN-CINEMA-00001A", "2026-10-01 18:00"}, // Quá 1 ngày
        {"VN-CINEMA-00003C", "2026-03-01 10:00"}, // Hết hạn sang tháng 03
        {"VN-CINEMA-00004D", "2027-01-01 03:00"}, // Quá hạn sang năm mới
        {"VN-CINEMA-00002B", "2026-09-30 21:05"}, // Vừa USED vừa EXPIRED (Ưu tiên EXPIRED)

        // 3. ĐÃ SỬ DỤNG (USED)
        {"VN-CINEMA-00002B", "2026-09-30 18:30"}, // Vé đã dùng còn trong thời hạn
        {"VN-CINEMA-00005E", "2026-09-30 18:30"}, // Vé ghi đè trạng thái sang USED

        // 4. KHÔNG TÌM THẤY (NOT_FOUND)
        {"VN-CINEMA-99999Z", "2026-09-30 19:00"}, // Mã đúng định dạng nhưng không có trong DB
        {"VN-CINEMA-00000A", "2026-09-30 19:00"}, // Mã chưa từng được thêm

        // 5. SAI ĐỊNH DẠNG MÃ VÉ (INVALID_FORMAT) 
        {"VN-CINEMA-1234",   "2026-09-30 19:00"}, // Độ dài ngắn (14 ký tự)
        {"VN-CINEMA-123456A", "2026-09-30 19:00"}, // Độ dài dài (17 ký tự)
        {"VN-CINEMA-12A45B", "2026-09-30 19:00"}, // Lỗi chữ ở cụm 5 số
        {"VN-CINEMA-12345#", "2026-09-30 19:00"}, // Ký tự đặc biệt ở cuối
        {"XX-CINEMA-12345A", "2026-09-30 19:00"}, // Sai tiền tố VN-CINEMA-

        // 6. SAI ĐỊNH DẠNG THỜI GIAN (INVALID_FORMAT)
        {"VN-CINEMA-00001A", "2026-09-30 25:00"}, // Giờ > 23
        {"VN-CINEMA-00001A", "2026-09-30 20:60"}, // Phút > 59
        {"VN-CINEMA-00001A", "2026-02-29 10:00"}, // 29/02 không được hỗ trợ
        {"VN-CINEMA-00001A", "2026-04-31 10:00"}, // Tháng 4 có 31 ngày
        {"VN-CINEMA-00001A", "2026/09/30 19:00"}, // Sai ký tự phân cách /
        {"VN-CINEMA-00001A", "2026-09-3019:00"}   // Thiếu khoảng trắng giữa ngày và giờ
    };

    for (const CheckInRequest& req : requests) {

        CheckInResult result = service.checkTicket(req.bookingId, req.currentTime);

        cout
            << req.bookingId
            << "|"
            << req.currentTime
            << "|"
            << resultToString(result)
            << '\n';
    }

    return 0;
}