<style>
  body { font-family: "Times New Roman", Times, serif; }
</style>


# BIÊN BẢN ĐÁNH GIÁ CHÉO & REVIEW KỸ THUẬT (PEER REVIEW)

> **Mã lớp HP:** 261DASA230179_06
> **Tên đồ án:** Hệ thống đặt vé sự kiện / Rạp chiếu phim
> **Ngày thực hiện:** 22/09/2026
---

## I. BẢNG TỔNG HỢP ĐÁNH GIÁ ĐÓNG GÓP (PEER RATING)
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
- **Thành phần review:** `TicketService.cpp`
- **Nhận xét:** Chọn bảng băm lưu vé là hợp lý, nhưng kích thước cố định nên thêm nhiều vé sẽ chậm dần; ô dùng danh sách liên kết đôi hơi thừa, chỉ cần đơn, thêm/tìm vé phải duyệt từng phần tử trong ô nên ô dài thì lâu, thứ tự kiểm tra (định dạng, tồn tại, hết hạn, đã dùng) hợp lý vì cái nhẹ làm trước; ba chỗ chưa tối ưu xử lí: tháng 2 luôn 28 ngày nên 29/02 bị coi sai, mỗi năm luôn 365 ngày nên đếm thời gian lệch (cái này cũng một phần do nhóm đã thống nhất để đi trọng tâm hơn vào việc xử lý), kiểm "hết hạn" trước "đã dùng" nên vé vừa hết hạn vừa đã dùng có thể báo nhầm. Về điểm tốt, bạn tách hàm nhỏ dễ đọc, các điều kiện đặt ra được điểm tra khá kĩ càng.

- **Kết luận:** Cấu trúc đúng hướng, đáp ứng đủ cho bài tập, chọn hash + linked list hợp lý.

### 2. Review của Lê Bùi Minh Hiếu cho phần code của Trương Hoàng Minh Nhật
**Thành phần review:** Showtime.h - ShowtimeService.h - ShowtimeService.cpp - HashTable.h

**Nhận xét:** Thành viên triển khai khá tốt chức năng **Showtime Search**, sử dụng `HashTable` tự cài đặt để gom các suất chiếu theo khóa `MovieID|Date`, nên tra cứu nhóm suất chiếu trong O(1). `HashTable` tự động `resize()` khi hệ số tải vượt 0.75 nên chuỗi luôn ngắn. Các suất trong mỗi nhóm được sắp xếp theo `StartTime`, rồi `ShowtimeID`, rồi `CinemaRoom`, và dùng `lower_bound` để tìm suất đầu tiên từ T1, nên việc lọc theo khung giờ nhanh và cho kết quả đúng thứ tự. Dữ liệu đầu vào cũng được kiểm tra cẩn thận, dòng sai định dạng bị bỏ qua mà không ảnh hưởng việc nạp file.

**Kết luận:** Nhìn chung, thành viên hoàn thành tốt chức năng đã được giao, hiểu và áp dụng đúng `HashTable` kết hợp `lower_bound` để giải quyết bài toán lọc suất chiếu theo khung giờ.

### 3. Review của Trương Hoàng Minh Nhật cho phần code của Tào Lê Quốc Anh
- **Thành phần review:** BookingRequest.h - BookingService.cpp - BookingService.h - PriorityQueue.h
- **Nhận xét:** Thành viên triển khai khá tốt chức năng **BookingRequest** và **BookingService**, sử dụng `PriorityQueue` để thực hiện thứ tự xử lí công việc. Hàng đợi ưu tiên cài bằng heap hoạt động đúng, với `push()` và `pop()` có độ phức tạp O(log n) khá nhanh. Yêu cầu có thời gian sớm hơn được xử lý trước, và khi bằng nhau thì so theo requestID, nên thứ tự xử lý công bằng và luôn xác định. Việc lưu khóa chọn ghế trong `unordered_set` giúp kiểm tra ghế đã bị giữ trong O(1), ngăn đặt trùng ghế trong cùng một suất chiếu mà vẫn phân biệt được các suất khác nhau.

- **Kết luận:** Nhìn chung, thành viên hoàn thành tốt chức năng đã được giao, hiểu và áp dụng nhiều cấu trúc mới như `PriorityQueue` để giải quyết thứ tự công việc cần xử lý.

