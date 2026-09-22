#include "BookingService.h"

#include <cctype>

BookingService::BookingService() {
}


// REQ-XXXXX
// XXXXX phải đúng 5 chữ số
bool BookingService::isValidRequestId(
    const string& requestId
) const {

    if (requestId.length() != 9) {
        return false;
    }

    if (requestId.substr(0, 4) != "REQ-") {
        return false;
    }

    for (int i = 4; i < 9; i++) {
        if (!isdigit(requestId[i])) {
            return false;
        }
    }

    return true;
}


// [A-L][0-9]{1,2}
bool BookingService::isValidSeatId(
    const string& seatId
) const {

    if (seatId.length() < 2 ||
        seatId.length() > 3) {
        return false;
    }

    char row = seatId[0];

    if (row < 'A' || row > 'L') {
        return false;
    }

    for (int i = 1; i < seatId.length(); i++) {
        if (!isdigit(seatId[i])) {
            return false;
        }
    }

    return true;
}


string BookingService::makeSeatKey(
    const string& showtimeId,
    const string& seatId
) const {

    return showtimeId + "|" + seatId;
}


void BookingService::addRequest(
    const BookingRequest& request
) {
    queue.push(request);
}


bool BookingService::hasLockedSeat(
    const string& showtimeId,
    const string& seatId
) const {

    string key = makeSeatKey(
        showtimeId,
        seatId
    );

    return lockedSeats.find(key)
        != lockedSeats.end();
}


vector<BookingResult>
BookingService::processRequests() {

    vector<BookingResult> results;

    while (!queue.empty()) {

        BookingRequest request = queue.top();

        queue.pop();


        BookingResult result;

        result.request_id =
            request.getRequestId();

        result.seat_id =
            request.getSeatId();

        result.customer_id =
            request.getCustomerId();


        // 1. Kiểm tra Request ID
        if (!isValidRequestId(
                request.getRequestId())) {

            result.result_status = "INVALID";

            results.push_back(result);

            continue;
        }


        // 2. Kiểm tra Seat ID
        if (!isValidSeatId(
                request.getSeatId())) {

            result.result_status = "INVALID";

            results.push_back(result);

            continue;
        }


        // 3. Kiểm tra CANCELLED
        if (request.isCancelled()) {

            result.result_status = "CANCELLED";

            results.push_back(result);

            continue;
        }


        // 4. Kiểm tra ghế đã được khóa chưa
        string seatKey =
            makeSeatKey(
                request.getShowtimeId(),
                request.getSeatId()
            );

        if (
            lockedSeats.find(seatKey)
            != lockedSeats.end()
        ) {

            result.result_status = "SEAT_TAKEN";

            results.push_back(result);

            continue;
        }


        // 5. Khóa ghế
        lockedSeats.insert(seatKey);

        result.result_status = "LOCKED";

        results.push_back(result);
    }

    return results;
}


int BookingService::pendingSize() const {
    return queue.size();
}