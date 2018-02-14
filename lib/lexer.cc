#include "lexer.h"

Lexer::Lexer() {}

std::vector<Token> Lexer::getTokens()
{
    std::vector<Token> tokens;

    char ch;
    while (std::cin >> ch) {
        if (isSpace(ch)) continue;

        Token token = getTokenFromCh(ch);

        tokens.push_back(token);
    }

    return tokens;
}

bool Lexer::isSpace(char ch)
{
    if (ch == ' ') {
        return true;
    } else {
        return false;
    }
}

Token Lexer::getNextToken()
{
    char ch;
    std::cin >> ch;

    return this->getTokenFromCh(ch);
}

Token Lexer::getTokenFromCh(char ch)
{
    switch (ch) {
        case '>':
            return Token::tok_inc_pointer;
        case '<':
            return Token::tok_dec_pointer;
        case '+':
            return Token::tok_inc;
        case '-':
            return Token::tok_dec;
        case '[':
            return Token::tok_while_start;
        case ']':
            return Token::tok_while_end;
        case '.':
            return Token::tok_put;
        case ',':
            return Token::tok_get;
        default:
            throw "Invalid token";
    }
}