#ifndef __hash__
#define __hash__

#include <cassert>
#include <iostream>
#include <limits>
#include <vector>
#include <string>

#include "../part-1/list.hpp"

template <typename K, typename V, typename H> class HashTable
{
  public:
    HashTable(size_t num_chains) : _table{num_chains} {}

    void insert(const K &key, const V &value)
    {
        size_t slot = _get_slot(key);
        Node<KeyValuePair> *node = _find_key(slot, key);
        if (!node) {
            list_insert_after(&_table[slot], {key, value});
        } else {
            node->next->value.value = value;
        }
    }

    V *get(const K &key)
    {
        size_t slot = _get_slot(key);
        Node<KeyValuePair> *node = _find_key(slot, key);
        if (!node) { return nullptr; }
        return &node->next->value.value;
    }

    void print(bool details = false) const
    {
        size_t min = std::numeric_limits<size_t>::max(), max = 0, average = 0;
        for (size_t slot = 0; slot < _table.size(); ++slot) {
            if (details) { std::cout << "Slot " << slot << " contains"; }
            size_t count = 0;
            for (Node<KeyValuePair> *node = _table[slot].next.get(); node;
                 node = node->next.get()) {
                if (details) { std::cout << " '" << node->value.key << '\''; }
                count++;
            }
            if (details) { std::cout << " (" << count << ")\n"; }
            max = std::max(count, max);
            min = std::min(count, min);
            average += count;
        }
        std::cout << "Slot sizes: min: " << min;
        std::cout << ", max: " << max;
        std::cout << ", average: " << float(average) / _table.size() << '\n';
    }

    // Inserting question 8.3 code here - hash function for strings
    uint32_t hash(const std::string& str, const uint32_t m){
        uint32_t hash_value = 0;
        uint32_t running_mult = 1; //Running multiplier
        assert(m > 0);  // Ensures m is greater than 0 to avoid division by zero

        for (int i = 0; i < str.size(); ++i) {
            unsigned char c = str[str.size() - 1 - i];
            hash_value = (hash_value + ((c % m) * running_mult)) % m;
            running_mult = (running_mult * 256) % m; // Update the multiplier
        }
        
        return hash_value;

    }

  private:
    struct KeyValuePair {
        K key;
        V value;
    };

    std::vector<Node<KeyValuePair>> _table;

    size_t _get_slot(const K &key) const { return H{}(key) % _table.size(); }

    Node<KeyValuePair> *_find_key(size_t slot, const K &key)
    {
        auto match = [&](const KeyValuePair &pair) { return pair.key == key; };
        return list_find_predecessor(&_table[slot], match);
    }
};

#endif // __hash__