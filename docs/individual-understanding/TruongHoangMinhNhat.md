<style>
  body { font-family: "Times New Roman", Times, serif; }
</style>

# Bài Đọc hiểu tài tài cá nhân - D1
# Trương Hoàng Minh Nhật - 25110282


## 1. Quy mô và mục tiêu
Hệ thồng quản lý rạp chiếu phim bao gồm 2 đối tượng chính là nhân viên và khách hàng. Với các yêu cầu là quản lý phim, suất chiếu, vé và các yêu cầu đặt ghế cho một chuỗi rạp. Em nhận định đây là một hệ thống với dữ liệu vô cùng lớn vì số vé và số khách hàng có thể lên đến hàng triệu. Và việc xử lí dữ liệu được thông thông qua các thao tác đặt vé, hủy vé, kiểm tra vé, tìm kiếm suất chiếu với tốc độ phản hồi nhanh.

## 2. Hai yêu cầu bắt buộc

# MC1 – Tra cứu vé theo mã: 
Nhân viên nhập mã vào hệ thống, hệ thống sẽ kiểm tra mã vé có hợp lệ hay không ra cho ra thông báo tương ứng theo một thứ tự, dựa vào các yêu cầu sau đây: định dạng của mã, mã có tồn tại hay chưa, vé hết hạn/còn hạn, vé đã sử dụng/hay chưa, dữ liệu thời gian không hợp lệ và mã bị trùng khi nạp dữ liệu hay không.

# MC2 – Xử lý yêu cầu đặt ghế theo thứ tự:
Khi phim được nhiều người mua vé, có nhiều người bấm mua cùng một ghế ở cùng thời điểm. Mỗi người lúc bấm mua sẽ có một mã ID được đưa vào hệ thống, mặc dù thời gian được làm chính xác đến từng ms nhưng không thể thiếu trường hợp cả hai cùng có chung thời gian, nên mã ID sẽ được so sánh để cho ra độ ưu tiên. Lúc này, hệ thống cần phải tự động lọc và xử lý các tình huống nếu có như: trùng thời gian, cùng chọn một ghế, người dùng đã hủy, ID nhập sai hoặc ghế đó đã hết.

## 3. Ba yêu cầu tự phát

# YC1: Hoàn tác thao tác (Undo)
Hỗ trợ hủy thao tác bấm nhầm ghế hoặc combo để quay lại bước liền trước. Hệ thống chỉ lưu tối đa một số lượng thao tác nhất định, thời gian sẽ được tính từ lúc thao tác để ghi nhớ, cứ đủ 15 phút thì thao tác sẽ bị loại. Và việc thoát ứng dụng cũng sẽ khiến cho tính năng này reset.

# YC2: Danh sách phim vừa xem
Lưu 5 phim xem gần đây nhất để khách truy cập lại nhanh, danh sách sẽ không bị trùng vì nếu đã xem rồi mà xem lại thì phim đó sẽ được đưa lên đầu. Nếu danh sách đạt tối đa và có phim mới xem thì phim cũ nhất sẽ bị xóa khỏi danh sách. Thứ tự được cập nhật khi bạn xem phim.

# YC3: Lọc suất chiếu theo khoảng thời gian
Tinh năng tìm các suất chiếu của một phim trong khoảng thời gian được chọn trước (ví dụ 15:00 - 17:00) và kết quả trả về là xếp tăng dần theo giờ chiếu. Các trường hợp cần xử lý: không có suất trong khoảng tìm kiếm, suất nằm đúng mốc tìm kiếm, nhiều suất chiếu cùng giờ.

## 3.Kết luận: 
Em đánh giá đây là một đề tài không phải qua mới nhưng nó đủ các yếu tố liên quan về đối tượng và các cấu trúc dữ liệu được thiết lập như thế nào để tối ưu. Đây là đề tài rất ổn và đủ sức để nhóm làm đồ án cuối kì, vận dụng được các kiến thức đã được học.