# D1 – BÀI ĐỌC-HIỂU ĐỀ BÀI CÁ NHÂN

**Lĩnh vực:** Hệ thống đặt vé sự kiện / Rạp chiếu phim

## 1. Hiểu bài toán

Hệ thống quản lý hoạt động đặt và kiểm tra vé trong rạp chiếu phim. Dữ liệu có thể rất lớn và hệ thống cần xử lý nhiều thao tác như kiểm tra vé, xử lý yêu cầu đặt ghế, xem phim gần đây, hoàn tác thao tác và tìm suất chiếu theo thời gian.

## 2. MC1 – Kiểm tra vé

Nhân viên nhập `booking_id` để kiểm tra vé tại cổng.

### Input

- Số lượng vé.
- Thông tin vé: `booking_id`, khách hàng, phim, suất chiếu, rạp, phòng, ghế và trạng thái.
- Danh sách mã vé cần kiểm tra.
- `CURRENT_TIME`.

### Output

Mỗi mã vé trả về một trong các kết quả:

- `VALID`
- `INVALID_FORMAT`
- `NOT_FOUND`
- `EXPIRED`
- `USED`

### Edge cases

- Mã vé sai định dạng.
- Mã vé không tồn tại.
- Vé đã hết hạn.
- Vé đã được sử dụng.
- Một mã vé được kiểm tra nhiều lần.
- Thời gian có định dạng không hợp lệ.

## 3. MC2 – Xử lý yêu cầu đặt ghế

Khi nhiều khách hàng cùng gửi yêu cầu đặt một ghế, hệ thống phải xử lý các yêu cầu theo đúng thứ tự thời gian.

### Input

Mỗi yêu cầu gồm:

`request_id | showtime_id | seat_id | customer_id | timestamp | request_status`

### Quy tắc xử lý

- Xử lý yêu cầu có `timestamp` sớm hơn trước.
- Nếu cùng thời gian thì ưu tiên `request_id` nhỏ hơn theo thứ tự từ điển.
- Kiểm tra định dạng và trạng thái hủy.
- Kiểm tra ghế đã được đặt hay chưa.
- Nếu chưa có yêu cầu khác giữ ghế thì khóa ghế.

### Output

- `LOCKED`
- `SEAT_TAKEN`
- `CANCELLED`
- `INVALID`

### Edge cases

- Nhiều yêu cầu cùng đặt một ghế.
- Hai yêu cầu có cùng thời gian.
- Yêu cầu đã bị hủy.
- `request_id` hoặc `seat_id` không hợp lệ.
- Dữ liệu đầu vào không được sắp xếp theo thời gian.
- Ghế không tồn tại.
- Dữ liệu thời gian không hợp lệ.

## 4. Yêu cầu tự phát hiện

### YC1 – Hoàn tác thao tác

Khách hàng có thể hoàn tác các thao tác gần đây như chọn ghế hoặc thêm combo.

- Chỉ hoàn tác thao tác gần nhất trước.
- Lưu tối đa 10 thao tác.
- Thao tác quá 15 phút không còn được hoàn tác.
- Nếu không còn thao tác hợp lệ thì trả về `FAILED DATA`.

### YC2 – Phim vừa xem gần đây

Hệ thống lưu tối đa 5 phim gần nhất.

- Phim mới xem được đưa lên đầu.
- Nếu phim đã tồn tại thì đưa lên đầu thay vì tạo bản sao.
- Khi vượt quá 5 phim, loại bỏ phim cũ nhất.

### YC3 – Lọc suất chiếu theo thời gian

Khách hàng có thể tìm các suất chiếu của một bộ phim trong khoảng `[T1, T2]`.

Kết quả cần:

- Đúng `MovieID` và ngày.
- Có `StartTime` nằm trong khoảng yêu cầu.
- Sắp xếp theo `StartTime`, sau đó `ShowtimeID` và `CinemaRoom`.
- Nếu không có kết quả thì trả về danh sách rỗng.

## 5. Nhận định cá nhân

Bài toán có nhiều kiểu truy cập dữ liệu: tìm chính xác theo mã, xử lý theo thứ tự ưu tiên, hoàn tác thao tác gần nhất, quản lý danh sách gần đây và tìm kiếm theo khoảng thời gian.

Vì vậy, trước khi lựa chọn cấu trúc dữ liệu, cần xác định rõ **dữ liệu đầu vào, kết quả đầu ra, tần suất thao tác và các trường hợp ngoại lệ** của từng yêu cầu.