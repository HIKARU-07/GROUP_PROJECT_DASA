#include "../src/core/services/BookingService.h"

#include <iostream>

using namespace std;

int main() {

    BookingService service;


    // Input không theo thứ tự timestamp
    service.addRequest(
        BookingRequest(
            "REQ-00003",
            "SHOWTIME-482",
            "A01",
            "CUS-003",
            "2026-09-03 10:05:00",
            "PENDING"
        )
    );


    service.addRequest(
        BookingRequest(
            "REQ-00001",
            "SHOWTIME-482",
            "A01",
            "CUS-001",
            "2026-09-03 10:00:00",
            "PENDING"
        )
    );


    service.addRequest(
        BookingRequest(
            "REQ-00002",
            "SHOWTIME-482",
            "A01",
            "CUS-002",
            "2026-09-03 10:00:00",
            "PENDING"
        )
    );


    service.addRequest(
        BookingRequest(
            "REQ-00004",
            "SHOWTIME-482",
            "B01",
            "CUS-004",
            "2026-09-03 10:06:00",
            "CANCELLED"
        )
    );


    service.addRequest(
        BookingRequest(
            "ABC-00005",
            "SHOWTIME-482",
            "C01",
            "CUS-005",
            "2026-09-03 10:07:00",
            "PENDING"
        )
    );


    vector<BookingResult> results =
        service.processRequests();


    for (const BookingResult& result : results) {

        cout
            << result.request_id
            << "|"
            << result.seat_id
            << "|"
            << result.customer_id
            << "|"
            << result.result_status
            << '\n';
    }


    return 0;
}