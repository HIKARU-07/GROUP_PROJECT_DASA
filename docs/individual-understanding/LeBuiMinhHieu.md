# D1 — BÀI ĐỌC-HIỂU ĐỀ BÀI CÁ NHÂN

**Họ tên:** Lê Bùi Minh Hiếu | **MSSV:** 25110197 | **Nhóm:** DASA_605 | **Lớp HP:** 261DASA230179_06

## 1. Bối cảnh và mục tiêu

Hệ thống đóng vai trò là một *records-and-decision engine* phục vụ công tác vận hành rạp chiếu phim. Hệ thống quản lý tập hợp bản ghi quy mô lớn gồm thông tin phim, suất chiếu, sơ đồ ghế và lịch sử giao dịch đặt vé. Mục tiêu cốt lõi là phản hồi tức thì các câu hỏi vận hành theo thời gian thực (đặt vé, hủy vé, kiểm tra vé, tìm kiếm suất chiếu) trong điều kiện dữ liệu biến động liên tục.

## 2. Đầu vào / Đầu ra / Ràng buộc

- **Đầu vào:** bản ghi vé (mã đặt vé, suất chiếu, trạng thái), yêu cầu đặt ghế có thời điểm gửi, thao tác của khách (chọn/bỏ ghế, xem phim, lọc suất chiếu).
- **Đầu ra:** kết quả quét vé (hợp lệ / không hợp lệ kèm lý do), yêu cầu đặt ghế tiếp theo cần xử lý, danh sách suất chiếu thuộc một khung giờ, danh sách phim vừa xem.
- **Ràng buộc:** dữ liệu lớn (giả định khoảng 10⁶ vé, 10⁵ lượt quét); tốc độ phản hồi các truy vấn chính duy trì ổn định, không suy giảm tuyến tính (O(n)) khi dữ liệu tăng trưởng; mọi thao tác truy xuất không được phép dùng giải pháp duyệt toàn bộ danh sách.

## 3. Hiểu về hai yêu cầu bắt buộc

- **MC1 (tra cứu chính xác):** tại cổng kiểm soát vé, nhân viên quét mã đặt vé và cần truy xuất đúng một bản ghi trong thời gian rất ngắn. Chỉ cần so khớp đúng định danh, không cần thứ tự. Kiểm tra theo trình tự: định dạng đúng → tồn tại → chưa hết hạn → chưa sử dụng → hợp lệ. Đảm bảo thời gian phản hồi cố định/tối thiểu bất kể quy mô dữ liệu.
- **MC2 (thứ tự / ưu tiên):** nhiều khách gửi yêu cầu đặt vé cùng thời điểm, hệ thống phải lấy ra yêu cầu sớm nhất để xử lý, lặp lại nhiều lần trong khi yêu cầu mới liên tục chen vào. Cần quy tắc phá hòa khi hai yêu cầu cùng thời điểm.

## 4. Yêu cầu tự phát hiện

1. **Hoàn tác khi chọn ghế/combo:** khách thay đổi ý kiến thì quay lại bước ngay trước đó, có giới hạn số bước và thời gian giữ chỗ.
2. **Danh sách phim vừa xem:** luôn cập nhật, số lượng nhỏ cố định, xem lại phim thì phim đó lên đầu danh sách, không trùng lặp.
3. **Lọc suất chiếu theo khung giờ:** kết quả phải theo thứ tự thời gian, giúp người dùng nhanh chóng tìm được suất phù hợp.

## 5. Trường hợp edge được nhận dạng trước khi thiết kế

Mã đặt vé sai định dạng hoặc không tồn tại; vé đúng nhưng quá hạn; vé đã được quét hai lần; hai yêu cầu cùng thời điểm; xem lại cùng một phim nhiều lần; khung giờ lọc suất chiếu không hợp lệ; dữ liệu rỗng.