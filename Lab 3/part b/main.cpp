#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

struct LineNode {
    std::string text;
    LineNode* next;

    LineNode(const std::string& lineText) : text(lineText), next(nullptr) {}
};

class LineEditor {
private:
    LineNode* head;
    int lineCount;
    int currentLineNum;
    std::string filename;

    void clear() {
        while (head != nullptr) {
            LineNode* temp = head;
            head = head->next;
            delete temp;
        }
        lineCount = 0;
    }

    LineNode* getNodeAt(int index) {
        if (index < 1 || index > lineCount) {
            return nullptr;
        }
        LineNode* current = head;
        for (int i = 1; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

    void insertLine(int n, const std::string& lineText) {
        if (n < 1 || n > lineCount + 1) {
            std::cout << "Error: Line number out of range." << std::endl;
            return;
        }

        LineNode* newNode = new LineNode(lineText);
        if (n == 1) {
            newNode->next = head;
            head = newNode;
        } else {
            LineNode* prev = getNodeAt(n - 1);
            newNode->next = prev->next;
            prev->next = newNode;
        }
        lineCount++;
        currentLineNum = n + 1;
    }
    
    void deleteLine(int n) {
        if (n < 1 || n > lineCount) {
            std::cout << "Error: Line number out of range." << std::endl;
            return;
        }

        LineNode* toDelete = nullptr;
        if (n == 1) {
            toDelete = head;
            head = head->next;
        } else {
            LineNode* prev = getNodeAt(n - 1);
            toDelete = prev->next;
            prev->next = toDelete->next;
        }
        delete toDelete;
        lineCount--;
        currentLineNum = (n > lineCount) ? lineCount + 1 : n;
        if (currentLineNum == 0) currentLineNum = 1;
    }

public:
    LineEditor(const std::string& fname) : head(nullptr), lineCount(0), currentLineNum(1), filename(fname) {}

    ~LineEditor() {
        clear();
    }

    void run() {
        std::string line;
        while (true) {
            std::cout << currentLineNum << "> ";
            if (!std::getline(std::cin, line)) {
                break;
            }

            std::stringstream ss(line);
            std::string command;
            ss >> command;

            if (command == "I") {
                int n;
                ss >> n;
                if (ss.fail()) {
                    n = currentLineNum;
                }
                std::cout << n << "> ";
                std::string textToInsert;
                std::getline(std::cin, textToInsert);
                insertLine(n, textToInsert);
            } else if (command == "D") {
                int n, m;
                ss >> n;
                if (ss.fail()) {
                    deleteLine(currentLineNum);
                    continue;
                }
                ss >> m;
                if (ss.fail()) {
                    m = n;
                }
                for (int i = m; i >= n; --i) {
                    deleteLine(i);
                }
            } else if (command == "L") {
                 LineNode* current = head;
                 for (int i = 1; i <= lineCount; ++i) {
                     std::cout << i << "> " << current->text << std::endl;
                     current = current->next;
                 }
            } else if (command == "A") {
                std::cout << lineCount + 1 << "> ";
                std::string textToAppend;
                std::getline(std::cin, textToAppend);
                insertLine(lineCount + 1, textToAppend);
            } else if (command == "E") {
                std::ofstream outFile(filename);
                if (outFile.is_open()) {
                    LineNode* current = head;
                    while (current != nullptr) {
                        outFile << current->text << std::endl;
                        current = current->next;
                    }
                    outFile.close();
                } else {
                    std::cout << "Error: Could not open file " << filename << " for writing." << std::endl;
                }
                break;
            } else {
                insertLine(currentLineNum, line);
            }
        }
    }
};

int main() {
    std::string initialCommand;
    std::cout << "Enter command (e.g., EDIT filename): ";
    std::getline(std::cin, initialCommand);

    std::stringstream ss(initialCommand);
    std::string command, filename;
    ss >> command >> filename;

    if (command == "EDIT" && !filename.empty()) {
        LineEditor editor(filename);
        editor.run();
    } else {
        std::cout << "Invalid startup command. Please use 'EDIT filename'." << std::endl;
    }

    return 0;
}