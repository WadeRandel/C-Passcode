/*
Wade Randel
Passcode
This program reads from a file containing 50 successful login attempts. The program uses backtracking as a method to find the
shortest password possible. The four secure coding practices used in this program are input validation when opening a file, input validation to
help prevent buffer overflow, I have also used C Strings, and modern c++ practices using things like <iostream> for I/O.
*/

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

// Function Prototypes
std::vector<std::string> loginAttempts(const std::string& filename);
void shortestPasscode(const std::vector<std::string>& attempts, std::string& passcode, std::unordered_set<char>& visited, char digit);

int main() {
    // Read login attempts
    std::vector<std::string> attempts = loginAttempts("keylog.txt");

    // Find unique digits in the attempts
    std::unordered_set<char> digits;
    for (const auto& attempt : attempts) {
        for (char digit : attempt) {
            digits.insert(digit);
        }
    }

    // Set variables for backtracking
    std::string passcode;
    std::unordered_set<char> visited;

    // Backtrack from each unique digit
    for (char digit : digits) {
        if (visited.find(digit) == visited.end()) {
            shortestPasscode(attempts, passcode, visited, digit);
        }
    }

    // Reverse passcode
    std::reverse(passcode.begin(), passcode.end());

    //Output
    std::cout << "Shortest Passcode: " << passcode << std::endl;

    return 0;
}

// Function definitions
std::vector<std::string> loginAttempts(const std::string& filename) {
    std::vector<std::string> attempts;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return attempts;
    }
    std::string attempt;
    while (std::getline(file, attempt)) {
        attempts.push_back(attempt);
    }
    file.close();
    return attempts;
}

// Find the shortest passcode using backtracking
void shortestPasscode(const std::vector<std::string>& attempts, std::string& passcode, std::unordered_set<char>& visited, char digit) {
    visited.insert(digit);
    for (const auto& attempt : attempts) {
        size_t position = attempt.find(digit);
        if (position != std::string::npos && position + 1 < attempt.size()) {
            char nextDigit = attempt[position + 1];
            if (visited.find(nextDigit) == visited.end()) {
                shortestPasscode(attempts, passcode, visited, nextDigit);
            }
        }
    }
    passcode += digit;
}