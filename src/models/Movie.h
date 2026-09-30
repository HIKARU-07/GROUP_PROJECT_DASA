#pragma once

#include <string>

using namespace std;

struct Movie{
    string movieId;
    string movieName;

    bool operator == (const Movie& other) const{
        return movieId == other.movieId;
    }

    bool operator!=(const Movie& other) const{
        return movieId != other.movieId;
    }
};
