# Benchmark Review

## 1. Mục đích

Benchmark dùng để đánh giá hiệu năng của hai cấu trúc dữ liệu chính
trong project:

-   **MC1:** `HashTable` tự cài đặt.
-   **MC2:** `PriorityQueue` tự cài đặt bằng Min-Heap.

Các cấu trúc tự cài đặt được so sánh với cấu trúc tương ứng của STL để
có mốc tham chiếu.

> Lưu ý: số liệu benchmark phụ thuộc máy tính, compiler, hệ điều hành và
> mức tối ưu hóa. Vì vậy nên dùng kết quả để so sánh tương đối giữa các
> phương án trên cùng một môi trường.

------------------------------------------------------------------------

## 2. Môi trường và cách chạy

Benchmark sử dụng:

-   C++17
-   `std::chrono::steady_clock`
-   Khuyến nghị biên dịch ở `Release` hoặc `-O2`
-   Dữ liệu được sinh tự động và có tính xác định.
-   Checksum được sử dụng để kiểm tra kết quả và tránh trường hợp phép
    đo không thực sự thực hiện công việc cần đo.

Chạy mặc định:

``` bash
benchmark.exe
```

Kích thước dữ liệu mặc định:

``` text
10,000
50,000
100,000
250,000
```

Có thể truyền kích thước tùy ý:

``` bash
benchmark.exe 10000 50000 100000
```

------------------------------------------------------------------------

## 3. Review MC1 -- HashTable

### Phương án benchmark

So sánh:

1.  `HashTable<int>` tự cài đặt của project.
2.  `std::unordered_map<string, int>` của STL.

Benchmark đo hai thao tác:

-   **Insert:** thêm `N` booking ID.
-   **Lookup:** thực hiện `N` truy vấn, trong đó khoảng 80% truy vấn
    thành công và 20% không tồn tại.

### Độ phức tạp

  Thao tác              HashTable   `std::unordered_map`
  ------------------- ----------- ----------------------
  Insert trung bình          O(1)                   O(1)
  Lookup trung bình          O(1)                   O(1)
  Trường hợp xấu             O(n)                   O(n)

`HashTable` của project sử dụng:

-   `std::hash<string>` để tạo hash.
-   Chia dữ liệu thành các bucket.
-   Mỗi bucket sử dụng `DoubleLinkedList`.
-   Khi load factor vượt `0.75`, bảng được resize lên gấp đôi.

### Nhận xét

Ưu điểm của `HashTable` tự cài đặt:

-   Đáp ứng đúng yêu cầu tự xây dựng cấu trúc dữ liệu.
-   Cho phép nhóm kiểm soát cách xử lý collision.
-   Có cơ chế resize khi bảng trở nên quá đầy.

Hạn chế:

-   Mỗi bucket sử dụng linked list nên lookup trong bucket vẫn phải
    duyệt tuyến tính.
-   Việc cấp phát và thao tác trên linked list có thể tạo overhead.
-   `std::unordered_map` được thư viện chuẩn tối ưu hóa mạnh nên thường
    có lợi thế về hiệu năng thực tế.

**Kết luận MC1:** `HashTable` tự cài đặt phù hợp với mục tiêu học thuật
và yêu cầu của project. `std::unordered_map` phù hợp hơn nếu mục tiêu
chính là hiệu năng và độ ổn định trong ứng dụng thực tế.

------------------------------------------------------------------------

## 4. Review MC2 -- PriorityQueue

### Phương án benchmark

So sánh ba cách:

1.  `PriorityQueue` tự cài đặt bằng Min-Heap.
2.  `std::priority_queue`.
3.  `sort + sequential scan`.

Tất cả các phương án sử dụng cùng tập `BookingRequest` và cùng tiêu chí
ưu tiên:

1.  Timestamp nhỏ hơn được ưu tiên trước.
2.  Nếu timestamp bằng nhau, `requestId` nhỏ hơn được ưu tiên trước.

### Độ phức tạp

  Thao tác     Custom PriorityQueue   `std::priority_queue`
  ---------- ---------------------- -----------------------
  Push                     O(log n)                O(log n)
  Top                          O(1)                    O(1)
  Pop                      O(log n)                O(log n)
  Bộ nhớ                       O(n)                    O(n)

Với phương án `sort`:

``` text
Sort toàn bộ N phần tử: O(n log n)
```

Sau khi sort, lấy phần tử theo thứ tự có thể thực hiện tuần tự với chi
phí O(1) cho mỗi phần tử.

### Vì sao Heap phù hợp với MC2?

