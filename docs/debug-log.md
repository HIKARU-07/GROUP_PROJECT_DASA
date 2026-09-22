# NHẬT KÝ GỠ LỖI (DEBUG LOG)

*Nhóm em đã sử dụng AI để tạo ra form mẫu, sau đó chỉnh sửa lại theo đúng những gì nhóm chúng em thực hiện*

> **Lưu ý:** Mọi lỗi phát sinh trong quá trình phát triển đều được ghi lại tại đây.

| STT | Ngày | Người phát hiện | File/Module | Mô tả lỗi (Bug Description) | Nguyên nhân (Root Cause) | Cách khắc phục (Solution) | Trạng thái |
|:---:|:---:|:---|:---|:---|:---|:---|:---:|
| 1 | 18/09 | Hoàng | `HashTable.cpp` | Chương trình bị chậm bất thường khi thêm 100k vé | Hàm băm (Hash function) bị va chạm quá nhiều, dẫn đến danh sách liên kết trong mỗi bucket quá dài | Đổi hàm băm từ đơn giản sang dùng thuật toán FNV-1a, tăng kích thước bảng băm | ✅ Đã sửa |



## Bài học kinh nghiệm sau khi Debug
