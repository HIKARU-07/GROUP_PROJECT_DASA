# NHẬT KÝ GỠ LỖI (DEBUG LOG)

*Nhóm em đã sử dụng AI để tạo ra form mẫu, sau đó chỉnh sửa lại theo đúng những gì nhóm chúng em thực hiện*

> **Lưu ý:** Mọi lỗi phát sinh trong quá trình phát triển đều được ghi lại tại đây.

| STT | Ngày | Người phát hiện | File/Module | Mô tả lỗi (Bug Description) | Nguyên nhân (Root Cause) | Cách khắc phục (Solution) | Trạng thái |
|:---:|:---:|:---|:---|:---|:---|:---|:---:|
| 1 | 30/09 | Hoàng | `DoubleLinkedList.cpp` | Thao tác DELETE quên chỉnh sửa lại size & prev | Lúc cài đặt bị thiếu sót | Chỉnh sửa cho phù hợp | ✅ Đã sửa |
| 2 | 02/10 | Nhật | `HashTable.h` | Debug | Hai mục HashTable và DoubleLinkedList xung đột với nhau | Doubly thay đổi nhưng HashTable vẫn chưa được cập nhật | ✅ Đã sửa |
| 3 | 04/10 | Hiếu | `TicketService.cpp` | Mã vé có chữ cái cuối viết thường (VD: `VN-CINEMA-72538b`) trả về `NOT_FOUND` thay vì `INVALID_FORMAT` | Hàm `checkId` dùng `isalpha` nên chấp nhận cả chữ thường, mã vé qua bước kiểm tra định dạng rồi mới bị loại ở bước tìm vé | Thay `isalpha` bằng so sánh trực tiếp `id[15] < 'A' \|\| id[15] > 'Z'` để chỉ nhận chữ cái in hoa | ✅ Đã sửa |
| 2 | 04/10 | Hiếu | `index.html`| Giao diện web cũng trả về `NOT_FOUND` với mã vé có chữ cái cuối viết thường, không khớp với bản C++ | Regex `checkId` dùng `[A-Za-z]` nên nhận cả chữ thường | Đổi regex thành `/^VN-CINEMA-\d{5}[A-Z]$/` để khớp với bản C++ | ✅ Đã sửa |

## Bài học kinh nghiệm sau khi Debug
