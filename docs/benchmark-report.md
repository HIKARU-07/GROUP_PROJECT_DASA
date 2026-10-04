# Benchmark Report – Group Project DASA

## 1. Mục tiêu

Benchmark được thực hiện để kiểm chứng bằng thực nghiệm rằng các cấu trúc dữ liệu được chọn cho hai yêu cầu chính của hệ thống có hành vi phù hợp với phân tích độ phức tạp:

- **MC1 – Exact lookup:** tìm vé theo `bookingId` ở quy mô dữ liệu lớn.
- **MC2 – Priority retrieval/processing:** xử lý các yêu cầu đặt ghế theo thứ tự ưu tiên dựa trên `timestamp`, sau đó `requestId`.

Ngoài việc đo cấu trúc dữ liệu tự cài đặt, benchmark có thêm baseline đơn giản để làm đối chứng:

- MC1: **linear scan** và `std::unordered_map`.
- MC2: `std::priority_queue` và phương án **sort + sequential scan**.

Mục tiêu của benchmark không phải chứng minh implementation tự cài đặt nhanh hơn thư viện STL, mà là chứng minh lựa chọn cấu trúc dữ liệu phù hợp với workload và quy mô dữ liệu của bài toán.

## 2. Cấu trúc dữ liệu được đánh giá

### 2.1 MC1 – HashTable

Project sử dụng `HashTable<V>` với:

- `std::hash<string>` để ánh xạ khóa vào bucket.
- Mỗi bucket dùng `DoubleLinkedList<Entry<V>>` để xử lý collision.
- Khi load factor vượt `0.75`, bảng được resize lên gấp đôi và rehash các phần tử.
- Thao tác tra cứu đi vào đúng bucket rồi tìm khóa trong bucket.

Độ phức tạp kỳ vọng:

| Thao tác | Trung bình | Trường hợp xấu |
|---|---:|---:|
| `put` | O(1) amortized | O(n) khi resize/collision xấu |
| `get` / `find` | O(1) | O(n) |

Đối chứng **linear scan** có độ phức tạp O(n) cho mỗi lần tìm kiếm.

### 2.2 MC2 – PriorityQueue

Project sử dụng `PriorityQueue` tự cài đặt bằng **binary min-heap** trên mảng động. Ưu tiên được xác định theo:

1. `timestamp` nhỏ hơn → ưu tiên cao hơn.
2. Nếu cùng timestamp, `requestId` nhỏ hơn → ưu tiên cao hơn.

Độ phức tạp kỳ vọng:

| Thao tác | Độ phức tạp |
|---|---:|
| `top` | O(1) |
| `push` | O(log n) |
| `pop` | O(log n) |
| Xử lý n phần tử bằng push + pop | O(n log n) |

Phương án đối chứng `sort + sequential scan` cũng có tổng chi phí O(n log n), nhưng phù hợp hơn với trường hợp cần sắp xếp toàn bộ dữ liệu một lần thay vì liên tục thêm/xóa phần tử ưu tiên.

## 3. Phương pháp thực nghiệm

### 3.1 Dữ liệu

Benchmark tạo dữ liệu **deterministic** bằng các hàm sinh dữ liệu cố định, vì vậy các lần chạy có cùng kích thước sẽ có cùng tập khóa/request về mặt logic.

Các kích thước được dùng trong lần chạy báo cáo:

- **N = 10,000**
- **N = 100,000**

Hai mức này chênh nhau một bậc độ lớn, đáp ứng yêu cầu đánh giá ở quy mô đủ lớn để quan sát sự khác biệt giữa tuyến tính và cấu trúc dữ liệu phù hợp.

Với MC1, số truy vấn `Q = N`. Trong mỗi tập truy vấn:

- 4/5 truy vấn là tìm thấy khóa.
- 1/5 truy vấn là khóa không tồn tại.

Thời gian được đo bằng `std::chrono::steady_clock` và đơn vị là milliseconds. Kết quả tìm kiếm được cộng vào checksum để tránh việc phần công việc đo được bị tối ưu hóa bỏ đi.

### 3.2 Môi trường chạy benchmark

Lần chạy được thực hiện bằng:

- Compiler: **g++ 14.2.0**
- Standard: **C++17**
- Optimization: **-O2**
- OS/kernel: **Linux x86_64**
- Clock: `std::chrono::steady_clock`

> **Lưu ý:** số liệu bên dưới là số đo thực tế từ môi trường chạy benchmark này. Khi nộp/defense, nên chạy lại `benchmark.cpp` trên chính máy dùng để trình diễn và cập nhật bảng số liệu nếu thời gian thay đổi theo CPU/OS/compiler.

