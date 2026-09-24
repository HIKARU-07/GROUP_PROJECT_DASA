#include "../src/services/BookingService.h"

#include <iostream>

using namespace std;

int main() {

    BookingService service;

    service.addRequest(
        BookingRequest(
            "REQ-00003",
            "SHOWTIME-001",
            "A01",
            "CUS-003",
            "2026-09-03 10:05:00",
            "PENDING"
        )
    );

    service.addRequest(
        BookingRequest(
            "REQ-00001",
            "SHOWTIME-001",
            "A01",
            "CUS-001",
            "2026-09-03 10:00:00",
            "PENDING"
        )
    );

    service.addRequest(
        BookingRequest(
            "REQ-00002",
            "SHOWTIME-001",
            "A01",
            "CUS-002",
            "2026-09-03 10:00:00",
            "PENDING"
        )
    );

    service.addRequest(
        BookingRequest(
            "REQ-00004",
            "SHOWTIME-001",
            "B01",
            "CUS-004",
            "2026-09-03 10:06:00",
            "CANCELLED"
        )
    );

    service.addRequest(
        BookingRequest(
            "ABC-00005",
            "SHOWTIME-001",
            "C01",
            "CUS-005",
            "2026-09-03 10:07:00",
            "PENDING"
        )
    );

    service.addRequest(
        BookingRequest(
            "REQ-00006",
            "SHOWTIME-001",
            "L12",
            "CUS-006",
            "2026-09-03 10:08:00",
            "PENDING"
        )
    );

    service.addRequest(
        BookingRequest(
            "REQ-00007",
            "SHOWTIME-002",
            "A01",
            "CUS-007",
            "2026-09-03 10:09:00",
            "PENDING"
        )
    );

    service.addRequest(
        BookingRequest(
            "REQ-00008",
            "SHOWTIME-001",
            "L12",
            "CUS-008",
            "2026-09-03 10:10:00",
            "PENDING"
        )
    );

    vector<BookingResult> results =
        service.process();

    for (const BookingResult& result : results) {

        cout
            << result.requestId
            << "|"
            << result.seatId
            << "|"
            << result.customerId
            << "|"
            << result.resultStatus
            << '\n';
    }

    return 0;
}