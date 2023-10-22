#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <regex>

using namespace std;

vector<pair<string, string>> lexicalAnalyzer(ifstream &file) {

    regex numberFloatRegex("^\\d*\\.\\d+$");
    regex numberDecimalRegex("^\\d+$");
    regex numberHexadecimalRegex("^0[xX][0-9a-fA-F]+$");
    regex stringConstantRegex("\"[^\"]*\"");
    regex charConstantRegex("'.'");
    regex preprocessorRegex("^#[a-zA-Z_]\\w*$");
    regex commentRegex("^;.*$");
    regex reservedWordRegex("^(MOV|ADD|SUB|DIV|MUL)$");
    regex operatorRegex("^(AND|OR|XOR)$");
    regex separatorRegex("^[\\.,;:\\[\\]{}()]$");
    regex identifierRegex("^[a-zA-Z_][a-zA-Z0-9_]*$");

    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    vector<pair<regex, string>> patterns = {
            {numberFloatRegex, "Float number"},
            {numberDecimalRegex, "Dec number"},
            {numberHexadecimalRegex, "Hex number"},
            {stringConstantRegex, "String"},
            {charConstantRegex, "Char"},
            {preprocessorRegex, "Preprocessor"},
            {commentRegex, "Comment"},
            {reservedWordRegex, "Reserved word"},
            {operatorRegex, "Operator"},
            {separatorRegex, "Separator"},
            {identifierRegex, "Identifier"}
    };

    vector<pair<string, string>> lexemes;
    regex wordsRegex(";.*|\\d*\\.\\d+|\\w+|[\\.,;:\\[\\]{}()]|\"[^\"]*\"|'.'|#[a-zA-Z_][a-zA-Z0-9_]*\\b");
    smatch match;

    string::const_iterator start(code.cbegin());

    while (regex_search(start, code.cend(), match, wordsRegex)) {
        string lexeme = match[0];
        string lexemeType = "Error";

        for (const auto& pattern: patterns) {
            if (regex_match(lexeme, pattern.first)) {
                lexemeType = pattern.second;
                break;
            }
        }
        lexemes.emplace_back(lexeme, lexemeType);
        start = match.suffix().first;
    }
    return lexemes;
}

int main() {

    cout << "Lab task: code the analyzer to divide the code into lexemes and determine their type" << endl;
    cout << "Chernenko Yevhenii, TTP-32" << endl;

    string filename;
    ifstream file;

    cout << "Please enter the file name:" << endl;
    cin >> filename;

    do {
        file.open(filename);

        if(file.is_open()) {
            break;
        }

        cout << "Cannot read a file, please enter the file name again. Also, you can type 'exit' and stop a program" << endl;
        cin >> filename;

        if(filename == "exit"){
            return 1;
        }

    } while(true);

    vector<pair<string, string>> lexemes = lexicalAnalyzer(file);

    for (const auto& lexeme : lexemes) {
        cout << "< " << lexeme.first << " - " << lexeme.second << " >" << endl;
    }

    file.close();

    return 0;
}