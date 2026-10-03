#ifndef MAIN_H
#define MAIN_H
 
#include <iostream>
#include <string>
#include <vector>
#include <limits>
 
#include "services/TicketService.h"
#include "services/UndoService.h"
#include "services/RecentlyViewedService.h"
#include "services/BookingService.h"
#include "services/ShowtimeService.h"
 
// Xóa dữ liệu thừa trong bộ đệm nhập (dùng khi người dùng nhập sai kiểu)
void clearInputBuffer();
 
void showMenu();
 
#endif