## 4. Kết quả MC1 – Exact Lookup

### 4.1 N = 10,000

| Implementation | Insert (ms) | Lookup (ms) |
|---|---:|---:|
| Custom `HashTable` | 2.304 | **0.204** |
| Linear scan | – | **136.924** |
| `std::unordered_map` | 0.786 | 0.257 |

Tại N = 10,000, lookup bằng `HashTable` nhanh hơn linear scan khoảng **671 lần** (`136.924 / 0.204`).

### 4.2 N = 100,000

| Implementation | Insert (ms) | Lookup (ms) |
|---|---:|---:|
| Custom `HashTable` | 41.792 | **7.101** |
| Linear scan | – | **13,558.826** |
| `std::unordered_map` | 7.548 | 4.522 |

Tại N = 100,000, lookup bằng `HashTable` nhanh hơn linear scan khoảng **1,909 lần** (`13,558.826 / 7.101`).

### 4.3 Nhận xét MC1

Khi N tăng từ 10,000 lên 100,000:

- Linear scan tăng từ **136.924 ms** lên **13,558.826 ms**, tức khoảng **99 lần**.
- Custom `HashTable` tăng từ **0.204 ms** lên **7.101 ms**, tức khoảng **34.8 lần**.
- Thời gian thực tế của hash table không tăng tuyến tính theo N trong hai điểm đo này, phù hợp với kỳ vọng lookup trung bình gần O(1), dù benchmark thực tế còn chịu ảnh hưởng của cache, collision, allocation và resize.

Kết quả quan trọng nhất là khoảng cách giữa hai chiến lược tăng rất mạnh khi quy mô dữ liệu tăng. Điều này cho thấy linear scan không phù hợp cho exact lookup ở quy mô lớn, trong khi hash table giữ được thời gian truy vấn thấp hơn đáng kể.

`std::unordered_map` nhanh hơn custom `HashTable` ở lookup trong lần chạy này. Đây là kết quả có thể kỳ vọng vì STL có implementation đã được tối ưu, nhưng nó không phủ nhận tính đúng đắn của lựa chọn Hash Table về mặt thuật toán.

## 5. Kết quả MC2 – Priority Processing

### 5.1 N = 10,000

| Implementation | Push (ms) | Pop (ms) | Total (ms) |
|---|---:|---:|---:|
| Custom `PriorityQueue` | 5.629 | 28.330 | **33.959** |
| `std::priority_queue` | 2.983 | 12.732 | **15.715** |
| Sort + sequential scan | – | – | **14.152** |

### 5.2 N = 100,000

| Implementation | Push (ms) | Pop (ms) | Total (ms) |
|---|---:|---:|---:|
| Custom `PriorityQueue` | 46.609 | 390.077 | **436.686** |
| `std::priority_queue` | 35.501 | 172.929 | **208.430** |
| Sort + sequential scan | – | – | **180.656** |

### 5.3 Nhận xét MC2

Khi N tăng từ 10,000 lên 100,000:

- Custom PriorityQueue tăng từ **33.959 ms** lên **436.686 ms**, khoảng **12.9 lần**.
- `std::priority_queue` tăng từ **15.715 ms** lên **208.430 ms**, khoảng **13.3 lần**.
- Sort + sequential scan tăng từ **14.152 ms** lên **180.656 ms**, khoảng **12.8 lần**.

Mức tăng khoảng 13 lần khi N tăng 10 lần phù hợp với xu hướng **O(n log n)**: chi phí không tăng đúng 10 lần như thuật toán tuyến tính, nhưng cũng không tăng tới 100 lần như O(n²).

Trong workload benchmark này, sort toàn bộ dữ liệu một lần có thời gian tổng thấp hơn custom heap. Tuy nhiên, đây là hai chiến lược có workload khác nhau:

- **PriorityQueue:** phù hợp khi request được thêm dần và cần lấy phần tử ưu tiên nhất nhiều lần.
- **Sort + scan:** phù hợp khi toàn bộ dữ liệu đã có sẵn và chỉ cần sắp xếp một lần rồi duyệt theo thứ tự.

Do `BookingService` của project sử dụng `addRequest()` để đưa request vào queue và `process()` lấy lần lượt `top()` rồi `pop()`, PriorityQueue phù hợp trực tiếp với mô hình xử lý của service.

## 6. Kiểm tra tính đúng của kết quả

Benchmark sử dụng checksum để kiểm tra rằng các implementation đang xử lý cùng một workload.

