#include <iostream>
#include <iomanip>

#include "LibJS/Source.h"
#include "LibJS/Lexer.h"
#include "LibJS/Token.h"

int main(int argc, char **argv)
{
  auto source_file = SN::LibJS::Source("./res/testfile.js");

  SN::LibJS::Lexer lexer{source_file};

  SN::LibJS::Token token;

  do
  {
    token = lexer.next();
    std::cout << "Type: " << token.name() << " Message: " << token.message() << " Value: " << token.value() << std::endl;
  } while (token.type() != SN::LibJS::TokenType::Eof && token.type() != SN::LibJS::TokenType::Invalid);

  return 0;
}