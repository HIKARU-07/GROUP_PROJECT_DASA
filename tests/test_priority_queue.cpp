#include "../src/structures/PriorityQueue.h"

#include <iostream>

using namespace std;

int main() {

    PriorityQueue queue;

    queue.push(
        BookingRequest(
            "REQ-00003",
            "SHOWTIME-001",
            "A01",
            "CUS-003",
            "2026-09-03 12:00:00",
            "PENDING"
        )
    );

    queue.push(
        BookingRequest(
            "REQ-00002",
            "SHOWTIME-001",
            "A01",
            "CUS-002",
            "2026-09-03 10:00:00",
            "PENDING"
        )
    );

    queue.push(
        BookingRequest(
            "REQ-00001",
            "SHOWTIME-001",
            "A01",
            "CUS-001",
            "2026-09-03 10:00:00",
            "PENDING"
        )
    );

    while (!queue.empty()) {

        BookingRequest request =
            queue.top();

        cout
            << request.getRequestId()
            << " | "
            << request.getTimestamp()
            << '\n';

        queue.pop();
    }

    return 0;
}