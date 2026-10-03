### NHẬT KÝ SỬ DỤNG AI & PHẢN TƯ (AI LOG & REFLECTION)
> **Ngày cập nhập:** 22/09/2026
> **Nhóm thực hiện:** DASA_605
---
*Nhóm em đã sử dụng AI để tạo ra form mẫu, sau đó chỉnh sửa lại theo đúng những gì nhóm chúng em thực hiện*
## I. Mục tiêu sử dụng AI
Trong quá trình thực hiện đồ án, nhóm đã sử dụng AI như một công cụ hỗ trợ nhằm:
1. Gợi ý cấu trúc dữ liệu và giải thuật tối ưu.
2. Hỗ trợ tìm lỗi (debug) và giải thích thông báo lỗi.
3. Tối ưu hóa đoạn code.

*Nhóm cam kết không sử dụng AI để sinh ra toàn bộ mã nguồn chính, mọi đoạn code do AI gợi ý đều được thành viên trong nhóm kiểm tra, chạy thử và hiểu rõ logic trước khi áp dụng.*

## II. Nhật ký chi tiết (AI Usage Log)

| STT | Ngày | Thành viên | File/Module | Mục đích | Tóm tắt Prompt | Kết quả & Đánh giá |
|:---:|:---:|:---|:---|:---|:---|:---|
| 1 | 22/09 | Hoàng |  | Tạo và cập nhật cấu trúc Project ban đầu | Hãy giúp tôi tạo ra một cấu trúc Project theo Nội Dung hướng dẫn dưới đây | AI trả ra là một cấu trúc Project có sự phù hợp với những gì nhóm đã hướng đến |
| 3 | 23/09 | Hoàng | DoubleLinkedList | Tìm hướng giải quyết | Tôi muốn tạo một structure nhưng lại có 2 service dùng chung khác nhưng dữ liệu -> gợi ý | Gợi ý 2 service lưu 2 loại object khác nhau thì nên dùng template & em đã áp dụng và thấy hiệu quả |
| 4 | 25/09 | Nhật | HashTable | Tìm hướng giải quyết | Tôi muốn tạo một structure và tìm cách kết nối các service dùng chung khác nhau | Giải quyết xung đột giữa service HashTable và DoubleLinkedList |
| 5 | 27/09 | Minh | UndoService | Tìm hướng giải quyết | Với input có cấu trúc thế này thì hướng đi nào phù hợp để tách được 2 phần vào 2 dữ liệu khác nhau | Đưa ra hướng đi phù hợp kèm theo đó giải quyết luôn cả vấn đề tách command và target |
| 6 | 27/09 | Minh | UndoService | Tìm hướng giải quyết | Với định dạng YYYY-MM-DD HH:MM thì hướng nào để xử lí chuỗi và so sánh với chuỗi khác | Đưa ra thư viện để xử lí chuỗi sau đó so sánh với nhau để lấy được khoảng cách thời gian |
| 7 | 30/09 | Hoàng | DoubleLinkedList | Debug | Hiện tại đoạn mã nguồn của tôi như sau: .... tại sao khi chạy test nó lại báo lỗi ... | Đã giải quyết được vấn đề, kết quả nhận được khá là mới mẻ trong việc dùng operator== |
| 8 | 30/09 | Hiếu | test_mc1 | Sinh bộ testcase kiểm thử | Hãy giúp tôi sinh các testcase cho đầy đủ các trường hợp TicketService | Sinh ra danh sách testcase đầy đủ cho các trường hợp hợp lệ, hết hạn, đã dùng, không tìm thấy và sai định dạng |
| 9 | 02/10 | Nhật | HashTable | Debug | Hãy kiểm tra giúp tôi HashTable vì sao vẫn còn xung đột với DoublyLinkedList | Cần phải thêm operator cho giống của DoubleLinkedList (DLL) để cho HashTable hiểu được cùng kiểu dữ liệu với DLL |
| 10 | 02/10 | Nhật | test_showtime | Tìm hướng giải quyết | Dựa trên 6 tiêu chí để tìm kiếm một suất phù hợp, hãy giúp tôi viết code đúng yêu cầu, nếu sai thì nhảy ra ngay | Đúng như yêu cầu, kiểm tra lần lượt từng tiêu chí, nếu sai có thể fix nhanh chóng |

## III. Phản tư & Đánh giá (Reflection)

### 1. Phạm Minh Hoàng

### 2. Phạm Hồng Tiến Minh

### 3. Trương Hoàng Minh Nhật

### 4.

### 5.

## IV. Minh chứng (Evidence)
*Hình ảnh nhóm sử dụng AI để gỡ lỗi (Debug) trong quá trình làm việc:*
- Minh chứng 1:
![Minh chung 1 ](Image/minhchung1.png)
- Minh chứng 2:
![Minh chứng 2](Image/minhchung2.png)
- Minh chứng 3:
![Minh chứng 3](Image/minhchung3.png)
- Minh chứng 4:
![Minh chứng 4](Image/minhchung4.png)
- Minh chứng 5:
![Minh chứng 5](Image/minhchung5.png)
- Minh chứng 6:
![Minh chứng 6](Image/minhchung6.png)
- Minh chứng 7:
![Minh chứng 7](Image/minhchung7.png)
- Minh chứng 8:
![Minh chứng 8](Image/minhchung8.png)
- Minh chứng 9:
![Minh chứng 9](Image/minhchung9.png)
- Minh chứng 10:
![Minh chứng 10](Image/minhchung10.png)