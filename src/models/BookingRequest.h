#pragma once

#include <string>

using namespace std;

struct BookingRequest
{
    string requestId;
    string showtimeId;
    string seatId;
    string customerId;
    string timestamp;
    string requestStatus;
};
