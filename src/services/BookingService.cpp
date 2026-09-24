#include "BookingService.h"

#include <cctype>

bool BookingService::validRequestId(
    const string& requestId
) const {

    if (requestId.length() != 9) {
        return false;
    }

    if (requestId.substr(0, 4) != "REQ-") {
        return false;
    }

    for (int i = 4; i < 9; i++) {

        if (!isdigit(
                static_cast<unsigned char>(
                    requestId[i]))) {

            return false;
        }
    }

    return true;
}

bool BookingService::validSeatId(
    const string& seatId
) const {

    if (
        seatId.length() < 2 ||
        seatId.length() > 3
    ) {
        return false;
    }

    char row = seatId[0];

    if (row < 'A' || row > 'L') {
        return false;
    }

    for (int i = 1; i < seatId.length(); i++) {

        if (!isdigit(
                static_cast<unsigned char>(
                    seatId[i]))) {

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

vector<BookingResult>
BookingService::process() {

    vector<BookingResult> results;

    while (!queue.empty()) {

        BookingRequest request =
            queue.top();

        queue.pop();

        BookingResult result;

        result.requestId =
            request.getRequestId();

        result.seatId =
            request.getSeatId();

        result.customerId =
            request.getCustomerId();

        // 1. Kiểm tra request_id
        if (!validRequestId(
                request.getRequestId())) {

            result.resultStatus = "INVALID";

            results.push_back(result);

            continue;
        }

        // 2. Kiểm tra seat_id
        if (!validSeatId(
                request.getSeatId())) {

            result.resultStatus = "INVALID";

            results.push_back(result);

            continue;
        }

        // 3. Kiểm tra CANCELLED
        if (request.getStatus() == "CANCELLED") {

            result.resultStatus = "CANCELLED";

            results.push_back(result);

            continue;
        }

        // 4. Tạo khóa showtime + seat
        string seatKey =
            makeSeatKey(
                request.getShowtimeId(),
                request.getSeatId()
            );

        // 5. Kiểm tra ghế đã được khóa chưa
        if (
            lockedSeats.find(seatKey)
            != lockedSeats.end()
        ) {

            result.resultStatus = "SEAT_TAKEN";

            results.push_back(result);

            continue;
        }

        // 6. Khóa ghế
        lockedSeats.insert(seatKey);

        result.resultStatus = "LOCKED";

        results.push_back(result);
    }

    return results;
}