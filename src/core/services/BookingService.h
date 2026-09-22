#ifndef BOOKING_SERVICE_H
#define BOOKING_SERVICE_H

#include "../models/BookingRequest.h"
#include "../structures/PriorityQueue.h"

#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

struct BookingResult {
    string request_id;
    string seat_id;
    string customer_id;
    string result_status;
};

class BookingService {
private:
    PriorityQueue queue;

    // Lưu các ghế đã được khóa.
    // Key = showtime_id + "|" + seat_id
    unordered_set<string> lockedSeats;

    bool isValidRequestId(const string& requestId) const;

    bool isValidSeatId(const string& seatId) const;

    string makeSeatKey(
        const string& showtimeId,
        const string& seatId
    ) const;

public:
    BookingService();

    void addRequest(
        const BookingRequest& request
    );

    vector<BookingResult> processRequests();

    bool hasLockedSeat(
        const string& showtimeId,
        const string& seatId
    ) const;

    int pendingSize() const;
};

#endif