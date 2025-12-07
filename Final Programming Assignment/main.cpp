#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// Task 1: Data Structure Definition
struct Node {
    string word;
    string definition;
    Node* left;
    Node* right;

    Node(string w, string d) : word(w), definition(d), left(nullptr), right(nullptr) {}
};

class Dictionary {
private:
    Node* root;

    string toLower(string s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

    Node* insertRecursive(Node* current, string word, string definition) {
        if (current == nullptr) {
            return new Node(word, definition);
        }

        if (toLower(word) < toLower(current->word)) {
            current->left = insertRecursive(current->left, word, definition);
        } else if (toLower(word) > toLower(current->word)) {
            current->right = insertRecursive(current->right, word, definition);
        }
        return current;
    }

    // Task 2: Recursive helper for search
    Node* searchRecursive(Node* current, string key) {
        if (current == nullptr) {
            return nullptr;
        }

        string lowerKey = toLower(key);
        string lowerCurrent = toLower(current->word);

        if (lowerKey == lowerCurrent) {
            return current;
        } else if (lowerKey < lowerCurrent) {
            return searchRecursive(current->left, key);
        } else {
            return searchRecursive(current->right, key);
        }
    }

    void destroyRecursive(Node* node) {
        if (node) {
            destroyRecursive(node->left);
            destroyRecursive(node->right);
            delete node;
        }
    }

public:
    Dictionary() : root(nullptr) {}

    ~Dictionary() {
        destroyRecursive(root);
    }

    void insert(string word, string definition) {
        root = insertRecursive(root, word, definition);
    }

    void findWord(string word) {
        Node* result = searchRecursive(root, word);
        if (result != nullptr) {
            cout << "-------------------------------------------------------" << endl;
            cout << "Word: " << result->word << endl;
            cout << "Definition: " << result->definition << endl;
            cout << "-------------------------------------------------------" << endl;
        } else {
            cout << ">> '" << word << "' was not found in the dictionary." << endl;
        }
    }
};

int main() {
    Dictionary dict;
    
    dict.insert("Dance", "To move one's feet or body, or both, rhythmically in a pattern of steps, especially to the accompaniment of music.");
    dict.insert("Apple", "The usually round, red or yellow, edible fruit of a small tree, Malus sylvestris, of the rose family.");
    dict.insert("Buffalo", "Any of several large wild oxen of the family Bovidae.");
    dict.insert("Computer", "A programmable electronic device designed to accept data, perform prescribed mathematical and logical operations at high speed, and display the results of these operations.");
    dict.insert("Elephant", "A very large herbivorous mammal of the family Elephantidae, the only extant family of proboscideans and comprising the genera Loxodonta (African elephants) and Elephus (Asian elephants)");
    dict.insert("Friend", "A person attached to another by feelings of affection or personal regard.");
    dict.insert("Goat", "Any of numerous agile, hollow-horned ruminants of the genus Capra, of the family Bovidae, closely related to the sheep, found native in rocky and mountainous regions of the Old World, and widely distributed in domesticated varieties.");

    string input;
    cout << "Welcome to the Binary Tree Dictionary." << endl;
    cout << "Type 'exit' to quit the program." << endl;

    while (true) {
        cout << "\nEnter a word to search: ";
        getline(cin, input);

        if (input == "exit") {
            break;
        }

        dict.findWord(input);
    }

    return 0;
}