#include "LibJS/Lexer.h"

#include <algorithm>
#include <assert.h>
#include <iomanip>
#include <iostream>

namespace SN::LibJS {
Lexer::Lexer(Source source)
    : m_source(source), m_current_char(source[0]),
      m_hit_invalid_unicode_character(source.length() + 1) {
  if (s_keywords.empty()) {
    s_keywords.emplace("await", TokenType::Await);
    s_keywords.emplace("break", TokenType::Break);
    s_keywords.emplace("case", TokenType::Case);
    s_keywords.emplace("catch", TokenType::Catch);
    s_keywords.emplace("class", TokenType::Class);
    s_keywords.emplace("const", TokenType::Const);
    s_keywords.emplace("continue", TokenType::Continue);
    s_keywords.emplace("debugger", TokenType::Debugger);
    s_keywords.emplace("default", TokenType::Default);
    s_keywords.emplace("delete", TokenType::Delete);
    s_keywords.emplace("do", TokenType::Do);
    s_keywords.emplace("else", TokenType::Else);
    s_keywords.emplace("enum", TokenType::Enum);
    s_keywords.emplace("export", TokenType::Export);
    s_keywords.emplace("extends", TokenType::Extends);
    s_keywords.emplace("false", TokenType::BoolLiteral);
    s_keywords.emplace("finally", TokenType::Finally);
    s_keywords.emplace("for", TokenType::For);
    s_keywords.emplace("function", TokenType::Function);
    s_keywords.emplace("if", TokenType::If);
    s_keywords.emplace("import", TokenType::Import);
    s_keywords.emplace("in", TokenType::In);
    s_keywords.emplace("instanceof", TokenType::Instanceof);
    s_keywords.emplace("new", TokenType::New);
    s_keywords.emplace("null", TokenType::NullLiteral);
    s_keywords.emplace("return", TokenType::Return);
    s_keywords.emplace("super", TokenType::Super);
    s_keywords.emplace("switch", TokenType::Switch);
    s_keywords.emplace("this", TokenType::This);
    s_keywords.emplace("throw", TokenType::Throw);
    s_keywords.emplace("true", TokenType::BoolLiteral);
    s_keywords.emplace("try", TokenType::Try);
    s_keywords.emplace("typeof", TokenType::Typeof);
    s_keywords.emplace("var", TokenType::Var);
    s_keywords.emplace("void", TokenType::Void);
    s_keywords.emplace("while", TokenType::While);
    s_keywords.emplace("with", TokenType::With);
    s_keywords.emplace("yield", TokenType::Yield);
  }

  if (s_one_char_tokens.empty()) {
    s_one_char_tokens.emplace('&', TokenType::Ampersand);
    s_one_char_tokens.emplace('*', TokenType::Asterisk);
    s_one_char_tokens.emplace('[', TokenType::BracketOpen);
    s_one_char_tokens.emplace(']', TokenType::BracketClose);
    s_one_char_tokens.emplace('^', TokenType::Caret);
    s_one_char_tokens.emplace(':', TokenType::Colon);
    s_one_char_tokens.emplace(',', TokenType::Comma);
    s_one_char_tokens.emplace('{', TokenType::CurlyOpen);
    s_one_char_tokens.emplace('}', TokenType::CurlyClose);
    s_one_char_tokens.emplace('=', TokenType::Equals);
    s_one_char_tokens.emplace('!', TokenType::ExclamationMark);
    s_one_char_tokens.emplace('-', TokenType::Minus);
    s_one_char_tokens.emplace('(', TokenType::ParenOpen);
    s_one_char_tokens.emplace(')', TokenType::ParenClose);
    s_one_char_tokens.emplace('%', TokenType::Percent);
    s_one_char_tokens.emplace('.', TokenType::Period);
    s_one_char_tokens.emplace('|', TokenType::Pipe);
    s_one_char_tokens.emplace('+', TokenType::Plus);
    s_one_char_tokens.emplace('?', TokenType::QuestionMark);
    s_one_char_tokens.emplace(';', TokenType::Semicolon);
    s_one_char_tokens.emplace('/', TokenType::Slash);
    s_one_char_tokens.emplace('~', TokenType::Tilde);
    s_one_char_tokens.emplace('<', TokenType::LessThan);
    s_one_char_tokens.emplace('>', TokenType::GreaterThan);
  }

  if (s_two_char_tokens.empty()) {
    s_two_char_tokens.emplace("=>", TokenType::Arrow);
    s_two_char_tokens.emplace("+=", TokenType::PlusEquals);
    s_two_char_tokens.emplace("-=", TokenType::MinusEquals);
    s_two_char_tokens.emplace("*=", TokenType::AsteriskEquals);
    s_two_char_tokens.emplace("/=", TokenType::SlashEquals);
    s_two_char_tokens.emplace("%=", TokenType::PercentEquals);
    s_two_char_tokens.emplace("&=", TokenType::AmpersandEquals);
    s_two_char_tokens.emplace("|=", TokenType::PipeEquals);
    s_two_char_tokens.emplace("^=", TokenType::CaretEquals);
    s_two_char_tokens.emplace("&&", TokenType::DoubleAmpersand);
    s_two_char_tokens.emplace("||", TokenType::DoublePipe);
    s_two_char_tokens.emplace("??", TokenType::DoubleQuestionMark);
    s_two_char_tokens.emplace("**", TokenType::DoubleAsterisk);
    s_two_char_tokens.emplace("==", TokenType::EqualsEquals);
    s_two_char_tokens.emplace("<=", TokenType::LessThanEquals);
    s_two_char_tokens.emplace(">=", TokenType::GreaterThanEquals);
    s_two_char_tokens.emplace("!=", TokenType::ExclamationMarkEquals);
    s_two_char_tokens.emplace("--", TokenType::MinusMinus);
    s_two_char_tokens.emplace("++", TokenType::PlusPlus);
    s_two_char_tokens.emplace("<<", TokenType::ShiftLeft);
    s_two_char_tokens.emplace(">>", TokenType::ShiftRight);
    s_two_char_tokens.emplace("?.", TokenType::QuestionMarkPeriod);
  }

  if (s_two_char_tokens.empty()) {
    s_three_char_tokens.emplace("===", TokenType::EqualsEqualsEquals);
    s_three_char_tokens.emplace("!==", TokenType::ExclamationMarkEqualsEquals);
    s_three_char_tokens.emplace("**=", TokenType::DoubleAsteriskEquals);
    s_three_char_tokens.emplace("<<=", TokenType::ShiftLeftEquals);
    s_three_char_tokens.emplace(">>=", TokenType::ShiftRightEquals);
    s_three_char_tokens.emplace("&&=", TokenType::DoubleAmpersandEquals);
    s_three_char_tokens.emplace("||=", TokenType::DoublePipeEquals);
    s_three_char_tokens.emplace("\?\?=", TokenType::DoubleQuestionMarkEquals);
    s_three_char_tokens.emplace(">>>", TokenType::UnsignedShiftRight);
    s_three_char_tokens.emplace("...", TokenType::TripleDot);
  }
}

Token Lexer::run() {
  m_current_state = LexerState::Start;
  m_value = {};
  m_message = {};

  do {
    if (is_eof()) {
      m_current_type = TokenType::Eof;
      m_current_state = LexerState::Eof;
    }

    switch (m_current_state) {
    case LexerState::Eof: {
      return {TokenType::Eof, "", ""};
    }
    case LexerState::Invalid: {
      return {TokenType::Invalid, m_message, m_value};
    }
    case LexerState::Start: {
      m_current_state = lexStart();
      break;
    }
    case LexerState::LineTerminator: {
      return {m_current_type, "", ""};
    }
    case LexerState::SingleLineComment: {
      m_current_state = lexSingleLineComment();
      break;
    }
    case LexerState::MultiLineComment: {
      m_current_state = lexMultiLineComment();
      break;
    }
    case LexerState::Identifier: {
      m_current_state = lexIdentifier();
      return {m_current_type, m_message, m_value};
    }
    case LexerState::NumericLiteral: {
      m_current_state = lexNumericLiteral();
      return {m_current_type, m_message, m_value};
    }
    case LexerState::StringLiteral: {
      m_current_state = lexStringLiteral();
      return {m_current_type, m_message, m_value};
    }
    case LexerState::Operand: {
      m_current_state = lexOperand();
      return {m_current_type, m_message, m_value};
    }
    default: {
      m_current_state = LexerState::Invalid;
      m_message = "Unhandled";
      m_current_type = TokenType::Invalid;
      break;
    }
    }
  } while (true);

  assert(false);
} // namespace SN::LibJS

LexerState Lexer::lexStart() {
  while (true) {
    if (is_line_terminator()) {
      do {
        consume();
      } while (is_line_terminator());
      m_current_type = TokenType::LineTerminator;
      return LexerState::LineTerminator;
    } else if (is_whitespace()) {
      do {
        consume();
      } while (is_whitespace());
    } else if (match('/', '/')) {
      return LexerState::SingleLineComment;
    } else if (match('/', '*')) {
      return LexerState::MultiLineComment;
    } else {
      break;
    }
  }

  if (is_valid_identifier_start()) {
    return LexerState::Identifier;
  } else if (match('\'') || match('"')) {
    return LexerState::StringLiteral;
  } else if (is_numeric_literal_start()) {
    return LexerState::NumericLiteral;
  } else {
    return LexerState::Operand;
  }

  return LexerState::Invalid;
}

LexerState Lexer::lexSingleLineComment() {
  consume();
  consume();

  while (!is_eof() && !is_line_terminator()) {
    consume();
  }

  if (is_eof()) {
    return LexerState::Eof;
  }

  if (is_line_terminator()) {
    consume();
  }

  m_current_type = TokenType::LineTerminator;
  return LexerState::LineTerminator;
}

LexerState Lexer::lexMultiLineComment() {
  consume();

  do {
    consume();
  } while (!is_eof() && !match('*', '/'));

  if (is_eof()) {
    m_unterminated_comment = true;
  }

  consume();

  if (is_eof()) {
    m_unterminated_comment = true;
  }

  consume();

  if (m_unterminated_comment) {
    return LexerState::Invalid;
  }

  m_current_type = TokenType::LineTerminator;
  return LexerState::LineTerminator;
}

LexerState Lexer::lexIdentifier() {
  m_current_type = TokenType::Identifier;

  size_t value_start = m_position - 1;

  do {
    consume();
  } while (is_valid_identifier_part());

  auto identifier =
      m_source.substr(value_start, (m_position - value_start) - 1);

  if (auto it = s_keywords.find(identifier); it != s_keywords.end()) {
    m_value = it->first;
    m_current_type = it->second;
    return LexerState::Start;
  }

  m_value = identifier;

  return LexerState::Start;
}

LexerState Lexer::lexNumericLiteral() {
  m_current_type = TokenType::NumericLiteral;

  size_t value_start = m_position - 1;

  bool has_exponent{false};
  bool has_period{false};

  if (match('0')) {
    consume();

    m_current_type = TokenType::Invalid;
    m_message = "Unhandled";
    m_value = m_source.substr(value_start, (m_position - value_start) - 1);
    return LexerState::Invalid;
  } else {
    consume();

    while (true) {
      if (is_ascii_digit(m_current_char)) {
        consume();
      } else if (match_numerical_literal_separator_followed_by(
                     is_ascii_digit)) {
        consume();
        consume();
      } else {
        break;
      }
    }

    if (match('.')) {
      has_period = true;
      // Decimal
      consume();

      while (true) {
        if (is_ascii_digit(m_current_char)) {
          consume();
        } else if (match_numerical_literal_separator_followed_by(
                       is_ascii_digit)) {
          consume();
          consume();
        } else {
          break;
        }
      }
    }

    if (match('e') || match('E')) {
      has_exponent = true;
      // Exponent
      consume();

      if (is_eof()) {
        m_current_type = TokenType::Invalid;
        m_value = m_source.substr(value_start, (m_position - value_start) - 1);
        m_message = "Malformed numeric literal with exponent.";
        return LexerState::Invalid;
      }

      if (match('-') || match('+')) {
        consume();

        if (is_eof()) {
          m_current_type = TokenType::Invalid;
          m_value =
              m_source.substr(value_start, (m_position - value_start) - 1);
          m_message =
              "Malformed numeric literal: Explicit sign after exponent.";
          return LexerState::Invalid;
        }
      }

      if (!is_ascii_digit(m_current_char)) {
        m_current_type = TokenType::Invalid;
        m_value = m_source.substr(value_start, (m_position - value_start) - 1);
        m_message = "Malformed numeric literal: No a digit after exponent.";
        return LexerState::Invalid;
      }

      while (true) {
        if (is_ascii_digit(m_current_char)) {
          consume();
        } else if (match_numerical_literal_separator_followed_by(
                       is_ascii_digit)) {
          consume();
          consume();
        } else {
          break;
        }
      }
    }

    if (match('n')) {
      consume();
      if (has_exponent || has_period) {
        m_current_type = TokenType::Invalid;
        m_value = m_source.substr(value_start, (m_position - value_start) - 1);
        m_message = "Malformed numeric literal.";
        return LexerState::Invalid;
      }

      m_current_type = TokenType::BigIntLiteral;
    }

    m_value = m_source.substr(value_start, (m_position - value_start) - 1);
    return LexerState::Start;
  }
}

LexerState Lexer::lexStringLiteral() {
  char m_string_literal_stop_char = m_current_char;

  size_t start_string_literal = m_position;

  consume();

  while (!is_eof() && m_current_char != m_string_literal_stop_char &&
         m_current_char != LINE_FEED && m_current_char != CARRIAGE_RETURN) {
    if (m_current_char == '\\') {
      m_current_type = TokenType::Invalid;
      m_message = "Unhandled";
      m_value = '\\';
      return LexerState::Invalid;
    }
    consume();
  }

  auto string_literal = m_source.substr(
      start_string_literal, (m_position - start_string_literal) - 1);

  if (m_current_char != m_string_literal_stop_char) {
    m_current_type = TokenType::UnterminatedStringLiteral;
    return LexerState::Invalid;
  }

  consume();

  m_value = string_literal;
  m_current_type = TokenType::StringLiteral;

  return LexerState::Start;
}

LexerState Lexer::lexOperand() {
  size_t value_start = m_position - 1;

  if (match('>', '>', '>', '=')) {
    consume();
    consume();
    consume();
    consume();
    m_current_type = TokenType::UnsignedShiftRightEquals;
    return LexerState::Start;
  }

  if (m_position + 1 < m_source.length()) {
    if (auto it = s_three_char_tokens.find(m_source.substr(m_position - 1, 3));
        it != s_three_char_tokens.end()) {
      consume();
      consume();
      consume();
      m_current_type = it->second;
      return LexerState::Start;
    }
  }

  if (m_position < m_source.length()) {
    if (auto it = s_two_char_tokens.find(m_source.substr(m_position - 1, 2));
        it != s_two_char_tokens.end()) {
      consume();
      consume();
      m_current_type = it->second;
      return LexerState::Start;
    }
  }

  if (auto it = s_one_char_tokens.find(m_current_char);
      it != s_one_char_tokens.end()) {
    consume();
    m_current_type = it->second;
    return LexerState::Start;
  }

  m_message = "Unhandled";
  m_value = m_source.substr(value_start, m_position - value_start);
  m_current_type = TokenType::Invalid;
  return LexerState::Invalid;
}

template <typename Callback>
bool Lexer::match_numerical_literal_separator_followed_by(
    Callback callback) const {
  if (m_position >= m_source.length()) {
    return false;
  }

  return m_current_char == '_' && callback(m_source[m_position]);
}

void Lexer::consume() {
  if (is_eof()) {
    return;
  }

  if (is_line_terminator()) {
    m_line_number++;
    m_column_number = 1;
    m_current_state = LexerState::LineTerminator;
  } else if (is_unicode_character()) {
    std::cout << "Unicode(" << std::dec << m_line_number << ", "
              << m_column_number << "): "
              << "0x" << std::hex << std::setw(4) << std::setfill('0')
              << current_code_point() << std::endl;

    size_t char_size = 1;
    if ((m_current_char & 0b01000000) == 0) {
      m_hit_invalid_unicode_character = m_position;
    } else if ((m_current_char & 0b00100000) == 0) {
      char_size = 2;
    } else if ((m_current_char & 0b00010000) == 0) {
      char_size = 3;
    } else if ((m_current_char & 0b00001000) == 0) {
      char_size = 4;
    }

    --char_size;

    for (size_t i = m_position; i < m_position + char_size; i++) {
      if (i >= m_source.length() || (m_source[i] & 0b11000000) != 0b10000000) {
        m_hit_invalid_unicode_character = m_position;
        break;
      }
    }

    if (m_hit_invalid_unicode_character < m_source.length()) {
      m_position = m_source.length();
    } else {
      m_position += char_size;
    }

    if (is_eof()) {
      return;
    }

    m_column_number++;
  } else {
    m_column_number++;
  }

  m_current_char = m_source[m_position++];
}

bool Lexer::is_numeric_literal_start() {

  return is_ascii_digit(m_current_char) ||
         (match('.') && m_position < m_source.length() &&
          is_ascii_digit(m_position));
}

bool Lexer::is_unicode_character() {
  return (m_current_char & 0b10000000) != 0;
}

uint32_t Lexer::current_code_point() {
  static constexpr uint32_t REPLACEMENT_CHARACTER = 0xFFFD;

  if (m_position == 0) {
    return REPLACEMENT_CHARACTER;
  }

  // Unicode 1 byte
  if ((m_current_char & 0b10000000) == 0) {
    return m_current_char;
  }

  // Unicode 2 bytes
  if ((m_current_char & 0b00100000) == 0) {
    char c1_bits = m_current_char & 0b11111;
    char c2_bits = m_source[m_position] & 0b111111;

    return (static_cast<uint32_t>(c1_bits) << 6 |
            static_cast<uint32_t>(c2_bits));
  }

  // Unicode 3 bytes
  if ((m_current_char & 0b00010000) == 0) {
    char c1_bits = m_current_char & 0b11111;
    char c2_bits = m_source[m_position] & 0b111111;
    char c3_bits = m_source[m_position + 1] & 0b111111;

    return (static_cast<uint32_t>(c1_bits) << 12 |
            static_cast<uint32_t>(c2_bits) << 6 |
            static_cast<uint32_t>(c3_bits));
  }

  // Unicode 4 bytes
  if ((m_current_char & 0b00001000) == 0) {
    char c1_bits = m_current_char & 0b11111;
    char c2_bits = m_source[m_position] & 0b111111;
    char c3_bits = m_source[m_position + 1] & 0b111111;
    char c4_bits = m_source[m_position + 2] & 0b111111;

    return (static_cast<uint32_t>(c1_bits) << 18 |
            static_cast<uint32_t>(c2_bits) << 12 |
            static_cast<uint32_t>(c3_bits) << 6 |
            static_cast<uint32_t>(c4_bits));
  }

  assert(false);
}

bool Lexer::is_eof() {
  if (m_position < m_source.length()) {
    return false;
  }

  m_current_char = '\0';
  m_position = m_source.length() + 1;
  return true;
}

bool Lexer::is_whitespace() {
  if (m_current_char == SPACE || m_current_char == CHARACTER_TABULATION ||
      m_current_char == LINE_TABULATION || m_current_char == FORM_FEED) {
    return true;
  }

  if (!is_unicode_character()) {
    return false;
  }

  auto code_point = current_code_point();

  if (code_point == ZERO_WIDTH_NO_BREAK_SPACE || code_point == NO_BREAK_SPACE) {
    return true;
  }

  return false;
}

bool Lexer::is_valid_identifier_start() {
  return is_ascii_letter(m_current_char) || m_current_char == '$' ||
         m_current_char == '_';
}

bool Lexer::is_valid_identifier_part() {
  return is_ascii_letter(m_current_char) || is_ascii_digit(m_current_char) ||
         m_current_char == '$' ||
         (current_code_point() == ZERO_WIDTH_NON_JOINER) ||
         (current_code_point() == ZERO_WIDTH_JOINER);
}

bool Lexer::is_line_terminator() {
  if (m_current_char == LINE_FEED || m_current_char == CARRIAGE_RETURN) {
    return true;
  }

  if (!is_unicode_character()) {
    return false;
  }

  auto code_point = current_code_point();

  if (code_point == LINE_SEPARATOR || code_point == PARAGRAPH_SEPARATOR) {
    return true;
  }

  return false;
}

bool Lexer::match(char a) { return m_current_char == a; }

bool Lexer::match(char a, char b) {
  if (m_position >= m_source.length()) {
    return false;
  }

  return m_current_char == a && m_source[m_position] == b;
}

bool Lexer::match(char a, char b, char c) {
  if ((m_position + 1) >= m_source.length()) {
    return false;
  }

  return m_current_char == a && m_source[m_position] == b &&
         m_source[m_position + 1] == c;
}

bool Lexer::match(char a, char b, char c, char d) {
  if ((m_position + 2) >= m_source.length()) {
    return false;
  }

  return m_current_char == a && m_source[m_position] == b &&
         m_source[m_position + 1] == c && m_source[m_position + 2] == d;
}
} // namespace SN::LibJS