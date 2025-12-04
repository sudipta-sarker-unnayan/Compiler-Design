#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <set>
using namespace std;

// Keywords list
vector<string> keywords = {"int", "return", "float", "double", "char", "void", "long", "short"};

// Check if keyword
bool isKeyword(const string &s) {
    for (auto &k : keywords)
        if (s == k) return true;
    return false;
}

// Check if identifier
bool isIdentifier(const string &s) {
    if (!isalpha(s[0]) && s[0] != '_') return false;
    for (char c : s)
        if (!isalnum(c) && c != '_') return false;
    return true;
}

// Check if number
bool isNumber(const string &s) {
    for (char c : s)
        if (!isdigit(c)) return false;
    return true;
}

bool isDelimiter(char c) {
    return (c==' ' || c=='\t' || c=='(' || c==')' || c=='{' || c=='}' ||
            c==',' || c==';' || c=='=');
}

string getTokenType(const string &token) {
    if (isKeyword(token)) return "KEYWORD";
    if (isNumber(token)) return "NUMBER";
    if (isIdentifier(token)) return "IDENTIFIER";
    return "UNKNOWN";
}

int main() {
    ifstream file("input.cpp");
    if (!file.is_open()) {
        cout << "Cannot open input.cpp file!\n";
        return 1;
    }

    set<string> symbolTable;  // store identifiers

    string line;
    int lineNo = 1;

    while (getline(file, line)) {

        int tokenNo = 1;
        string token = "";

        for (char c : line) {
            if (isDelimiter(c)) {
                if (!token.empty()) {
                    string type = getTokenType(token);
                    cout << "Line " << lineNo << ", Token " << tokenNo++
                         << ": " << token << "    (" << type << ")\n";

                    if (type == "IDENTIFIER")
                        symbolTable.insert(token);

                    token = "";
                }

                if (c != ' ' && c != '\t') {
                    string s(1, c);
                    string type;

                    if (c == '=')
                        type = "OPERATOR";
                    else
                        type = "SEPARATOR";

                    cout << "Line " << lineNo << ", Token " << tokenNo++
                         << ": " << s << "    (" << type << ")\n";
                }
            }
            else {
                token += c;
            }
        }

        if (!token.empty()) {
            string type = getTokenType(token);
            cout << "Line " << lineNo << ", Token " << tokenNo++
                 << ": " << token << "    (" << type << ")\n";

            if (type == "IDENTIFIER")
                symbolTable.insert(token);
        }

        lineNo++;
    }

    // Print symbol table
    cout << "\n--- SYMBOL TABLE ---\n";
    for (auto &id : symbolTable)
        cout << id << "\n";

    return 0;
}
