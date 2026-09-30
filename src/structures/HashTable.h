#pragma once
 
#include <vector>
#include<string>
#include <functional>
#include <stdexcept>
#include "DoubleLinkedList.h"
using namespace std;

struct Entry
{
    string key;
    string value;

    Entry (const string &k, const string &v){
        key = k;
        value = v;
    }

    //Kiểm tra 2 Entry có giống nhau
    bool operator == (const Entry &other) const{
        return key == other.key;
    }
};


template <typename V>
class HashTable{
    private:
        vector<DoubleLinkedList<Entry<V>>> buckets;
        int count; // biến đếm số lượng Entry có trong HashTable

        //Hàm băm -> mã băm
        size_t hashCode(const string &key) const{
            return std::hash<string>{}(key);
        }

        //Định vị buckets của một key sẽ được lưu vào
        int slotOf (const string &key) const{
            return hashCode(key) % buckets.size();
        }

        void rawInsert (const string &key, const V &value){
            int index = slotOf(key);
            //Tìm key trong buckets, nếu có thì cập nhật giá trị
            Entry* entry = buckets[index].Search(Entry(key, value));
            if (entry != nullptr){
                entry->value = value;
                return;
            }

            //Không có thì thêm Entry mới vò bucket
            buckets[index].pushBack(Entry(key, value));
            count++;
        }
    public:
        //Khởi tạo bảng băm
        HashTable(int capacity = 8){
            buckets.resize(capacity);
            count = 0;
        }

        //Trả về con trỏ tới value (nếu null thì không phải sao chép)
        V* find(const string& key) {
            Entry<V>* entry = buckets[slotOf(key)].Search(Entry<V>(key, V()));
            return entry != nullptr ? &entry->value : nullptr;
        }
 
        const V* find(const string& key) const {
            const Entry<V>* entry = buckets[slotOf(key)].Search(Entry<V>(key, V()));
            return entry != nullptr ? &entry->value : nullptr;
        }



        //Thêm một Entry
        void put(const string& key, const V& value) {
            rawInsert(key, value);
            //Kiểm tra buckets sắp đầy hay chưa (áp dụng công thức)
            if ((double) count / buckets.size() > 0.75) {
                resize(2 * buckets.size());
            }
        }

        //Lấy giá trị
        bool get(const string& key, V& result) const {
            const V* value = find(key);
            if (value == nullptr) return false;
            result = *value;
            return true;
        }
 
        //Kiểm tra key có tồn tại không
        bool contains(const string& key) const {
            return find(key) != nullptr;
        }
 
        //Xóa một Entry
        bool remove(const string& key) {
            size_t index = slotOf(key);
            if (buckets[index].Search(Entry<V>(key, V())) == nullptr) return false;
            buckets[index].Delete(Entry<V>(key, V()));
            count--;
            return true;
        }
 
        //Số lượng Entry
        int size() const {
            return count;
        }
 
        //Tăng kích thước
        void resize(int new_capacity) {
            // move thay vì copy để không sao chép cả các danh sách
            vector<DoubleLinkedList<Entry<V>>> old_buckets = std::move(buckets);
            buckets.clear();
            buckets.resize(new_capacity);
            count = 0;
 
            for (const auto& bucket : old_buckets) {
                // Duyệt các Entry trong bucket
                for (const Entry<V>& entry : bucket) {
                    rawInsert(entry.key, entry.value);
                }
            }
        }
};