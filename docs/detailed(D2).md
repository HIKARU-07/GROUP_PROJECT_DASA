# Báo cáo bài tập D2
## Nội dung báo cáo Project – D2 – Nộp Tài liệu Yêu cầu & Bài toán
## Lĩnh vực của nhóm chọn: Hệ thống đặt vé sự kiện / Rạp chiếu phim



### YC2: Danh các phim vừa xem gần đây (Recently Viewed Movies).
#### Bối cảnh
- Để tăng trải nghiệm cá nhân hóa cho khách hàng, hệ thống cần lưu lại lịch sử các bộ phim mà người dùng vừa xem thông tin trên ứng dụng. Khi khách hàng mua vé của một bộ phim, Movie ID của bộ phim đó được thêm vào danh sách "Các phim vừa xem gần đây".
- Danh sách chỉ lưu tối đa 5 bộ phim gần nhất, được sắp xếp theo thứ tự từ phim vừa xem gần nhất đến phim xem lâu nhất.
- Nếu khách hàng mua lại một bộ phim đã có trong danh sách, hệ thống không tạo thêm bản sao mà đưa bộ phim đó lên vị trí đầu tiên. Nếu danh sách đã có đủ 5 phim và khách hàng xem một phim mới, phim ở vị trí cuối cùng sẽ bị loại bỏ.
- Do đây là bộ nhớ tạm có kích thước nhỏ và thường xuyên được cập nhật, hệ thống cần sử dụng cấu trúc dữ liệu phù hợp để thao tác thêm, xóa và cập nhật vị trí nhanh chóng
#### Input:
-	Dòng 1: số nguyên N, M – Số ID tồn tại trong danh sách , Số ID phim mới xem.
-	N dòng tiếp theo chứa ID các phim coi từ mới nhất nhất dến cũ nhất.
-	M dòng tiêp theo chứa ID của các mới xem.
#### Output
-	Nếu lịch sử xem của khách hàng có tồn tại ít nhất 1 bộ phim thì
-	In ra toàn bộ phim có trong danh sách theo trình tự thời gian, mỗi hàng một ID phim.
-	Còn nếu lịch sử xem phim trống thì in: “Không có lịch sử xem phim gần đây”
#### Ràng buộc
-	Danh sách tối đa 5 phần tử. 0 <= N <= 5
-	Danh sách không chứa phần tử trùng lập.
-   Quy ước vị trí 0 là phim xem gần nhất
-	Phim được coi từ danh sách được đẩy lên vị trí đầu tiên không thêm mới.
-	Với kích thước danh sách tối đa 5 phần tử, thao tác phải nhanh và không làm ảnh hưởng dữ liệu tổng thể.
#### Trường hợp ngoại lệ (Edge casse)
-	Tài khoản mới tạo chưa tồn tại danh sách đã xem.
-	Tài khoản mua vé nhưng không check-in xem phim.

