#ifndef BOOKING_REPOSITORY_H
#define BOOKING_REPOSITORY_H

#include "../core/models/BookingRequest.h"

#include <string>
#include <vector>

using namespace std;

class BookingRepository {
public:

    vector<BookingRequest> loadFromFile(
        const string& filename
    );

    bool saveResultsToFile(
        const string& filename,
        const vector<string>& results
    );
};

#endif