#pragma once

#include <string>
#include <vector>
#include "../models/Ticket.h"
#include "../structures/DoubleLinkedList.h"

enum class CheckInResult {
    VALID,              // Vé hợp lệ
    INVALID_FORMAT,     // Vé không khớp với định dạng quy định 
    NOT_FOUND,          // Vé đúng định dạng nhưng không tìm thấy trong hệ thống
    EXPIRED,            // Vé đã quá thời gian suất chiếu diễn ra 
    USED                // Vé đã được sử dụng 
};

class TicketService {
private:
    std::vector<DoubleLinkedList<Ticket>> buckets;
    size_t ticketCount;

    // Hàm băm hash_ticket
    size_t hash_ticket(const std::string& key) const;
    
    // Hàm tính vị trí của giá trị cần tìm 
    size_t bucketIndex(const std::string& key) const;

    // Hàm kiểm tra định dạng mã vé
    bool checkId(const std::string& id) const;

    // Các hàm kiểm tra và xử lý thời gian (YYYY-MM-DD HH:MM)
    bool checkTime(const std::string& dt) const;
    int getDaysInMonth(int month, int year) const;  // Lấy ra số ngày trong tháng
    long long toMinutes(const std::string& dt) const; // Chuyển đổi thời gian sang phút
    bool checkDate(const std::string& showtime, const std::string& currentTime) const; // Hàm kiểm tra vé đã hết hạn hay chưa 

public:
    // Hàm khởi tạo: Nhận vào N (số vé dự kiến) để cấp phát sẵn số lượng buckets = N / 0.75
    explicit TicketService(size_t expectedN = 1000000);

    // Thêm một vé mới vào Bảng băm
    void addTicket(const Ticket& ticket);

    // Tìm kiếm vé theo bookingId (Trả về con trỏ chỉ đọc const Ticket*)
    const Ticket* findTicket(const std::string& bookingId) const;

    // Quy trình check-in vé tối ưu theo tư duy Fail-Fast
    CheckInResult checkTicket(const std::string& bookingId, const std::string& currentTime) const;

    // Lấy tổng số lượng vé đang có trong hệ thống
    size_t getTicketCount() const { 
        return ticketCount; 
    }

    void run();
};