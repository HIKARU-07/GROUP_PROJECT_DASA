# BIÊN BẢN ĐÁNH GIÁ CHÉO & REVIEW KỸ THUẬT (PEER REVIEW)

> **Mã lớp HP:** 261DASA230179_06
> **Tên đồ án:** Hệ thống đặt vé sự kiện / Rạp chiếu phim
> **Ngày thực hiện:** 22/09/2026
---
*Nhóm em đã sử dụng AI để tạo ra form mẫu, sau đó chỉnh sửa lại theo đúng những gì nhóm chúng em thực hiện*
## I. BẢNG TỔNG HỢP ĐÁNH GIÁ ĐÓNG GÓP (PEER RATING)

*Hướng dẫn: Mỗi thành viên tự đánh giá bản thân và đánh giá các thành viên còn lại dựa trên mức độ đóng góp thực tế. Điểm tối đa là 10. Điểm trung bình sẽ được dùng để điều chỉnh điểm cá nhân.*

| STT | Họ và Tên | MSSV | Mức độ hoàn thành (%) | Điểm đóng góp (1-10) | 
|:---:|:---|:---:|:---:|:---|
| 1 | Phạm Minh Hoàng | 25110205 |  100% | 10 | 
| 2 | Lê Bùi Minh Hiếu | 25110197 | 100% | 10 | 
| 3 | Phạm Hồng Tiến Minh | 25110271 | 100% | 10 | 
| 4 | Tào Lê Quốc Anh | 25110138 | 100% | 10 |
| 5 | Trương Hoàng Minh Nhật | 25110282 | 100% | 10 | 
---

## II. ĐÁNH GIÁ CHÉO KỸ THUẬT (PEER TECHNICAL REVIEW - D6)

*Mỗi thành viên chọn 1 thành phần code của bạn khác để review (tối đa nửa trang).*

### 1. Review của Phạm Minh Hoàng cho phần code của Lê Bùi Minh Hiếu 
- **Thành phần review:** 
- **Nhận xét:**

- **Kết luận:** 

### 2. Review của Lê Bùi Minh Hiếu cho phần code của Trương Hoàng Minh Nhật
**Thành phần review:** Showtime.h - ShowtimeService.h - ShowtimeService.cpp - HashTable.h

**Nhận xét:** Thành viên triển khai khá tốt chức năng **Showtime Search**, sử dụng `HashTable` tự cài đặt để gom các suất chiếu theo khóa `MovieID|Date`, nên tra cứu nhóm suất chiếu trong O(1). `HashTable` tự động `resize()` khi hệ số tải vượt 0.75 nên chuỗi luôn ngắn. Các suất trong mỗi nhóm được sắp xếp theo `StartTime`, rồi `ShowtimeID`, rồi `CinemaRoom`, và dùng `lower_bound` để tìm suất đầu tiên từ T1, nên việc lọc theo khung giờ nhanh và cho kết quả đúng thứ tự. Dữ liệu đầu vào cũng được kiểm tra cẩn thận, dòng sai định dạng bị bỏ qua mà không ảnh hưởng việc nạp file.

**Kết luận:** Nhìn chung, thành viên hoàn thành tốt chức năng đã được giao, hiểu và áp dụng đúng `HashTable` kết hợp `lower_bound` để giải quyết bài toán lọc suất chiếu theo khung giờ.

### 3. Review của Trương Hoàng Minh Nhật cho phần code của Tào Lê Quốc Anh
- **Thành phần review:** BookingRequest.h - BookingService.cpp - BookingService.h - PriorityQueue.h
- **Nhận xét:** Thành viên triển khai khá tốt chức năng **BookingRequest** và **BookingService**, sử dụng `PriorityQueue` để thực hiện thứ tự xử lí công việc. Hàng đợi ưu tiên cài bằng heap hoạt động đúng, với `push()` và `pop()` có độ phức tạp O(log n) khá nhanh. Yêu cầu có thời gian sớm hơn được xử lý trước, và khi bằng nhau thì so theo requestID, nên thứ tự xử lý công bằng và luôn xác định. Việc lưu khóa chọn ghế trong `unordered_set` giúp kiểm tra ghế đã bị giữ trong O(1), ngăn đặt trùng ghế trong cùng một suất chiếu mà vẫn phân biệt được các suất khác nhau.

- **Kết luận:** Nhìn chung, thành viên hoàn thành tốt chức năng đã được giao, hiểu và áp dụng nhiều cấu trúc mới như `PriorityQueue` để giải quyết thứ tự công việc cần xử lý.

### 4. Review của Tào Lê Quốc Anh cho phần code của Phạm Hồng Tiến Minh
- **Thành phần review:** 
- **Nhận xét:**

- **Kết luận:**

### 5. Review của Phạm Hồng Tiến Minh cho phần code của Phạm Minh Hoàng
- **Thành phần review:** DoubleLinkedList.h - RecentlyViewedService.cpp
- **Nhận xét:** Thành viên triển khai khá tốt chức năng **Recently Viewed**, sử dụng `DoubleLinkedList` phù hợp với yêu cầu vì có thể thêm/xóa ở đầu và cuối danh sách hiệu quả. Logic `view()` xử lý đúng trường hợp phim đã tồn tại bằng cách xóa phim cũ rồi đưa lên đầu, đồng thời giới hạn số lượng lịch sử thông qua `MAX`. Phần `DoubleLinkedList` được triển khai tương đối đầy đủ với `head`, `tail`, `prev/next`, destructor và `clear()` để quản lý và giải phóng bộ nhớ. Tuy nhiên, code vẫn cần cải thiện ở một số điểm như `getAt()` chưa tự kiểm tra phạm vi index.

- **Kết luận:** Nhìn chung, thành viên hoàn thành tốt chức năng được giao, hiểu và áp dụng đúng **Double Linked List** vào bài toán **Recently Viewed**. Code có nền tảng tốt.

---

## III. KẾT LUẬN CHUNG CỦA NHÓM

- **Tinh thần làm việc:** Nhóm làm việc nghiêm túc, hầu hết các deadline đều được hoàn thành đúng hạn. Có sự phân công rõ ràng và hỗ trợ lẫn nhau khi gặp khó khăn.
- **Mức độ đóng góp:** Tương đối đồng đều, không có thành viên nào "ăn theo". Các thành viên đều có đóng góp kỹ thuật thực chất (code) và đóng góp về lập luận (thiết kế).
- **Đề xuất điều chỉnh cá nhân (nếu có):** Không có đề xuất điều chỉnh đặc biệt, giữ nguyên theo điểm đóng góp ở Mục I.

---