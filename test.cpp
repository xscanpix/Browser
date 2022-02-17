#include <iomanip>
#include <iostream>

#include "LibJS/Lexer.h"
#include "LibJS/Source.h"
#include "LibJS/Token.h"

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  auto source_file = LibJS::Source::from_path("./res/testfile.js");

  if (source_file.length() == 0) {
    return -1;
  }

  LibJS::Lexer lexer{source_file};

  while (true) {
    auto token = lexer.next();

    std::cout << token << std::endl;

    if (token.type() == LibJS::TokenType::Eof ||
        token.type() == LibJS::TokenType::Invalid) {
      break;
    }
  };

  return 0;
}
