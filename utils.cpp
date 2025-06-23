#include "utils.h"
#include <fstream>
#include <iostream>
using namespace std;

void write_to_file(const string& filename, const vector<string>& content) {
    ofstream f(filename);
    if (!f) {
        cerr << "[ERROR] Cannot open file: " << filename << endl;
        return;
    }
    for (const auto& line : content) {
        f << line << '\n';
    }
    f.flush();
    f.close();
    ifstream check(filename);
    string result((istreambuf_iterator<char>(check)), istreambuf_iterator<char>());
    if (result.empty()) {
        cerr << "[WARNING] " << filename << " is empty after writing!" << endl;
    } else {
        cout << "[INFO] " << filename << " successfully written." << endl;
    }
}

void write_to_file(const string& filename, const string& content) {
    ofstream f(filename);
    if (!f) {
        cerr << "[ERROR] Cannot open file: " << filename << endl;
        return;
    }
    f << content;
    f.flush();
    f.close();
    ifstream check(filename);
    string result((istreambuf_iterator<char>(check)), istreambuf_iterator<char>());
    if (result.empty()) {
        cerr << "[WARNING] " << filename << " is empty after writing!" << endl;
    } else {
        cout << "[INFO] " << filename << " successfully written." << endl;
    }
} 