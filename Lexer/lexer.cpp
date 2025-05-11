#include "lexer.h"
using namespace std;

void Lexer::advance() {
    input.get(peek);
    if (peek == '\n') line_number++;
}


bool Lexer::isLetter(char c) { return isalpha(c) || c == '_'; }
bool Lexer::isDigit(char c) { return isdigit(c); }
bool Lexer::isOperator(char c) {
    return Token::operator_mapper.find(c) != Token::operator_mapper.end();
}

// keyword or identifier
Token Lexer::processIdentifier() {
    string result;  // 考虑优化？
    while (isLetter(peek) || isDigit(peek)) {
        result += tolower(peek);  // PASCAL 大小写不敏感
        advance();
    }

    // is keyword?
    auto iter = Token::keywords_mapper.find(result);
    // 不单独实现helper是为了复用iter
    if (iter != Token::keywords_mapper.end()) {
        return Token((*iter).second);
    }

    // is identifier
    return Token(TokenType::IDENTIFIER, result);
}

// constant int number
Token Lexer::processNumber() {
    string result;
    while (isDigit(peek)) {
        result += peek;
        advance();
    }

    return Token(TokenType::CONSTANT, result);
}

// operator
Token Lexer::processOperator() {
    char c = peek;
    advance();

    if (c == ':' && peek == '=') {
        advance();
        return Token(TokenType::ASSIGN);
    }

    auto iter = Token::operator_mapper.find(c);
    if (iter != Token::operator_mapper.end()) {
        return Token((*iter).second);
    }

    cerr << "Error: Unknown character '" << c << "' at line " << line_number
         << endl;
    return Token(TokenType::UNKNOWN);
}

Lexer::Lexer(string input_filename, string output_filename) : line_number(1) {
    input.open(input_filename);
    if (!input.is_open()) {
        cerr << "Error: Cannot open input file " << input_filename << endl;
        exit(1);
    }

    output.open(output_filename);
    if (!output.is_open()) {
        cerr << "Error: Cannot open output file " << output_filename << endl;
        exit(1);
    }

    advance();
}

Lexer::~Lexer() {
    if (input.is_open()) input.close();
    if (output.is_open()) output.close();
}

Token Lexer::nextToken() {
    if (input.eof()) {
        return Token(TokenType::END_OF_FILE);
    }

    if (isspace(peek)) {
        advance();
        return Token(TokenType::WS);
    }

    if (isLetter(peek)) {
        return processIdentifier();
    }

    if (isDigit(peek)) {
        return processNumber();
    }

    if (isOperator(peek)) {
        // 这里有两次map查询，考虑优化？
        return processOperator();
    }

    // error
    return Token(TokenType::UNKNOWN);
}

void Lexer::analyzeAll() {
    Token token = nextToken();
    for (; token.type != TokenType::END_OF_FILE; token = nextToken()) {
        output << "(" << token.type;
        if (!token.value.empty()) {
            output << ", " << token.value;
        } else {
            output << ", —";
        }
        output << ")\n";
    }
}