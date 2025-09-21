#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unordered_set>

const int MAX_LEVEL = 7;

struct Node {
    int key;
    Node** forward;
    int level;

    Node(int k, int lvl) : key(k), level(lvl) {
        forward = new Node*[level + 1];
        for (int i = 0; i <= level; ++i) {
            forward[i] = nullptr;
        }
    }

    ~Node() {
        delete[] forward;
    }
};

class SkipList {
private:
    Node* head;
    int currentLevel;

public:
    SkipList() {
        // (a) Implement data structure
        head = new Node(-1, MAX_LEVEL - 1);
        currentLevel = 0;
    }

    ~SkipList() {
        Node* current = head->forward[0];
        while (current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
        delete head;
    }

    int generateLevel() {
        int lvl = 1;
        while (rand() % 2 == 0 && lvl < MAX_LEVEL) {
            lvl++;
        }
        return lvl;
    }

    void insert(int key) {
        std::cout << "\n--------------------------------------------\n";
        std::cout << "Inserting Key: " << key << std::endl;

        Node* update[MAX_LEVEL];
        Node* current = head;

        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];
        if (current != nullptr && current->key == key) {
            std::cout << "Key " << key << " already exists. Skipping insertion." << std::endl;
            return;
        }

        // (c) Show level of choice before inserting a node
        int newLevel = generateLevel();
        std::cout << "Generated Level for new node: " << newLevel << std::endl;

        if (newLevel > currentLevel) {
            for (int i = currentLevel + 1; i < newLevel; ++i) {
                update[i] = head;
            }
            currentLevel = newLevel - 1;
        }

        Node* newNode = new Node(key, newLevel - 1);

        std::cout << "Linking new node..." << std::endl;
        for (int i = 0; i < newLevel; ++i) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
        std::cout << "Key " << key << " inserted successfully." << std::endl;
    }

    // (d) Show the trace of each level
    void display() {
        std::cout << "\n\n--- Final Skip List State ---\n";
        for (int i = MAX_LEVEL - 1; i >= 0; --i) {
            std::cout << "Level " << i + 1 << ": ";
            Node* node = head->forward[i];
            if (node == nullptr) {
                std::cout << "(empty)";
            }
            while (node != nullptr) {
                std::cout << node->key;
                if (node->forward[i] != nullptr) {
                    std::cout << ", ";
                }
                node = node->forward[i];
            }
            std::cout << std::endl;
        }
    }
};


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    SkipList sl;

    std::cout << "--- Starting Skip List Insertion Test ---\n";
    std::cout << "Generating 128 unique random numbers between 1 and 1000.\n";

    // (b) Randomly generate 128 numbers
    std::unordered_set<int> used_numbers;
    while (used_numbers.size() < 128) {
        int randomNumber = rand() % 1000 + 1;
        if (used_numbers.find(randomNumber) == used_numbers.end()) {
            used_numbers.insert(randomNumber);
            sl.insert(randomNumber);
        }
    }

    sl.display();

    return 0;
}