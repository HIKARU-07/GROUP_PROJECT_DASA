# BÁO CÁO THIẾT KẾ & BIỆN MINH LỰA CHỌN CẤU TRÚC DỮ LIỆU

**Mã lớp HP:** 261DASA230179_06  
**Đồ án:** Hệ thống đặt vé sự kiện / Rạp chiếu phim  
---
*Nhóm em đã sử dụng AI để tạo ra form mẫu, sau đó chỉnh sửa lại theo đúng những gì nhóm chúng em thực hiện*
---

## I. KIẾN TRÚC HỆ THỐNG

Hệ thống chia làm 3 tầng, mỗi tầng một việc:

**1. Presentation (CLI)**
Nhận input từ người dùng, gọi hàm xử lý, in kết quả ra màn hình. Không chứa logic cấu trúc dữ liệu.

**2. DSA Core**
Chứa 3 cấu trúc dữ liệu tự cài đặt: `HashTable`, `PriorityQueue`, `DoubleLinkedList`. Đây là nơi xử lý MC1, MC2 và các yêu cầu tự phát hiện.

**3. Persistence**
Đọc file text khi khởi động, ghi file khi tắt chương trình. Chỉ load và save, không dùng SQL hay ORDER BY để trả lời truy vấn.

---

## II. PHÂN TÍCH & CHỌN CẤU TRÚC DỮ LIỆU

### 1. MC1 — Tra cứu vé theo Booking ID
**Bài toán:** Nhân viên quét mã vé, hệ thống phải trả kết quả trong thời gian ngắn. Dữ liệu có thể lên tới hàng triệu vé.

**Phân tích:**
- Thao tác chính: tìm chính xác theo `booking_id`.
- Không cần sắp xếp hay duyệt theo thứ tự.
- Tần suất đọc rất cao, ghi thấp.
- Yêu cầu: trung bình O(1).

**Chọn:** `HashTable.h` tự cài đặt.

**Đánh đổi:** Chấp nhận worst-case O(n) khi xảy ra va chạm. Nếu sau này cần liệt kê vé theo thứ tự thời gian, Hash Table không làm được — phải dùng thêm cấu trúc khác.

---

### 2. MC2 — Xử lý yêu cầu đặt ghế theo thứ tự ưu tiên
**Bài toán:** Nhiều khách đặt cùng lúc, hệ thống phải xử lý theo timestamp tăng dần. Nếu trùng timestamp, ưu tiên request_id nhỏ hơn.

**Phân tích:**
- Thao tác chính: lấy ra phần tử có timestamp nhỏ nhất.
- Cần so sánh hai yếu tố: timestamp, sau đó đến request_id.
- Dữ liệu đầu vào không được sắp xếp sẵn.
- Yêu cầu: O(log n) cho thao tác thêm và lấy ra.

**Chọn:** `PriorityQueue.h` (Min-Heap) tự cài đặt.

**Đánh đổi:** Heap cho phép lấy phần tử nhỏ nhất trong O(log n). Nhược điểm: muốn duyệt toàn bộ hàng đợi theo thứ tự phải pop ra rồi push lại. Với bài toán này, điều đó chấp nhận được vì chỉ cần lấy ra xử lý lần lượt.

---

### 3. Yêu cầu tự phát hiện 1 — Hoàn tác thao tác (Undo)
**Bài toán:** Khách chọn nhầm ghế hoặc combo, cần hoàn tác. Giới hạn 10 bước, hết hạn sau 15 phút.

**Phân tích:**
- Thao tác mới nhất được hoàn tác trước (LIFO).
- Kích thước tối đa 10 phần tử.
- Cần kiểm tra thời gian để loại bỏ thao tác cũ.

**Chọn:** `DoubleLinkedList.h` đóng vai trò như một Stack (thêm vào đầu, lấy ra từ đầu).

