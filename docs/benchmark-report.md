# Benchmark Report

## 1. Tổng quan

Benchmark được xây dựng để đánh giá hiệu năng của các cấu trúc dữ liệu
được sử dụng trong project.

Hai thành phần chính được kiểm thử:

-   **MC1 -- HashTable:** HashTable tự cài đặt.
-   **MC2 -- PriorityQueue:** PriorityQueue tự cài đặt bằng Min-Heap.

Các cấu trúc tự cài đặt được so sánh với các cấu trúc tương ứng của STL
nhằm tạo một baseline để đánh giá hiệu năng.

------------------------------------------------------------------------

## 2. Mục tiêu

Benchmark có các mục tiêu chính:

1.  Đo thời gian thực thi của các thao tác quan trọng.
2.  So sánh implementation tự cài đặt với STL.
3.  Kiểm tra sự phù hợp giữa hiệu năng thực tế và độ phức tạp lý thuyết.
4.  Kiểm tra tính đúng của kết quả thông qua checksum.
5.  Đánh giá khả năng mở rộng khi số lượng dữ liệu tăng.

------------------------------------------------------------------------

## 3. Môi trường thử nghiệm

Benchmark được viết bằng **C++17** và sử dụng
`std::chrono::steady_clock` để đo thời gian.

Khuyến nghị biên dịch ở chế độ tối ưu hóa:

``` bash
g++ -std=c++17 -O2
```

Các yếu tố như CPU, RAM, compiler, hệ điều hành và chương trình chạy nền
có thể ảnh hưởng đến thời gian benchmark.

Vì vậy, các phương án phải được chạy trong cùng một môi trường để kết
quả có tính so sánh.

------------------------------------------------------------------------

## 4. Dữ liệu kiểm thử

Benchmark hỗ trợ nhiều kích thước dữ liệu để quan sát xu hướng khi quy
mô input tăng.

Các kích thước mặc định:

``` text
N = 10,000
N = 50,000
N = 100,000
N = 250,000
```

Có thể truyền kích thước khác khi chạy:

``` bash
benchmark.exe 10000 50000 100000
```

Dữ liệu được sinh tự động để đảm bảo các phương án nhận cùng một
workload.

------------------------------------------------------------------------

# 5. MC1 -- HashTable Benchmark

## 5.1. Các phương án

MC1 so sánh:

### Custom HashTable

HashTable do nhóm tự cài đặt.

Đặc điểm:

-   Hash function dựa trên `std::hash`.
-   Collision được xử lý bằng bucket.
-   Bucket sử dụng linked list.
-   Resize khi load factor vượt ngưỡng quy định.

### STL `std::unordered_map`

`std::unordered_map` được sử dụng làm baseline.

Đây là hash table được cung cấp bởi thư viện chuẩn C++.

------------------------------------------------------------------------

## 5.2. Các thao tác được đo

### Insert

Thêm `N` phần tử vào HashTable.

``` text
Insert N elements
```

Mục tiêu là đo chi phí xây dựng bảng khi số lượng phần tử tăng.

### Lookup

Thực hiện nhiều truy vấn tìm kiếm trên bảng.

Workload bao gồm cả:

-   Key tồn tại.
-   Key không tồn tại.

Điều này giúp benchmark phản ánh gần hơn trường hợp sử dụng thực tế.

------------------------------------------------------------------------

## 5.3. Độ phức tạp lý thuyết

  Operation             Custom HashTable   `std::unordered_map`
  ------------------- ------------------ ----------------------
  Insert trung bình                 O(1)                   O(1)
  Lookup trung bình                 O(1)                   O(1)
  Worst case                        O(n)                   O(n)

Về mặt lý thuyết, hai phương án có cùng độ phức tạp trung bình.

Tuy nhiên, thời gian thực tế có thể khác nhau do cách triển khai, cấp
phát bộ nhớ, collision và cache locality.

------------------------------------------------------------------------

# 6. MC2 -- PriorityQueue Benchmark

## 6.1. Các phương án

MC2 so sánh ba cách xử lý priority queue:

1.  **Custom PriorityQueue**
    -   Min-Heap tự cài đặt.
2.  **`std::priority_queue`**
    -   Priority queue có sẵn trong STL.
3.  **Sort + Sequential Scan**
    -   Sắp xếp dữ liệu rồi xử lý tuần tự.

------------------------------------------------------------------------

## 6.2. Tiêu chí ưu tiên

Các phương án sử dụng cùng tiêu chí so sánh `BookingRequest`:

1.  Timestamp nhỏ hơn được ưu tiên trước.
2.  Nếu timestamp bằng nhau, `requestId` nhỏ hơn được ưu tiên trước.

Việc sử dụng cùng comparator đảm bảo các phương án xử lý cùng một thứ tự
ưu tiên.

------------------------------------------------------------------------

## 6.3. Các thao tác được đo

### Push

Thêm request vào PriorityQueue.

Với Min-Heap:

``` text
Push = O(log n)
```

### Pop

Lấy và xóa request có độ ưu tiên cao nhất.

``` text
Pop = O(log n)
```

### Top

Truy cập request có độ ưu tiên cao nhất mà không xóa.

``` text
Top = O(1)
```

------------------------------------------------------------------------