MC2 liên tục có các yêu cầu:

``` text
push(request)
top()
pop()
```

Do đó không cần sắp xếp lại toàn bộ danh sách sau mỗi lần thêm request.

Min-Heap chỉ cần điều chỉnh một đường từ node mới lên root khi `push`,
hoặc từ root xuống khi `pop`.

Vì vậy:

``` text
Push  -> O(log n)
Pop   -> O(log n)
Top   -> O(1)
```

Đây là lý do `PriorityQueue` bằng Heap phù hợp hơn việc duy trì một mảng
luôn được sắp xếp.

------------------------------------------------------------------------

## 5. Review về STL

STL được sử dụng làm **baseline/reference**, không phải để thay thế cấu
trúc dữ liệu mà nhóm đã tự cài đặt.

Ví dụ:

``` cpp
HashTable<int>
```

được so sánh với:

``` cpp
std::unordered_map<string, int>
```

và:

``` cpp
PriorityQueue
```

được so sánh với:

``` cpp
std::priority_queue
```

Nếu custom structure chậm hơn STL thì điều đó không có nghĩa thuật toán
sai. STL thường đã được tối ưu về:

-   Cấp phát bộ nhớ.
-   Container nội bộ.
-   Compiler optimization.
-   Copy/move object.
-   Implementation details.

Benchmark chủ yếu giúp đánh giá **xu hướng hiệu năng và chi phí của cách
cài đặt hiện tại**.

------------------------------------------------------------------------

## 6. Kiểm tra tính đúng của benchmark

Benchmark không chỉ đo thời gian.

Sau khi thực hiện các thao tác, chương trình tính `checksum`.

Ví dụ MC1:

``` text
Custom HashTable checksum
vs
std::unordered_map checksum
```

MC2:

``` text
Custom PriorityQueue checksum
vs
std::priority_queue checksum
vs
sort
```

Nếu checksum giống nhau, các phương án đã xử lý cùng một lượng dữ liệu
đầu ra theo cách tương đương.

Nếu checksum khác nhau, benchmark sẽ cảnh báo:

``` text
WARNING: MC1 checksums differ!
```

hoặc:

``` text
WARNING: MC2 checksums differ!
```

Điều này giúp phát hiện lỗi logic thay vì chỉ dựa vào thời gian chạy.

------------------------------------------------------------------------

## 7. Những yếu tố ảnh hưởng kết quả

Kết quả benchmark có thể thay đổi do:

-   CPU.
-   RAM.
-   Compiler.
-   Cờ tối ưu hóa (`-O0`, `-O2`, `-O3`).
-   Hệ điều hành.
-   Chương trình khác đang chạy nền.
-   Kích thước dữ liệu.
-   Cách cấp phát bộ nhớ.
-   Cache của CPU.

Do đó không nên kết luận rằng một phương án luôn nhanh hơn chỉ từ một
lần chạy.

Nên chạy nhiều lần với cùng môi trường và so sánh xu hướng.

------------------------------------------------------------------------

## 8. Đánh giá tổng thể

  Tiêu chí                    Custom               STL
  --------------------------- -------------------- --------------------
  Mục tiêu học thuật          **Tốt**              Trung bình
  Kiểm soát cách triển khai   **Cao**              Thấp
  Hiệu năng thực tế           Có thể thấp hơn      **Thường tốt hơn**
  Dễ sử dụng                  Trung bình           **Cao**
  Phù hợp yêu cầu project     **Có**               Dùng làm baseline
  Khả năng mở rộng code       Tùy implementation   **Tốt**

### Kết luận

Các cấu trúc dữ liệu tự cài đặt của project phù hợp với mục tiêu chính
là **áp dụng kiến thức Data Structures & Algorithms vào bài toán thực
tế**.

-   `HashTable` phù hợp với MC1 vì cung cấp lookup trung bình **O(1)**.
-   `PriorityQueue` bằng Min-Heap phù hợp với MC2 vì hỗ trợ `push/pop`
    **O(log n)** và lấy phần tử ưu tiên nhất **O(1)**.
-   STL được dùng làm baseline để đánh giá hiệu năng, không thay thế
    phần cài đặt của nhóm.
-   Benchmark có checksum giúp kiểm tra rằng các phương án đang xử lý dữ
    liệu tương đương.

**Đánh giá cuối:** lựa chọn cấu trúc dữ liệu của project là hợp lý về
mặt thuật toán. Phần khác biệt hiệu năng chủ yếu đến từ chi tiết triển
khai và overhead của cấu trúc dữ liệu tự cài đặt.