### MC1

Checksum ở cả ba cách lookup đều khớp:

- N = 10,000: `1,240,056,000`
- N = 100,000: `124,000,560,000`

### MC2

Checksum của cả ba phương án đều khớp:

- N = 10,000: `90,000`
- N = 100,000: `900,000`

Vì vậy benchmark không chỉ đo thời gian mà còn kiểm tra rằng các phương án đang thực hiện cùng một công việc logic.

## 7. Đối chiếu với phân tích độ phức tạp

| Yêu cầu | Cách tiếp cận | Độ phức tạp kỳ vọng | Kết quả thực nghiệm |
|---|---|---:|---|
| MC1 exact lookup | Linear scan | O(n) / query | Tăng gần tỷ lệ với kích thước dữ liệu |
| MC1 exact lookup | Custom HashTable | O(1) trung bình / query | Tăng chậm hơn linear scan rất nhiều |
| MC2 priority processing | Binary heap | O(n log n) tổng | Tăng khoảng 13x khi N tăng 10x |
| MC2 batch sorting | Sort | O(n log n) tổng | Tăng khoảng 12.8x khi N tăng 10x |

Các số đo không được dùng để khẳng định một hằng số tuyệt đối cho Big-O. Mục tiêu của thực nghiệm là kiểm chứng **xu hướng tăng trưởng** khi N thay đổi.

## 8. Kết luận

### MC1

`HashTable` là lựa chọn phù hợp cho exact lookup theo `bookingId`. So với linear scan, khoảng cách hiệu năng tăng rất lớn khi quy mô dữ liệu tăng. Ở N = 100,000, lookup của custom HashTable chỉ mất **7.101 ms**, trong khi linear scan mất **13,558.826 ms** trong cùng workload.

### MC2

`PriorityQueue` dựa trên binary heap phù hợp với nghiệp vụ xử lý booking request theo thứ tự ưu tiên. Các thao tác `push` và `pop` có độ phức tạp O(log n), do đó toàn bộ quá trình xử lý n request có xu hướng O(n log n). Kết quả benchmark phù hợp với xu hướng này.

### Đánh giá implementation tự cài đặt

Benchmark cũng cho thấy custom implementations hiện tại chậm hơn các implementation STL trong môi trường thử nghiệm:

- Custom HashTable chậm hơn `std::unordered_map` ở lookup tại N = 100,000.
- Custom PriorityQueue chậm hơn `std::priority_queue` ở cả push và pop.

Điều này là chấp nhận được đối với mục tiêu của đồ án DSA: nhóm cần **tự cài đặt và chứng minh lựa chọn cấu trúc dữ liệu**, không nhất thiết phải vượt qua thư viện STL đã được tối ưu.

## 9. Hạn chế của benchmark

1. Thời gian phụ thuộc vào CPU, RAM, compiler, optimization level và trạng thái hệ thống.
2. Mỗi cấu hình trong lần chạy này được đo một lần; chưa thực hiện nhiều repetition rồi lấy median/mean.
3. Dữ liệu benchmark là dữ liệu sinh tự động, chưa phải toàn bộ dữ liệu production thực tế.
4. Custom HashTable sử dụng `std::hash<string>`, nên benchmark đánh giá phần cấu trúc bucket/collision/resize do nhóm cài đặt, nhưng không phải tự cài đặt thuật toán hash.
5. Linear scan tại N = 100,000 đã mất khoảng 13.6 giây; vì vậy không tiếp tục chạy linear scan ở N = 250,000 trong cùng lần đo để tránh tạo workload O(n²) quá lớn. Hai điểm 10,000 và 100,000 đã đủ để kiểm chứng yêu cầu tăng quy mô một bậc độ lớn.

## 10. Cách chạy lại benchmark

Từ thư mục project:

```bash
g++ -std=c++17 -O2 benchmark/benchmark.cpp -o benchmark
./benchmark 10000 100000
```

Trên Windows với MinGW:

```bash
g++ -std=c++17 -O2 benchmark/benchmark.cpp -o benchmark.exe
benchmark.exe 10000 100000
```

Khi defense, nên giữ lại output terminal của lần chạy thực tế và giải thích ba ý chính:

1. **MC1:** HashTable giảm mạnh thời gian exact lookup so với linear scan.
2. **MC2:** Binary heap cho phép lấy request ưu tiên với `top = O(1)`, `push/pop = O(log n)`.
3. **Số liệu thực nghiệm phù hợp với xu hướng Big-O**, nhưng không dùng benchmark để khẳng định Big-O một cách tuyệt đối.
