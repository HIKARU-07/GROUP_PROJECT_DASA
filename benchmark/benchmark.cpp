#include "../src/models/BookingRequest.h"
#include "../src/structures/HashTable.h"
#include "../src/structures/PriorityQueue.h"

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using Clock = chrono::steady_clock;

// ------------------------------------------------------------
// Benchmark utilities
// ------------------------------------------------------------

template <typename Func>
double measureMs(Func&& func) {
    const auto start = Clock::now();
    func();
    const auto finish = Clock::now();
    return chrono::duration<double, milli>(finish - start).count();
}

string makeBookingId(int i) {
    // Deterministic ID with the same general style as the project data:
    // VN-CINEMA- + exactly 5 digits + 1 uppercase letter.
    const int number = i % 100000;
    const char suffix = static_cast<char>('A' + (i / 100000) % 26);

    ostringstream out;
    out << "VN-CINEMA-" << setw(5) << setfill('0') << number << suffix;
    return out.str();
}

BookingRequest makeRequest(int i) {
    // Reverse-ish timestamps create a non-trivial heap workload.
    int minute = (i * 37) % 1000000;
    int day = minute / (24 * 60);
    int hour = (minute / 60) % 24;
    int min = minute % 60;

    char buffer[32];
    snprintf(
        buffer,
        sizeof(buffer),
        "2026-09-%02d %02d:%02d:00",
        (day % 28) + 1,
        hour,
        min
    );

    string requestId = "REQ-" + string(5 - to_string(i % 100000).size(), '0')
                     + to_string(i % 100000);

    return BookingRequest(
        requestId,
        "SHOWTIME-001",
        "A01",
        "CUS-" + to_string(i),
        buffer,
        "PENDING"
    );
}

// A value that is cheap to store and makes lookup results observable.
int valueFor(int i) {
    return i * 31 + 7;
}

// ------------------------------------------------------------
// MC1 - Exact lookup: custom HashTable vs std::unordered_map
// ------------------------------------------------------------

struct HashBenchmarkResult {
    double customInsertMs{};
    double customLookupMs{};
    double stlInsertMs{};
    double stlLookupMs{};
    long long customChecksum{};
    long long stlChecksum{};
};

HashBenchmarkResult benchmarkHashTable(int n, int q) {
    vector<string> keys;
    keys.reserve(n);
    for (int i = 0; i < n; ++i) {
        keys.push_back(makeBookingId(i));
    }

    vector<string> queries;
    queries.reserve(q);
    for (int i = 0; i < q; ++i) {
        // 4/5 successful lookups, 1/5 misses.
        if (i % 5 == 0) {
            queries.push_back("VN-CINEMA-99999-Z" + to_string(i));
        } else {
            queries.push_back(keys[(i * 7919LL) % n]);
        }
    }

    HashBenchmarkResult result;

    HashTable<int> custom(max(8, n / 2));
    result.customInsertMs = measureMs([&] {
        for (int i = 0; i < n; ++i) {
            custom.put(keys[i], valueFor(i));
        }
    });

    result.customLookupMs = measureMs([&] {
        long long checksum = 0;
        for (const string& key : queries) {
            int value = 0;
            if (custom.get(key, value)) {
                checksum += value;
            }
        }
        result.customChecksum = checksum;
    });

    unordered_map<string, int> stl;
    stl.reserve(static_cast<size_t>(n * 1.4) + 1);

    result.stlInsertMs = measureMs([&] {
        for (int i = 0; i < n; ++i) {
            stl.emplace(keys[i], valueFor(i));
        }
    });

    result.stlLookupMs = measureMs([&] {
        long long checksum = 0;
        for (const string& key : queries) {
            auto it = stl.find(key);
            if (it != stl.end()) {
                checksum += it->second;
            }
        }
        result.stlChecksum = checksum;
    });

    return result;
}

// ------------------------------------------------------------
// MC2 - Priority processing: custom PriorityQueue vs STL heap
// ------------------------------------------------------------

struct PriorityBenchmarkResult {
    double customPushMs{};
    double customPopMs{};
    double stlPushMs{};
    double stlPopMs{};
    long long customChecksum{};
    long long stlChecksum{};
};

struct RequestCompare {
    bool operator()(const BookingRequest& a, const BookingRequest& b) const {
        if (a.getTimestamp() != b.getTimestamp()) {
            // std::priority_queue is a max-heap, so invert the comparison
            // to obtain the same min-heap order as PriorityQueue.
            return a.getTimestamp() > b.getTimestamp();
        }
        return a.getRequestId() > b.getRequestId();
    }
};

PriorityBenchmarkResult benchmarkPriorityQueue(int n) {
    vector<BookingRequest> requests;
    requests.reserve(n);
    for (int i = 0; i < n; ++i) {
        requests.push_back(makeRequest(i));
    }

    PriorityBenchmarkResult result;

    PriorityQueue custom(16);
    result.customPushMs = measureMs([&] {
        for (const BookingRequest& request : requests) {
            custom.push(request);
        }
    });

    result.customPopMs = measureMs([&] {
        long long checksum = 0;
        while (!custom.empty()) {
            BookingRequest request = custom.top();
            checksum += request.getRequestId().size();
            custom.pop();
        }
        result.customChecksum = checksum;
    });

    priority_queue<BookingRequest, vector<BookingRequest>, RequestCompare> stl;
    result.stlPushMs = measureMs([&] {
        for (const BookingRequest& request : requests) {
            stl.push(request);
        }
    });

    result.stlPopMs = measureMs([&] {
        long long checksum = 0;
        while (!stl.empty()) {
            BookingRequest request = stl.top();
            checksum += request.getRequestId().size();
            stl.pop();
        }
        result.stlChecksum = checksum;
    });

    return result;
}

