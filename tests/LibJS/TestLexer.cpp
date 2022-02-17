#include <gtest/gtest.h>

#include "LibJS/Lexer.h"
#include "LibJS/Source.h"

using ::testing::EmptyTestEventListener;
using ::testing::InitGoogleTest;
using ::testing::Test;
using ::testing::TestEventListeners;
using ::testing::TestInfo;
using ::testing::TestPartResult;
using ::testing::UnitTest;

using LibJS::Lexer;
using LibJS::Source;
using LibJS::Token;
using LibJS::TokenType;

static bool tokens_eq(Token const &first, Token const &second) {
  return (first.type() == second.type()) && (first.value() == second.value());
}

TEST(TestLexer, After_If) {
  auto test_string = "if(x){} /y/.test(z)";
  Lexer lexer{Source::from_text(test_string)};

  ASSERT_TRUE(tokens_eq(lexer.next(), {TokenType::If}));
  ASSERT_TRUE(tokens_eq(lexer.next(), {TokenType::ParenOpen}));
  ASSERT_TRUE(tokens_eq(lexer.next(), {TokenType::Identifier, "x"}));
  ASSERT_TRUE(tokens_eq(lexer.next(), {TokenType::ParenClose}));
  ASSERT_TRUE(tokens_eq(lexer.next(), {TokenType::CurlyOpen}));
  ASSERT_TRUE(tokens_eq(lexer.next(), {TokenType::CurlyClose}));
  ASSERT_TRUE(tokens_eq(lexer.next(), {TokenType::RegexLiteral, "/y/"}));
  ASSERT_TRUE(tokens_eq(lexer.next(), {TokenType::Period}));
  ASSERT_TRUE(tokens_eq(lexer.next(), {TokenType::Identifier, "test"}));
  ASSERT_TRUE(tokens_eq(lexer.next(), {TokenType::ParenOpen}));
  ASSERT_TRUE(tokens_eq(lexer.next(), {TokenType::Identifier, "z"}));
  ASSERT_TRUE(tokens_eq(lexer.next(), {TokenType::ParenClose}));
  ASSERT_TRUE(tokens_eq(lexer.next(), {TokenType::Eof}));
}

int main(int argc, char **argv) {
  InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
