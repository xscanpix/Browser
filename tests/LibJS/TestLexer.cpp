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

using SN::LibJS::Lexer;
using SN::LibJS::Source;
using SN::LibJS::Token;
using SN::LibJS::TokenType;

TEST(TestLexer, SingleLineComment_Alone) {
  auto test_string = "// This is a single line comment";
  Lexer lexer{Source::from_text(test_string)};

  ASSERT_EQ(lexer.next().type(), TokenType::Eof);
}

TEST(TestLexer, MultiLineComment_Alone) {
  auto test_string = "/* This is a multi line comment*/";
  Lexer lexer{Source::from_text(test_string)};

  ASSERT_EQ(lexer.next().type(), TokenType::Eof);
}

int main(int argc, char **argv) {
  InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}