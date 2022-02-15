#pragma once

#include <functional>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "LibBase/Base.h"

#include "LibJS/Source.h"
#include "LibJS/Token.h"

namespace SN::LibJS {
constexpr bool is_ascii_digit(char c) { return c >= '0' && c <= '9'; }
constexpr bool is_ascii_letter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

enum class LexerState {
  Start,
  Eof,
  Invalid,
  LineTerminator,
  SingleLineComment,
  MultiLineComment,
  Identifier,
  NumericLiteral,
  StringLiteral,
  Operand
};

class Lexer {
public:
  Lexer(Source source);

  Token run();

private:
  TokenType m_current_type{TokenType::Invalid};
  LexerState m_current_state{LexerState::Start};

  LexerState lexStart();
  LexerState lexMultiLineComment();
  LexerState lexSingleLineComment();
  LexerState lexIdentifier();
  LexerState lexNumericLiteral();
  LexerState lexStringLiteral();
  LexerState lexOperand();

  void consume();

  bool is_eof();
  bool is_unicode_character();
  bool is_whitespace();
  bool is_line_terminator();

  bool is_valid_identifier_start();
  bool is_valid_identifier_part();
  bool is_numeric_literal_start();

  bool match(char a);
  bool match(char a, char b);
  bool match(char a, char b, char c);
  bool match(char a, char b, char c, char d);

  template <typename Callback>
  bool match_numerical_literal_separator_followed_by(Callback callback) const;

  uint32_t current_code_point();

  Source m_source;
  char m_current_char;

  size_t m_value_start{0};
  size_t m_position{1};

  std::string m_message{};
  std::string m_value{};

  bool m_unterminated_comment{false};
  bool m_malformed_value{false};
  size_t m_hit_invalid_unicode_character;

  size_t m_line_number{1};
  size_t m_column_number{1};

  std::unordered_map<std::string, TokenType> s_keywords{};
  std::unordered_map<char, TokenType> s_one_char_tokens{};
  std::unordered_map<std::string, TokenType> s_two_char_tokens{};
  std::unordered_map<std::string, TokenType> s_three_char_tokens{};
};
} // namespace SN::LibJS