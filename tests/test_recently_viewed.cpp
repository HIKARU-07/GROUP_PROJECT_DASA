#include <iostream>
#include "../src/services/RecentlyViewedService.h"

using namespace std;

int main(){
    RecentlyViewedService service;

    Movie movie1;
    movie1.movieId = "M001";

    Movie movie2;
    movie2.movieId = "M002";

    Movie movie3;
    movie3.movieId = "M003";

    Movie movie4;
    movie4.movieId = "M004";

    Movie movie5;
    movie5.movieId = "M005";

    Movie movie6;
    movie6.movieId = "M006";


    cout << "===== TEST APPEND =====\n";

    service.append(movie1);
    service.append(movie2);
    service.append(movie3);

    service.print();


    cout << "\n===== TEST VIEW =====\n";

    service.clear();

    service.view(movie1);
    service.view(movie2);
    service.view(movie3);

    service.print();


    cout << "\n===== TEST VIEW DUPLICATE =====\n";

    service.view(movie1);

    service.print();

    
    cout << "\n===== TEST VIEW FULL =====\n";

    service.view(movie5);
    service.view(movie4);

    service.print();


    cout << "\n===== TEST VIEW FULL & DULICATE =====\n";

    service.view(movie3);

    service.print();

    
    cout << "\n===== TEST MAX SIZE =====\n";

    service.clear();

    service.view(movie1);
    service.view(movie2);
    service.view(movie3);
    service.view(movie4);
    service.view(movie5);
    service.view(movie6);

    service.print();

    cout << "\nSize: " << service.getSize() << endl;


    cout << "\n===== TEST GET MOVIE ID =====\n";

    cout << "Index 0: " << service.getMovieId(0) << endl;
    cout << "Index 1: " << service.getMovieId(1) << endl;
    cout << "Index 2: " << service.getMovieId(2) << endl;


    cout << "\n===== TEST CLEAR =====\n";

    service.clear();

    cout << "Size after clear: "
         << service.getSize() << endl;

    cout << "Empty: "
         << (service.isEmpty() ? "true" : "false")
         << endl;

    return 0;
}