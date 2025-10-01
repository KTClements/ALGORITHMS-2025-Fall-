#include <iostream>
#include <string>
#include <stack>

bool delimiterMatching(const std::string& expr) {
    std::stack<char> s;
    for (char ch : expr) {
        if (ch == '(' || ch == '[' || ch == '{') {
            s.push(ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (s.empty()) {
                return false;
            }
            char open = s.top();
            s.pop();
            if ((ch == ')' && open != '(') ||
                (ch == ']' && open != '[') ||
                (ch == '}' && open != '{')) {
                return false;
            }
        }
    }
    return s.empty();
}

int main() {
    std::cout << "--- Delimiter Matching Program ---" << std::endl;

    // a. Test with (x+b)
    std::string test1 = "(x+b)";
    std::cout << "\nTesting expression: " << test1 << std::endl;
    if (delimiterMatching(test1)) {
        std::cout << "Result: Delimiters are balanced." << std::endl;
    } else {
        std::cout << "Result: Delimiters are NOT balanced." << std::endl;
    }

    // b. Test it again with (a+b))
    std::string test2 = "(a+b))";
    std::cout << "\nTesting expression: " << test2 << std::endl;
    if (delimiterMatching(test2)) {
        std::cout << "Result: Delimiters are balanced." << std::endl;
    } else {
        std::cout << "Result: Delimiters are NOT balanced." << std::endl;
    }
    
    // c. Ask the user to enter an equation and test
    std::string userInput;
    std::cout << "\nPlease enter an equation to test: ";
    std::getline(std::cin, userInput);
    std::cout << "Testing user expression: " << userInput << std::endl;
    if (delimiterMatching(userInput)) {
        std::cout << "Result: Delimiters are balanced." << std::endl;
    } else {
        std::cout << "Result: Delimiters are NOT balanced." << std::endl;
    }

    return 0;
}