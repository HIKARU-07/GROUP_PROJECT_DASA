#include "BookingRepository.h"

#include <fstream>
#include <sstream>

vector<BookingRequest>
BookingRepository::loadFromFile(
    const string& filename
) {
    vector<BookingRequest> requests;

    ifstream file(filename);

    if (!file.is_open()) {
        return requests;
    }

    // Đọc số lượng request
    int M;
    file >> M;

    // Bỏ phần xuống dòng còn lại
    string line;
    getline(file, line);

    for (int i = 0; i < M; i++) {

        getline(file, line);

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string requestId;
        string showtimeId;
        string seatId;
        string customerId;
        string timestamp;
        string status;

        getline(ss, requestId, '|');
        getline(ss, showtimeId, '|');
        getline(ss, seatId, '|');
        getline(ss, customerId, '|');
        getline(ss, timestamp, '|');
        getline(ss, status, '|');

        BookingRequest request(
            requestId,
            showtimeId,
            seatId,
            customerId,
            timestamp,
            status
        );

        requests.push_back(request);
    }

    file.close();

    return requests;
}