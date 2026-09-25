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


class HashTable{
    private:
        vector<DoubleLinkedList<Entry>> buckets;
        int count; // biến đếm số lượng Entry có trong HashTable

        //Hàm băm -> mã băm
        size_t hashCode(const string &key) const{
            return std::hash<string>{}(key);
        }

        //Định vị buckets của một key sẽ được lưu vào
        int slotOf (const string &key) const{
            return hashCode(key) % buckets.size();
        }

        void rawInsert (const string &key, const string &value){
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

        //Thêm một Entry
        void put(const string& key, const string& value) {
            rawInsert(key, value);
            //Kiểm tra buckets sắp đầy hay chưa (áp dụng công thức)
            if ((double) count / buckets.size() > 0.75) {
                resize(2 * buckets.size());
            }
        }

        //Lấy giá trị
        bool get(const string& key, string& result) const {
            int index = slotOf(key);
            // Tìm Entry có key tương ứng
            Entry* entry = buckets[index].Search(Entry(key, ""));
            if (entry != nullptr) {
                result = entry->value;
                return true;
            }
            return false;
        }

        //Xóa một buckets
        bool remove(const string& key) {
            int index = slotOf(key);
            Entry* entry = buckets[index].Search(Entry(key, ""));
            if (entry == nullptr) return false;
            buckets[index].Delete(*entry);
            count--;
            return true;
        }

        //Tăng kích thước
        void resize(int new_capacity) {
            vector<DoublyLinkedList<Entry>> old_buckets = buckets;
            buckets.clear();
            buckets.resize(new_capacity);
            count = 0;

            for (const auto& bucket : old_buckets) {
                // Duyệt các Entry trong bucket
                for (const Entry& entry : bucket) {
                    rawInsert(entry.key, entry.value);
                }
            }
        }
};