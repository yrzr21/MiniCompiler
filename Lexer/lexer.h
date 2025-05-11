#ifndef MINI_LEXER_H
#define MINI_LEXER_H

#include <cctype>
#include <fstream>
#include <iostream>
#include <vector>

#include "token.h"

// 词法分析器类
class Lexer {
   private:
    char peek;
    int line_number;  // for debug, start at 1

   private:
    bool isLetter(char c);
    bool isDigit(char c);
    bool isOperator(char c);

    void advance();
    Token processIdentifier();
    Token processNumber();
    Token processOperator();

   public:
    std::ifstream input;
    std::ofstream output;

    Lexer(std::string input_filename, std::string output_filename);
    ~Lexer();

    Token nextToken();
    void analyzeAll();
};

#endif  // !MINI_LEXER_H