// ------------------------------------------------------------
// Alternative MC2 strategy: sort all requests first.
// This is included to demonstrate the algorithmic trade-off:
// heap = O(n log n) total, sort = O(n log n) total, but with
// different workloads and operation costs.
// ------------------------------------------------------------

double benchmarkSortAll(int n, long long& checksum) {
    vector<BookingRequest> requests;
    requests.reserve(n);
    for (int i = 0; i < n; ++i) {
        requests.push_back(makeRequest(i));
    }

    const double ms = measureMs([&] {
        sort(requests.begin(), requests.end(), [](const BookingRequest& a,
                                                  const BookingRequest& b) {
            if (a.getTimestamp() != b.getTimestamp()) {
                return a.getTimestamp() < b.getTimestamp();
            }
            return a.getRequestId() < b.getRequestId();
        });

        checksum = 0;
        for (const BookingRequest& request : requests) {
            checksum += request.getRequestId().size();
        }
    });

    return ms;
}

// ------------------------------------------------------------
// Output
// ------------------------------------------------------------

void printSeparator() {
    cout << string(112, '-') << '\n';
}

void printHashResult(int n, int q, const HashBenchmarkResult& r) {
    cout << "\nMC1 - HASH TABLE (N=" << n << ", Q=" << q << ")\n";
    printSeparator();
    cout << left
         << setw(28) << "Implementation"
         << right
         << setw(16) << "Insert (ms)"
         << setw(16) << "Lookup (ms)"
         << setw(20) << "Checksum" << '\n';
    printSeparator();

    cout << left << setw(28) << "Custom HashTable"
         << right << setw(16) << fixed << setprecision(3) << r.customInsertMs
         << setw(16) << r.customLookupMs
         << setw(20) << r.customChecksum << '\n';

    cout << left << setw(28) << "std::unordered_map"
         << right << setw(16) << r.stlInsertMs
         << setw(16) << r.stlLookupMs
         << setw(20) << r.stlChecksum << '\n';
    printSeparator();

    if (r.customChecksum != r.stlChecksum) {
        cerr << "WARNING: MC1 checksums differ!\n";
    }
}

void printPriorityResult(int n, const PriorityBenchmarkResult& r,
                         double sortMs, long long sortChecksum) {
    cout << "\nMC2 - PRIORITY QUEUE (N=" << n << ")\n";
    printSeparator();
    cout << left
         << setw(30) << "Implementation"
         << right
         << setw(16) << "Push (ms)"
         << setw(16) << "Pop (ms)"
         << setw(16) << "Total (ms)"
         << setw(18) << "Checksum" << '\n';
    printSeparator();

    cout << left << setw(30) << "Custom PriorityQueue"
         << right << setw(16) << fixed << setprecision(3) << r.customPushMs
         << setw(16) << r.customPopMs
         << setw(16) << r.customPushMs + r.customPopMs
         << setw(18) << r.customChecksum << '\n';

    cout << left << setw(30) << "std::priority_queue"
         << right << setw(16) << r.stlPushMs
         << setw(16) << r.stlPopMs
         << setw(16) << r.stlPushMs + r.stlPopMs
         << setw(18) << r.stlChecksum << '\n';

    cout << left << setw(30) << "sort + sequential scan"
         << right << setw(16) << "-"
         << setw(16) << "-"
         << setw(16) << sortMs
         << setw(18) << sortChecksum << '\n';
    printSeparator();

    if (r.customChecksum != r.stlChecksum ||
        r.customChecksum != sortChecksum) {
        cerr << "WARNING: MC2 checksums differ!\n";
    }
}

vector<int> parseSizes(int argc, char** argv) {
    if (argc <= 1) {
        return {10000, 50000, 100000, 250000};
    }

    vector<int> sizes;
    for (int i = 1; i < argc; ++i) {
        int n = atoi(argv[i]);
        if (n > 0) {
            sizes.push_back(n);
        }
    }

    if (sizes.empty()) {
        sizes = {10000, 50000, 100000, 250000};
    }
    return sizes;
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const vector<int> sizes = parseSizes(argc, argv);

    cout << "==============================================================\n";
    cout << " GROUP PROJECT DASA - PERFORMANCE BENCHMARK\n";
    cout << " Compiler: C++ / chrono::steady_clock\n";
    cout << " Usage: benchmark.exe [N1 N2 ...]\n";
    cout << " Default: 10000 50000 100000 250000\n";
    cout << "==============================================================\n";

    for (int n : sizes) {
        // MC1 uses Q = N queries so that lookup cost is visible.
        const int q = n;
        HashBenchmarkResult hashResult = benchmarkHashTable(n, q);
        printHashResult(n, q, hashResult);

        PriorityBenchmarkResult pqResult = benchmarkPriorityQueue(n);
        long long sortChecksum = 0;
        double sortMs = benchmarkSortAll(n, sortChecksum);
        printPriorityResult(n, pqResult, sortMs, sortChecksum);
    }

    cout << "\nNotes:\n";
    cout << "- Each benchmark uses deterministic generated data.\n";
    cout << "- Checksum is used to ensure measured work is not optimized away.\n";
    cout << "- Run in Release/O2 for meaningful performance measurements.\n";
    cout << "- The STL implementations are reference baselines, not project replacements.\n";

    return 0;
}