## 6.4. Độ phức tạp

  Operation     Custom Heap   `std::priority_queue`
  ----------- ------------- -----------------------
  Push             O(log n)                O(log n)
  Top                  O(1)                    O(1)
  Pop              O(log n)                O(log n)
  Space                O(n)                    O(n)

Với phương án sort:

``` text
Sorting = O(n log n)
```

Do đó sort có thể phù hợp khi cần sắp xếp toàn bộ dữ liệu một lần, nhưng
không phù hợp bằng Heap nếu workload liên tục có `push` và `pop`.

------------------------------------------------------------------------

# 7. Phương pháp đo

Thời gian được đo bằng:

``` cpp
std::chrono::steady_clock
```

Cấu trúc đo:

``` text
Start timer
    ↓
Execute operation
    ↓
Stop timer
    ↓
Calculate elapsed time
```

Việc sử dụng `steady_clock` giúp tránh ảnh hưởng của thay đổi system
clock trong quá trình đo.

Các thao tác chuẩn bị dữ liệu không được tính vào thời gian của thao tác
đang benchmark khi điều đó có thể làm sai lệch kết quả.

------------------------------------------------------------------------

# 8. Kiểm tra tính đúng

Benchmark không chỉ đo thời gian mà còn kiểm tra kết quả.

## MC1

Kết quả lookup của Custom HashTable được so sánh với:

``` text
std::unordered_map
```

## MC2

Kết quả xử lý được so sánh giữa:

``` text
Custom PriorityQueue
std::priority_queue
Sort + Scan
```

Checksum được sử dụng để phát hiện trường hợp hai implementation có thời
gian chạy nhưng tạo ra kết quả khác nhau.

Nếu checksum không giống nhau, benchmark sẽ cảnh báo để tránh đưa ra kết
luận hiệu năng dựa trên kết quả sai.

------------------------------------------------------------------------

# 9. Kết quả benchmark

Kết quả cần được ghi lại theo từng kích thước dữ liệu.

Mẫu bảng cho MC1:

          N   Custom Insert   STL Insert   Custom Lookup   STL Lookup
  --------- --------------- ------------ --------------- ------------
     10,000             ...          ...             ...          ...
     50,000             ...          ...             ...          ...
    100,000             ...          ...             ...          ...
    250,000             ...          ...             ...          ...

Mẫu bảng cho MC2:

          N   Custom Push   STL Push   Custom Pop   STL Pop   Sort + Scan
  --------- ------------- ---------- ------------ --------- -------------
     10,000           ...        ...          ...       ...           ...
     50,000           ...        ...          ...       ...           ...
    100,000           ...        ...          ...       ...           ...
    250,000           ...        ...          ...       ...           ...

> Các giá trị `...` cần được thay bằng số liệu thực tế thu được khi chạy
> benchmark trên máy của nhóm.

------------------------------------------------------------------------

# 10. Cách phân tích kết quả

Sau khi chạy benchmark, cần tập trung vào ba vấn đề.

## 10.1. Scaling theo N

So sánh thời gian khi:

``` text
10,000 → 50,000 → 100,000 → 250,000
```

Nếu thời gian tăng phù hợp với độ phức tạp lý thuyết thì implementation
có scaling hợp lý.

------------------------------------------------------------------------

## 10.2. Custom vs STL

So sánh:

``` text
Custom HashTable
        vs
std::unordered_map
```

và:

``` text
Custom PriorityQueue
        vs
std::priority_queue
```

STL thường có lợi thế về implementation và tối ưu hóa.

Do đó Custom implementation có thể chậm hơn nhưng vẫn có cùng độ phức
tạp Big-O.

------------------------------------------------------------------------

## 10.3. Heap vs Sort

Nếu workload có nhiều thao tác:

``` text
Push
Pop
Push
Pop
...
```

thì Heap phù hợp vì mỗi thao tác chỉ cần:

``` text
O(log n)
```

Trong khi việc duy trì một danh sách được sort lại có thể tốn:

``` text
O(n log n)
```

cho mỗi lần sắp xếp lại.

------------------------------------------------------------------------

# 11. Kết luận

Benchmark được thiết kế để đánh giá hai lựa chọn cấu trúc dữ liệu chính
của project.

### MC1

HashTable tự cài đặt có độ phức tạp trung bình:

``` text
Insert  → O(1)
Lookup  → O(1)
```

Do đó phù hợp với các thao tác tìm kiếm booking/request theo key.

### MC2

PriorityQueue sử dụng Min-Heap có:

``` text
Push → O(log n)
Pop  → O(log n)
Top  → O(1)
```

Đây là lựa chọn phù hợp cho hệ thống cần liên tục thêm request và lấy
request có độ ưu tiên cao nhất.

### Tổng kết

Benchmark cho phép nhóm:

-   Kiểm chứng độ phức tạp lý thuyết bằng dữ liệu thực tế.
-   So sánh implementation tự cài đặt với STL.
-   Kiểm tra khả năng mở rộng khi dữ liệu tăng.
-   Xác nhận tính đúng của kết quả thông qua checksum.

**Benchmark Report tập trung vào phương pháp đo và số liệu. Phần đánh
giá ưu/nhược điểm và giải thích nguyên nhân của kết quả được trình bày
riêng trong `benchmark-review.md`.**
