#include <iostream>

#include "lib/lexer.h"
#include "lib/parser.h"
#include "lib/compiler.h"

int main(int argv, char* argc[])
{
    Lexer lexer;
    std::vector<Token> tokens = lexer.getTokens();

    Compiler compiler;
    compiler.compile(tokens);

	return 0;
}