**Đánh đổi:** DLL cho phép push/pop ở đầu danh sách trong O(1). Muốn giới hạn 10 phần tử, chỉ cần kiểm tra size trước khi push. Muốn kiểm tra hết hạn, so sánh timestamp khi pop.

---

### 4. Yêu cầu tự phát hiện 2 — Danh sách phim vừa xem gần đây
**Bài toán:** Lưu tối đa 5 phim gần nhất. Khi xem phim mới, đẩy lên đầu. Nếu phim đã có trong danh sách, di chuyển lên đầu. Nếu đầy, xóa phim cuối.

**Phân tích:**
- Kích thước rất nhỏ (tối đa 5).
- Thao tác chính: thêm vào đầu, xóa ở cuối, di chuyển node lên đầu.
- Cần tra cứu nhanh xem phim đã tồn tại chưa.

**Chọn:** Kết hợp `DoubleLinkedList.h` và `HashTable.h`.

**Đánh đổi:** DLL cho phép thêm/xóa/di chuyển node trong O(1). Hash Table giúp tra cứu phim đã tồn tại trong O(1). Nếu chỉ dùng mảng, việc dịch chuyển phần tử tốn O(n).

---

### 5. Yêu cầu tự phát hiện 3 — Lọc suất chiếu theo khung giờ
**Bài toán:** Khách muốn xem phim trong khoảng [T1, T2], hệ thống trả về danh sách suất chiếu đã sắp xếp theo StartTime.

**Phân tích:**
- Thao tác chính: tìm kiếm theo khoảng thời gian, kết quả cần sắp xếp.
- Dữ liệu suất chiếu ít thay đổi.
- Cần duyệt theo thứ tự và tìm kiếm theo khoảng.

**Chọn:** `PriorityQueue.h` (Min-Heap) để trích xuất suất chiếu theo thứ tự thời gian.

**Đánh đổi:** Priority Queue cho phép lấy ra suất chiếu có StartTime nhỏ nhất một cách nhanh chóng. Để lấy được tất cả các suất chiếu trong khoảng [T1, T2], nhóm thực hiện pop lần lượt cho đến khi vượt quá T2. Cách này chấp nhận được vì số lượng suất chiếu thỏa mãn điều kiện lọc thường không lớn.

---

## III. YÊU CẦU XUNG ĐỘT

**Xung đột:** MC1 cần tra cứu nhanh theo ID (Hash Table), MC2 và yêu cầu lọc suất chiếu cần duyệt theo thứ tự (Priority Queue / DLL). Không có cấu trúc nào làm tốt cả hai.

**Giải pháp:** Kết hợp các cấu trúc.

- `HashTable` giữ vai trò chỉ mục chính để tra cứu vé theo `booking_id`.
- `PriorityQueue` giữ vai trò xử lý hàng đợi đặt ghế và trích xuất suất chiếu theo thời gian.
- `DoubleLinkedList` giữ vai trò quản lý lịch sử thao tác (Undo) và danh sách phim gần đây.
- Khi thêm hoặc xóa dữ liệu, cập nhật đồng bộ các cấu trúc liên quan.

**Chấp nhận:** Tốn thêm bộ nhớ và thời gian ghi. Đổi lại, thao tác đọc nhanh hơn.

---

## IV. PHƯƠNG ÁN BỊ LOẠI

| Phương án | Lý do loại |
|:---|:---|
| Mảng động cho MC1 | Tìm kiếm tuyến tính O(n), quá chậm với hàng triệu vé. |
| Hash Table cho MC2 | Không lấy được phần tử nhỏ nhất một cách hiệu quả. |
| SQLite xử lý truy vấn | Vi phạm yêu cầu kiến trúc, tầng Persistence chỉ được load/save. |
| Mảng cho Recently Viewed | Chèn/xóa/di chuyển tốn O(n), không đáp ứng yêu cầu nhanh. |

---

## V. SƠ ĐỒ KIẾN TRÚC
