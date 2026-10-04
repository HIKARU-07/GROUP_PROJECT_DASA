<style>
  body { font-family: "Times New Roman", Times, serif; }
</style>

## Nhận định cá nhân về đề tài - D1
## Phạm Hồng Tiến Minh - 25110271

Sau khi tìm hiểu đề bài, nhận thấy **“Hệ thống quản lý phim, suất chiếu và đặt vé cho chuỗi rạp”** là một bài toán có quy mô tương đối lớn, trong đó điểm đáng chú ý không chỉ nằm ở số lượng chức năng mà còn ở khối lượng dữ liệu và tần suất xử lý yêu cầu. Với số lượng vé có thể lên đến khoảng một triệu và các yêu cầu phát sinh liên tục, việc lựa chọn cách tổ chức và truy xuất dữ liệu có ảnh hưởng trực tiếp đến hiệu quả của hệ thống.

Đối với hai yêu cầu bắt buộc, em nhận thấy mỗi yêu cầu đặt ra một bài toán xử lý khác nhau. **MC1 – Tra cứu vé theo mã** yêu cầu khả năng tìm kiếm nhanh trong lượng dữ liệu lớn, đồng thời phải kiểm tra nhiều điều kiện để xác định vé hợp lệ. Trong khi đó, **MC2 – Xử lý yêu cầu đặt ghế** tập trung vào việc duy trì đúng thứ tự ưu tiên khi có nhiều yêu cầu cùng thời điểm, đặc biệt khi xảy ra trường hợp trùng thời gian hoặc nhiều người cùng chọn một ghế.

Ba yêu cầu tự phát cũng có những đặc điểm riêng. **YC1 – Hoàn tác** yêu cầu xử lý thao tác gần nhất trước và giới hạn thời gian hiệu lực. **YC2 – Danh sách phim vừa xem** yêu cầu liên tục cập nhật thứ tự phim theo thời gian xem, đồng thời loại bỏ phần tử cũ khi vượt quá giới hạn. **YC3 – Lọc suất chiếu** yêu cầu tìm kiếm theo điều kiện thời gian và trả kết quả theo thứ tự tăng dần.

Qua đó, em nhận thấy điểm quan trọng của đề tài là **không thể áp dụng một cách tổ chức dữ liệu giống nhau cho tất cả các chức năng**. Mỗi yêu cầu có đặc điểm khác nhau về tần suất truy cập, cách thêm và loại bỏ dữ liệu, thứ tự xử lý cũng như yêu cầu về thời gian. Vì vậy, trước khi triển khai, cần phân tích đặc điểm của từng nghiệp vụ để lựa chọn cấu trúc dữ liệu và thuật toán phù hợp.

Bên cạnh chức năng chính, các trường hợp ngoại lệ như mã vé không hợp lệ, dữ liệu trùng, yêu cầu bị hủy, ghế đã được giữ, thời gian không hợp lệ hoặc thao tác Undo đã quá thời hạn cũng cần được xem xét ngay trong quá trình thiết kế. Việc xử lý đầy đủ các trường hợp này giúp hệ thống hoạt động ổn định và đảm bảo kết quả đúng với yêu cầu đề bài.

### Kết luận

Em đánh giá đây là một đề tài phù hợp với mục tiêu của đồ án cuối kỳ vì yêu cầu người thực hiện kết hợp giữa **phân tích nhiệm vụ, cấu trúc dữ liệu, thuật toán và lập trình hướng đối tượng**. Đối với em, giá trị chính của đề tài nằm ở việc phải đưa ra được giải pháp phù hợp với từng loại dữ liệu và chứng minh được sự lựa chọn đó về cả tính chính xác lẫn hiệu quả xử lý.