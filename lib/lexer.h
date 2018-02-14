#ifndef MYBF_LEXER_H
#define MYBF_LEXER_H

#include <iostream>
#include <vector>

enum Token {
    tok_eof = -1,

    tok_inc_pointer = -2,
    tok_dec_pointer = -3,

    tok_inc = -4,
    tok_dec = -5,

	tok_while_start = -6,
	tok_while_end = -7,

    tok_put = -8,
    tok_get = -9
};

class Lexer
{
public:
	explicit Lexer();

    std::vector<Token> getTokens();

private:
    bool isSpace(char ch);
    Token getNextToken();
    Token getTokenFromCh(char ch);
};

#endif