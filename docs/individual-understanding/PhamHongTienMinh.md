## 1. Vai trò cụ thể

- **Thiết kế cấu trúc dữ liệu:** Xây dựng `Stack` bằng Linked List, quản lý `push`, `pop`, `peek`, `empty` và giới hạn tối đa 10 phần tử.
- **Thiết kế dữ liệu Undo:** Xây dựng `UndoAction` để lưu thông tin thao tác và thời gian thực hiện.
- **Xây dựng chức năng Undo:** Phát triển `UndoService` để đọc dữ liệu từ file, đưa thao tác vào Stack và xử lý Undo theo nguyên tắc LIFO.
- **Xử lý thời gian:** Xây dựng cơ chế chuyển timestamp sang `time_t` và kiểm tra thao tác có vượt quá 15 phút hay không.
- **Debug và kiểm thử:** Kiểm tra các trường hợp Stack rỗng, timestamp không hợp lệ, Undo thất bại và đảm bảo dữ liệu không bị xóa khi Undo không thành công.

## 2. Gặp khó khăn gì?

- **Logic `peek()` và `pop()`:** Ban đầu gặp lỗi khi Undo thất bại nhưng phần tử vẫn bị xóa khỏi Stack, sau đó sửa bằng cách kiểm tra bằng `peek()` trước rồi mới `pop()`.
- **Xử lý timestamp:** Gặp khó khăn trong việc chuyển chuỗi thời gian `YYYY-MM-DD HH:MM` sang dạng có thể tính toán và xác định chính xác khoảng cách 15 phút.
- **Quản lý Linked List:** Phải đảm bảo `topNode`, `next`, `count` được cập nhật chính xác khi thêm, xóa và giải phóng Node.
- **Xử lý dữ liệu đầu vào:** Phải kiểm tra trường hợp file không mở được, dữ liệu thiếu dấu `|`, timestamp không hợp lệ hoặc operation không đúng.

## 3. Học được những gì?

- Hiểu rõ hơn **cách Stack hoạt động theo nguyên tắc LIFO** và cách tự triển khai Stack bằng Linked List.
- Biết cách **tách dữ liệu, cấu trúc dữ liệu và xử lý nghiệp vụ** thành `UndoAction`, `Stack` và `UndoService`.
- Hiểu cách sử dụng `get_time()`, `mktime()` và `difftime()` để xử lý và so sánh thời gian trong C++.
- Học được tầm quan trọng của **debug và xử lý các trường hợp ngoại lệ**, đặc biệt là phải đảm bảo dữ liệu không bị thay đổi khi một thao tác thất bại.
- Hiểu rằng code không chỉ cần chạy đúng mà còn phải **dễ đọc, dễ kiểm tra và hạn chế lỗi khi mở rộng**.