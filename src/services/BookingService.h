#ifndef BOOKING_SERVICE_H
#define BOOKING_SERVICE_H

#include "../models/BookingRequest.h"
#include "../structures/PriorityQueue.h"

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

struct BookingResult {
    string requestId;
    string seatId;
    string customerId;
    string resultStatus;
};

class BookingService {
private:
    PriorityQueue queue;

    unordered_set<string> lockedSeats;

    bool validRequestId(
        const string& requestId
    ) const;

    bool validSeatId(
        const string& seatId
    ) const;

    string makeSeatKey(
        const string& showtimeId,
        const string& seatId
    ) const;

public:
    void addRequest(
        const BookingRequest& request
    );

    vector<BookingResult> process();
};

#endif