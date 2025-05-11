#include "../Lexer/lexer.h"

using namespace std;

int main() {
    string inputFilename =
        "/home/toki/workspace/Projects/MiniCompiler/Resource/input.txt";
    string outputFilename =
        "/home/toki/workspace/Projects/MiniCompiler/Resource/output.txt";

    Lexer lexer(inputFilename, outputFilename);

    Token token = lexer.nextToken();
    for (; token.type != TokenType::END_OF_FILE; token = lexer.nextToken()) {
        switch (token.type) {
            case TokenType::WS:
            case TokenType::SEMICOLON:
            case TokenType::COMMA:
            case TokenType::UNKNOWN:
                continue;
        }

        lexer.output << "(" << token.type;
        if (!token.value.empty()) {
            lexer.output << ", " << token.value;
        } else {
            lexer.output << ", —";
        }
        lexer.output << ")\n";
    }
    lexer.analyzeAll();

    cout << "Lexical analysis completed. Results saved to " << outputFilename
         << endl;

    return 0;
}