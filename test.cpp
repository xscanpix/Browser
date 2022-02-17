#include "LibJS/Lexer.h"
#include "LibJS/Source.h"
#include "LibJS/Token.h"

#include "SN/ContextFreeGrammar.h"

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  {
    auto cfg = SN::ContextFreeGrammar{};

    auto s = cfg.add_symbol(SN::CFGSymbol::create_non_terminal_symbol("Rule1"));
    auto s2 =
        cfg.add_symbol(SN::CFGSymbol::create_non_terminal_symbol("Rule2"));
    auto s3 =
        cfg.add_symbol(SN::CFGSymbol::create_non_terminal_symbol("Rule2"));
    auto s4 = cfg.add_symbol(SN::CFGSymbol::create_terminal_symbol("x"));

    auto r1 = cfg.add_rule(s, {s2, s3, s4});

    std::cout << *r1;
  }

  /*
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
   */

  return 0;
}
