#ifndef BOOKING_REQUEST_H
#define BOOKING_REQUEST_H

#include <string>

using namespace std;

class BookingRequest {
private:
    string request_id;
    string showtime_id;
    string seat_id;
    string customer_id;
    string timestamp;
    string request_status;

public:
    BookingRequest()
        : request_id(""),
          showtime_id(""),
          seat_id(""),
          customer_id(""),
          timestamp(""),
          request_status("PENDING") {
    }

    BookingRequest(
        const string& request_id,
        const string& showtime_id,
        const string& seat_id,
        const string& customer_id,
        const string& timestamp,
        const string& request_status = "PENDING"
    )
        : request_id(request_id),
          showtime_id(showtime_id),
          seat_id(seat_id),
          customer_id(customer_id),
          timestamp(timestamp),
          request_status(request_status) {
    }

    const string& getRequestId() const {
        return request_id;
    }

    const string& getShowtimeId() const {
        return showtime_id;
    }

    const string& getSeatId() const {
        return seat_id;
    }

    const string& getCustomerId() const {
        return customer_id;
    }

    const string& getTimestamp() const {
        return timestamp;
    }

    const string& getRequestStatus() const {
        return request_status;
    }

    void setRequestStatus(const string& status) {
        request_status = status;
    }

    bool isPending() const {
        return request_status == "PENDING";
    }

    bool isCancelled() const {
        return request_status == "CANCELLED";
    }
};

#endif