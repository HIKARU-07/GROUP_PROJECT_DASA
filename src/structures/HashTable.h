#pragma once

#include <vector>
#include <string>
#include <functional>
#include <stdexcept>
#include "DoubleLinkedList.h"
using namespace std;

template <typename V>
struct Entry
{
    string key;
    V value;

    Entry() : key(), value() {}                        // thêm: để Node dùng được
    Entry(const string &k, const V &v) : key(k), value(v) {}

    bool operator==(const Entry &other) const { return key == other.key; }
    bool operator!=(const Entry &other) const { return !(*this == other); }  // thêm: cho DoubleLinkedList::Delete
};

template <typename V>
class HashTable
{
private:
    vector<DoubleLinkedList<Entry<V>>> buckets;
    int count;

    size_t hashCode(const string &key) const
    {
        return std::hash<string>{}(key);
    }

    int slotOf(const string &key) const
    {
        return hashCode(key) % buckets.size();
    }

    // Vị trí của key trong một bucket, -1 nếu không có
    int posInBucket(const DoubleLinkedList<Entry<V>> &b, const string &key) const
    {
        for (long long i = 0; i < b.getSize(); i++)
            if (b.getAt(i).key == key)
                return (int)i;
        return -1;
    }

    void rawInsert(const string &key, const V &value)
    {
        auto &b = buckets[slotOf(key)];
        int pos = posInBucket(b, key);
        if (pos != -1)
        {
            b.getAt(pos).value = value;  // key đã có -> cập nhật
            return;
        }
        b.pushBack(Entry<V>(key, value));
        count++;
    }

public:
    HashTable(int capacity = 8)
    {
        buckets.resize(capacity);
        count = 0;
    }

    V *find(const string &key)
    {
        auto &b = buckets[slotOf(key)];
        int pos = posInBucket(b, key);
        return pos != -1 ? &b.getAt(pos).value : nullptr;
    }

    const V *find(const string &key) const
    {
        const auto &b = buckets[slotOf(key)];
        int pos = posInBucket(b, key);
        return pos != -1 ? &b.getAt(pos).value : nullptr;
    }

    void put(const string &key, const V &value)
    {
        rawInsert(key, value);
        if ((double)count / buckets.size() > 0.75)
            resize(2 * buckets.size());
    }

    bool get(const string &key, V &result) const
    {
        const V *value = find(key);
        if (value == nullptr) return false;
        result = *value;
        return true;
    }

    bool contains(const string &key) const
    {
        return find(key) != nullptr;
    }

    bool remove(const string &key)
    {
        auto &b = buckets[slotOf(key)];
        if (posInBucket(b, key) == -1) return false;
        b.Delete(Entry<V>(key, V()));
        count--;
        return true;
    }

    int size() const { return count; }

    void resize(int new_capacity)
    {
        vector<DoubleLinkedList<Entry<V>>> old_buckets = std::move(buckets);
        buckets.clear();
        buckets.resize(new_capacity);
        count = 0;

        for (const auto &bucket : old_buckets)
            for (long long i = 0; i < bucket.getSize(); i++)
            {
                const Entry<V> &e = bucket.getAt(i);
                rawInsert(e.key, e.value);
            }
    }
};