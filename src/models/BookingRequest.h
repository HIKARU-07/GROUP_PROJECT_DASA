#ifndef BOOKING_REQUEST_H
#define BOOKING_REQUEST_H

#include <string>

using namespace std;

class BookingRequest {
private:
    string requestId;
    string showtimeId;
    string seatId;
    string customerId;
    string timestamp;
    string status;

public:
    BookingRequest() {
        requestId = "";
        showtimeId = "";
        seatId = "";
        customerId = "";
        timestamp = "";
        status = "PENDING";
    }

    BookingRequest(
        string requestId,
        string showtimeId,
        string seatId,
        string customerId,
        string timestamp,
        string status
    ) {
        this->requestId = requestId;
        this->showtimeId = showtimeId;
        this->seatId = seatId;
        this->customerId = customerId;
        this->timestamp = timestamp;
        this->status = status;
    }

    string getRequestId() const {
        return requestId;
    }

    string getShowtimeId() const {
        return showtimeId;
    }

    string getSeatId() const {
        return seatId;
    }

    string getCustomerId() const {
        return customerId;
    }

    string getTimestamp() const {
        return timestamp;
    }

    string getStatus() const {
        return status;
    }
};

#endif