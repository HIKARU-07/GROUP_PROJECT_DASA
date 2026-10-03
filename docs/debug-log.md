# NHẬT KÝ GỠ LỖI (DEBUG LOG)

*Nhóm em đã sử dụng AI để tạo ra form mẫu, sau đó chỉnh sửa lại theo đúng những gì nhóm chúng em thực hiện*

> **Lưu ý:** Mọi lỗi phát sinh trong quá trình phát triển đều được ghi lại tại đây.

| STT | Ngày | Người phát hiện | File/Module | Mô tả lỗi (Bug Description) | Nguyên nhân (Root Cause) | Cách khắc phục (Solution) | Trạng thái |
|:---:|:---:|:---|:---|:---|:---|:---|:---:|
| 1 | 30/09 | Hoàng | `DoubleLinkedList.cpp` | Thao tác DELETE quên chỉnh sửa lại size & prev | Lúc cài đặt bị thiếu sót | Chỉnh sửa cho phù hợp | ✅ Đã sửa |
| 2 | 02/10 | Nhật | `HashTable.h` | Debug | Hai mục HashTable và DoubleLinkedList xung đột với nhau | Doubly thay đổi nhưng HashTable vẫn chưa được cập nhật | ✅ Đã sửa |


## Bài học kinh nghiệm sau khi Debug
