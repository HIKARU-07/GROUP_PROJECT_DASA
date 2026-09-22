#include "../core/services/BookingService.h"
#include "../persistence/BookingRepository.h"

#include <iostream>

using namespace std;

int main() {

    BookingRepository repository;

    BookingService service;


    // 1. Đọc dữ liệu từ file
    vector<BookingRequest> requests =
        repository.loadFromFile(
            "data/booking_requests.txt"
        );


    // 2. Đưa tất cả request vào Priority Queue
    for (const BookingRequest& request : requests) {
        service.addRequest(request);
    }


    // 3. Xử lý request
    vector<BookingResult> results =
        service.processRequests();


    // 4. In kết quả
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