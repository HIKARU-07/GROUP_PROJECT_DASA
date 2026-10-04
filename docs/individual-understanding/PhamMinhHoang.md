<style>
  body { font-family: "Times New Roman", Times, serif; }
</style>

# BÀI ĐỌC-HIỂU ĐỀ BÀI CÁ NHÂN – D1
# Phạm Minh Hoàng – 25110205

## 1. Vấn đề và quy mô
Hệ thống quản lý phim, suất chiếu, vé và các yêu cầu đặt ghế cho một chuỗi rạp có nhiều cụm. Người dùng bao gồm khách hàng và nhân viên rạp. Khách hàng có thể tra cứu phim và suất chiếu, đặt vé, hoàn tác khi chọn sai và xem lại danh sách phim mình vừa xem. Nhân viên rạp sẽ kiểm tra vé của bạn tại cổng bằng Booking Reference ID. Với số vé có thể lên tới khoảng một triệu và dữ liệu thay đổi liên tục, nếu mỗi lần kiểm tra lại phải duyệt hết danh sách thì sẽ quá chậm.

## 2. Hai yêu cầu bắt buộc
MC1 – Tra cứu vé theo mã: Nhân viên nhập mã vào hệ thống, hệ thống sẽ trả về vé hợp lệ hoặc nêu rõ lý do từ chối. Các điều kiện sẽ được kiểm tra theo thứ tự, các tình huống cần được dự đoán bao gồm mã sai định dạng, mã không tồn tại, vé hết hạn, vé đã sử dụng, dữ liệu thời gian không hợp lệ và mã bị trùng khi nạp dữ liệu.

MC2 – Xử lý yêu cầu đặt ghế theo thứ tự: Khi phim đang hot, có nhiều người có thể bấm chọn cùng một ghế ở cùng thời điểm. Tất cả các yêu cầu sẽ được hệ thống tập hợp lại và ưu tiên xử lý cái nào có thời gian đến trước, trong trường hợp thời gian bị trùng, hệ thống sẽ so sánh ID của các yêu cầu. Mỗi ghế trong từng suất chiếu chỉ được giữ cho một người đúng một điểm. Vào thời điểm này, hệ thống cần phải tự động lọc và xử lý các tình huống phát sinh: yêu cầu gửi lệch giờ, trùng thời gian, cùng chọn một ghế, người dùng đã hủy lệnh, ID nhập sai định dạng hoặc ghế đó đã hết lượt giữ.

## 3. Ba yêu cầu tự phát
YC1: Hoàn tác thao tác gần nhất: Hỗ trợ hủy thao tác bấm nhầm ghế hoặc combo để quay lại bước liền trước. Hệ thống chỉ lưu tối đa số lượng thao tác nhất định và mỗi thao tác chỉ có hiệu lực khi chưa quá 15 phút. Cần xử lý các trường hợp: chưa có thao tác nào, thao tác đã quá 15 phút, và khi vượt quá số lượng thao tác nhất định cho phép thì tự xóa cái cũ nhất để lưu cái mới.

YC2: Danh sách phim vừa xem: Lưu tối đa 5 phim xem gần đây nhất để khách truy cập lại nhanh, danh sách không chứa phim trùng, nếu xem lại phim đã có thì đưa lên trên cùng, nếu danh sách đạt tối đa mà xem phim mới thì xóa phim cũ nhất đi. Thứ tự luôn cập nhật liên tục theo mốc thời gian xem mới nhất.

YC3: Lọc suất chiếu theo khoảng thời gian: Cho phép tìm các suất chiếu của một phim trong khoảng giờ chọn trước (ví dụ 18:00 - 23:00) và kết quả trả về là xếp tăng dần theo giờ chiếu. Cần xử lý các trường hợp: không có suất nào trong khoảng tìm kiếm, suất nằm đúng mốc tìm kiếm khung giờ, nhiều suất chiếu cùng giờ, và khoảng giờ bị nhập ngược.

## 4. Cách thức sử dụng dữ liệu và những điểm cần chú ý trong quá trình thiết kế
Kiểm tra vé theo mã (MC1): Tần suất rất cao vào giờ cao điểm, chủ yếu là đọc dữ liệu để tra cứu. Không yêu cầu sắp xếp thứ tự.

Lấy yêu cầu đặt ghế kế tiếp (MC2): Tần suất cao khi mở bán phim hot, liên tục thêm mới và lấy ra xử lý. Bắt buộc sắp xếp theo thời gian, nếu trùng thì theo ID của các yêu cầu.

Hoàn tác: Tần suất sử dụng không cao, thực hiện từng lần một. Chỉ xoá ở vị trí mới nhất (thao tác gần đây nhất).

Phim vừa xem: Thông tin sẽ được cập nhật mỗi khi xem phim mới. Danh sách sắp xếp theo thứ tự thời gian, từ phim gần đây nhất.

Lọc suất chiếu dựa trên khoảng thời gian: Tần suất trung bình đến cao, chủ yếu liên quan đến việc đọc dữ liệu. Cần sắp xếp kết quả theo thứ tự tăng dần từ giờ bắt đầu.

## 5. Kết luận
Theo em, đề tài này đủ rộng để nhóm em phải dùng nhiều kiến thức khác nhau, không chỉ một cấu trúc dữ liệu. Đề tài cũng gần với mấy hệ thống check-in vé ngoài đời nên dễ hình dung yêu cầu và tự nghĩ ra được mấy trường hợp cần xử lý.
