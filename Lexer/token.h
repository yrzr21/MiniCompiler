#ifndef MINI_TOKEN_H
#define MINI_TOKEN_H

#include <map>
#include <string>

enum TokenType {
    PROGRAM = 1,
    BEGIN,
    END,
    VAR,
    INTEGER,
    IF,
    THEN,
    ELSE,
    DO,
    WHILE,
    IDENTIFIER,
    CONSTANT,  // 整型常数
    PLUS,
    MINUS,
    LPAREN,
    RPAREN,
    EQUAL,
    GREATER,
    LESS,

    COLON,
    ASSIGN,
    
    SEMICOLON,
    COMMA,
    WS,       // whitespace
    UNKNOWN,  // for error
    END_OF_FILE
};


class Token {
   public:
    TokenType type;
    std::string value;

   public:
    Token(TokenType t, std::string v = "") : type(t), value(v) {}

   public:
    // mapper
    static inline const std::map<std::string, TokenType> keywords_mapper = {
        {"program", TokenType::PROGRAM}, {"begin", TokenType::BEGIN},
        {"end", TokenType::END},         {"var", TokenType::VAR},
        {"integer", TokenType::INTEGER}, {"if", TokenType::IF},
        {"then", TokenType::THEN},       {"else", TokenType::ELSE},
        {"do", TokenType::DO},           {"while", TokenType::WHILE}};

    static inline const std::map<char, TokenType> operator_mapper = {
        {'+', TokenType::PLUS},   {'-', TokenType::MINUS},
        {'(', TokenType::LPAREN}, {')', TokenType::RPAREN},
        {'=', TokenType::EQUAL},  {'>', TokenType::GREATER},
        {'<', TokenType::LESS},   {';', TokenType::SEMICOLON},
        {',', TokenType::COMMA},  {':', TokenType::COLON}};
};

#endif  // !MINI_TOKEN_H