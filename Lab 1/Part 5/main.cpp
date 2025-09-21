#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

void createDataFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Apple" << std::endl;
        file << "Elephant" << std::endl;
        file << "Banana" << std::endl;
        file.close();
    } else {
        std::cerr << "Error: Unable to create data file." << std::endl;
    }
}

int main() {
    std::string filename = "data.txt";
    createDataFile(filename);

    std::ifstream data_file(filename);
    if (!data_file.is_open()) {
        std::cerr << "Error: Unable to open data file." << std::endl;
        return 1;
    }

    std::vector<std::pair<std::string, std::streampos>> records;
    std::string line;

    while (true) {
        std::streampos pos = data_file.tellg();
        if (getline(data_file, line)) {
            if (!line.empty()) {
                records.push_back({line, pos});
            }
        } else {
            break;
        }
    }

    std::sort(records.begin(), records.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    std::vector<std::streampos> sorted_positions;
    for (const auto& record : records) {
        sorted_positions.push_back(record.second);
    }

    // a. list the content of your vector
    std::cout << "a. Content of the new vector (file positions):" << std::endl;
    for (const auto& pos : sorted_positions) {
        std::cout << pos << std::endl;
    }
    std::cout << std::endl;

    // b. list the words using your vector
    std::cout << "b. Words listed in sorted order using the vector:" << std::endl;

    data_file.clear();

    for (const auto& pos : sorted_positions) {
        data_file.seekg(pos);
        getline(data_file, line);
        std::cout << line << std::endl;
    }

    data_file.close();
    return 0;
}