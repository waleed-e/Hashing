#include <iostream>
#include <list>
#include <utility> // For std::pair
#include <string>
#include <vector>
#include <functional> // For std::hash

using namespace std;

class HashTable {
private:
    static const int hashgroups = 10;  // Static constant for hash table size
    vector<list<pair<string, int>>> table;

public:
    HashTable() : table(hashgroups) {}

    void insert(const string& key, int value) {
        // Hash function directly in this method
        size_t index = hash<string>{}(key) % hashgroups;
        auto& chain = table[index];

        for (auto& node : chain) {
            if (node.first == key) {
                node.second = value;
                return;
            }
        }
        chain.emplace_back(key, value);
    }

    void remove(const string& key) {
        // Hash function directly in this method
        size_t index = hash<string>{}(key) % hashgroups;
        auto& chain = table[index];

        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) {
                chain.erase(it);
                return;
            }
        }
    }

    void print() const {
        for (size_t i = 0; i < table.size(); ++i) {
            const auto& chain = table[i];
            cout << "Bucket " << i << ": ";
            if (chain.empty()) {
                cout << "Empty";
            }
            else {
                for (const auto& node : chain) {
                    cout << "(" << node.first << ": " << node.second << ") -> ";
                }
            }
            cout << "None" << endl;
        }
    }

    bool isEmpty() const {
        for (const auto& chain : table) {
            if (!chain.empty()) {
                return false;
            }
        }
        return true;
    }
};

// Example usage
int main() {
    HashTable hashTable;

    hashTable.insert("name", 25);
    hashTable.insert("age", 30);
    hashTable.insert("city", 100);

    cout << "Hash Table contents:" << endl;
    hashTable.print();

    hashTable.remove("age");

    cout << "\nHash Table contents after removing 'age':" << endl;
    hashTable.print();

    if (hashTable.isEmpty()) {
        cout << "\nHash Table is empty." << endl;
    }
    else {
        cout << "\nHash Table is not empty." << endl;
    }

    return 0;
}