### 4. Review của Tào Lê Quốc Anh cho phần code của Phạm Hồng Tiến Minh
- **Thành phần review:** Stack.h - UndoAction.h - UndoService.h - UndoService.cpp

- **Nhận xét:** Phần Stack được cài đặt bằng Linked List và tuân thủ đúng nguyên lý LIFO. Các thao tác chính như push(), pop(), peek() được xây dựng rõ ràng, trong đó push() và pop() có độ phức tạp O(1). Code có kiểm tra trạng thái Stack và thực hiện giải phóng bộ nhớ, giúp hạn chế lỗi trong quá trình sử dụng. Tuy nhiên, việc giới hạn kích thước Stack cố định và sử dụng get() cần duyệt phần tử khiến tính linh hoạt và hiệu năng chưa tối ưu trong một số trường hợp.

  Phần Undo sử dụng Stack để lưu lịch sử thao tác, phù hợp với đặc điểm Undo vì thao tác gần nhất sẽ được xử lý trước. UndoService có tổ chức tương đối rõ ràng, có kiểm tra loại thao tác và thời gian Undo, đồng thời có file test riêng để kiểm tra chức năng. Tuy nhiên, chức năng Undo hiện chủ yếu mới xử lý và mô phỏng việc hoàn tác thông qua kết quả xuất ra, chưa thực sự cập nhật trạng thái của hệ thống đặt vé. Ngoài ra, phần xử lý Undo mới tập trung vào một số loại thao tác nhất định nên khả năng mở rộng còn hạn chế.

- **Kết luận:** Nhìn chung, phần Stack được triển khai đúng cấu trúc dữ liệu và đáp ứng tốt yêu cầu của bài toán. Phần Undo cũng lựa chọn Stack phù hợp và thể hiện được cách ứng dụng cấu trúc dữ liệu vào một chức năng thực tế. Code có cấu trúc tương đối rõ ràng và có kiểm thử, tuy nhiên cần cải thiện khả năng tích hợp Undo với trạng thái thực tế của hệ thống và mở rộng các loại thao tác có thể hoàn tác.

### 5. Review của Phạm Hồng Tiến Minh cho phần code của Phạm Minh Hoàng
- **Thành phần review:** DoubleLinkedList.h - RecentlyViewedService.cpp
- **Nhận xét:** Thành viên triển khai khá tốt chức năng **Recently Viewed**, sử dụng `DoubleLinkedList` phù hợp với yêu cầu vì có thể thêm/xóa ở đầu và cuối danh sách hiệu quả. Logic `view()` xử lý đúng trường hợp phim đã tồn tại bằng cách xóa phim cũ rồi đưa lên đầu, đồng thời giới hạn số lượng lịch sử thông qua `MAX`. Phần `DoubleLinkedList` được triển khai tương đối đầy đủ với `head`, `tail`, `prev/next`, destructor và `clear()` để quản lý và giải phóng bộ nhớ. Tuy nhiên, code vẫn cần cải thiện ở một số điểm như `getAt()` chưa tự kiểm tra phạm vi index.

- **Kết luận:** Nhìn chung, thành viên hoàn thành tốt chức năng được giao, hiểu và áp dụng đúng **Double Linked List** vào bài toán **Recently Viewed**. Code có nền tảng tốt.

---

## III. KẾT LUẬN CHUNG CỦA NHÓM

- **Tinh thần làm việc:** Nhóm làm nghiêm túc, hầu hết deadline đều đúng hạn. Phân công rõ ràng, ai gặp khó thì được hỗ trợ. Mọi người có ý thức với tiến độ chung, không để việc tồn rồi dồn cho người khác. Khi có bạn chưa hiểu phần code hay thiết kế thì những bạn còn lại ngồi lại trao đổi, có khi sửa giúp. Nhóm cũng thống nhất cách làm trước khi code nên ít bị lệch nhau.
- **Mức độ đóng góp:** Tương đối đồng đều, không có ai "ăn theo". Các thành viên đều đóng góp cả code lẫn lập luận thiết kế. Có bạn mạnh về cấu trúc dữ liệu, có bạn mạnh về xử lý logic và kiểm tra dữ liệu đầu vào, nhưng ghép lại thì phần của ai cũng rõ trong sản phẩm cuối. Mấy phần khó như thiết kế bảng băm, kiểm tra định dạng vé, xử lý thời gian đều chia nhau làm và review chéo.
---