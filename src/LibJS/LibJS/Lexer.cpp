#include "LibJS/Lexer.h"

#include <algorithm>
#include <assert.h>
#include <iomanip>
#include <iostream>

namespace SN::LibJS {
Lexer::Lexer(Source source)
    : m_source(source), m_current_char(source[0]),
      m_hit_invalid_unicode_character(source.length() + 1) {
  if (m_keywords.empty()) {
    m_keywords.emplace("await", TokenType::Await);
    m_keywords.emplace("break", TokenType::Break);
    m_keywords.emplace("case", TokenType::Case);
    m_keywords.emplace("catch", TokenType::Catch);
    m_keywords.emplace("class", TokenType::Class);
    m_keywords.emplace("const", TokenType::Const);
    m_keywords.emplace("continue", TokenType::Continue);
    m_keywords.emplace("debugger", TokenType::Debugger);
    m_keywords.emplace("default", TokenType::Default);
    m_keywords.emplace("delete", TokenType::Delete);
    m_keywords.emplace("do", TokenType::Do);
    m_keywords.emplace("else", TokenType::Else);
    m_keywords.emplace("enum", TokenType::Enum);
    m_keywords.emplace("export", TokenType::Export);
    m_keywords.emplace("extends", TokenType::Extends);
    m_keywords.emplace("false", TokenType::BoolLiteral);
    m_keywords.emplace("finally", TokenType::Finally);
    m_keywords.emplace("for", TokenType::For);
    m_keywords.emplace("function", TokenType::Function);
    m_keywords.emplace("if", TokenType::If);
    m_keywords.emplace("import", TokenType::Import);
    m_keywords.emplace("in", TokenType::In);
    m_keywords.emplace("instanceof", TokenType::Instanceof);
    m_keywords.emplace("new", TokenType::New);
    m_keywords.emplace("null", TokenType::NullLiteral);
    m_keywords.emplace("return", TokenType::Return);
    m_keywords.emplace("super", TokenType::Super);
    m_keywords.emplace("switch", TokenType::Switch);
    m_keywords.emplace("this", TokenType::This);
    m_keywords.emplace("throw", TokenType::Throw);
    m_keywords.emplace("true", TokenType::BoolLiteral);
    m_keywords.emplace("try", TokenType::Try);
    m_keywords.emplace("typeof", TokenType::Typeof);
    m_keywords.emplace("var", TokenType::Var);
    m_keywords.emplace("void", TokenType::Void);
    m_keywords.emplace("while", TokenType::While);
    m_keywords.emplace("with", TokenType::With);
    m_keywords.emplace("yield", TokenType::Yield);
  }

  if (m_one_char_tokens.empty()) {
    m_one_char_tokens.emplace('&', TokenType::Ampersand);
    m_one_char_tokens.emplace('*', TokenType::Asterisk);
    m_one_char_tokens.emplace('[', TokenType::BracketOpen);
    m_one_char_tokens.emplace(']', TokenType::BracketClose);
    m_one_char_tokens.emplace('^', TokenType::Caret);
    m_one_char_tokens.emplace(':', TokenType::Colon);
    m_one_char_tokens.emplace(',', TokenType::Comma);
    m_one_char_tokens.emplace('{', TokenType::CurlyOpen);
    m_one_char_tokens.emplace('}', TokenType::CurlyClose);
    m_one_char_tokens.emplace('=', TokenType::Equals);
    m_one_char_tokens.emplace('!', TokenType::ExclamationMark);
    m_one_char_tokens.emplace('-', TokenType::Minus);
    m_one_char_tokens.emplace('(', TokenType::ParenOpen);
    m_one_char_tokens.emplace(')', TokenType::ParenClose);
    m_one_char_tokens.emplace('%', TokenType::Percent);
    m_one_char_tokens.emplace('.', TokenType::Period);
    m_one_char_tokens.emplace('|', TokenType::Pipe);
    m_one_char_tokens.emplace('+', TokenType::Plus);
    m_one_char_tokens.emplace('?', TokenType::QuestionMark);
    m_one_char_tokens.emplace(';', TokenType::Semicolon);
    m_one_char_tokens.emplace('/', TokenType::Slash);
    m_one_char_tokens.emplace('~', TokenType::Tilde);
    m_one_char_tokens.emplace('<', TokenType::LessThan);
    m_one_char_tokens.emplace('>', TokenType::GreaterThan);
  }

  if (m_two_char_tokens.empty()) {
    m_two_char_tokens.emplace("=>", TokenType::Arrow);
    m_two_char_tokens.emplace("+=", TokenType::PlusEquals);
    m_two_char_tokens.emplace("-=", TokenType::MinusEquals);
    m_two_char_tokens.emplace("*=", TokenType::AsteriskEquals);
    m_two_char_tokens.emplace("/=", TokenType::SlashEquals);
    m_two_char_tokens.emplace("%=", TokenType::PercentEquals);
    m_two_char_tokens.emplace("&=", TokenType::AmpersandEquals);
    m_two_char_tokens.emplace("|=", TokenType::PipeEquals);
    m_two_char_tokens.emplace("^=", TokenType::CaretEquals);
    m_two_char_tokens.emplace("&&", TokenType::DoubleAmpersand);
    m_two_char_tokens.emplace("||", TokenType::DoublePipe);
    m_two_char_tokens.emplace("??", TokenType::DoubleQuestionMark);
    m_two_char_tokens.emplace("**", TokenType::DoubleAsterisk);
    m_two_char_tokens.emplace("==", TokenType::EqualsEquals);
    m_two_char_tokens.emplace("<=", TokenType::LessThanEquals);
    m_two_char_tokens.emplace(">=", TokenType::GreaterThanEquals);
    m_two_char_tokens.emplace("!=", TokenType::ExclamationMarkEquals);
    m_two_char_tokens.emplace("--", TokenType::MinusMinus);
    m_two_char_tokens.emplace("++", TokenType::PlusPlus);
    m_two_char_tokens.emplace("<<", TokenType::ShiftLeft);
    m_two_char_tokens.emplace(">>", TokenType::ShiftRight);
    m_two_char_tokens.emplace("?.", TokenType::QuestionMarkPeriod);
  }

  if (m_two_char_tokens.empty()) {
    m_three_char_tokens.emplace("===", TokenType::EqualsEqualsEquals);
    m_three_char_tokens.emplace("!==", TokenType::ExclamationMarkEqualsEquals);
    m_three_char_tokens.emplace("**=", TokenType::DoubleAsteriskEquals);
    m_three_char_tokens.emplace("<<=", TokenType::ShiftLeftEquals);
    m_three_char_tokens.emplace(">>=", TokenType::ShiftRightEquals);
    m_three_char_tokens.emplace("&&=", TokenType::DoubleAmpersandEquals);
    m_three_char_tokens.emplace("||=", TokenType::DoublePipeEquals);
    m_three_char_tokens.emplace("\?\?=", TokenType::DoubleQuestionMarkEquals);
    m_three_char_tokens.emplace(">>>", TokenType::UnsignedShiftRight);
    m_three_char_tokens.emplace("...", TokenType::TripleDot);
  }
}

Token Lexer::next() {
  // Consume whitespace and comments
  while (true) {
    if (is_line_terminator()) {
      do {
        consume();
      } while (is_line_terminator());
    } else if (is_whitespace()) {
      do {
        consume();
      } while (is_whitespace());
    } else if (match('/', '/')) {
      consume();
      do {
        consume();
      } while (!is_eof() && !is_line_terminator());
    } else if (match('/', '*')) {
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
    } else {
      break;
    }
  }

  if (is_eof()) {
    if (m_unterminated_comment) {
      return {TokenType::Invalid, "Unterminated comment", ""};
    }
    return {TokenType::Eof, "End of file", ""};
  } else if (is_valid_identifier_start()) {
    size_t m_value_start = m_position;

    do {
      consume();
    } while (is_valid_identifier_part());

    auto identifier =
        m_source.substr(m_value_start - 1, m_position - m_value_start);

    if (auto it = m_keywords.find(identifier); it != m_keywords.end()) {
      return {it->second, "", ""};
    }

    return {TokenType::Identifier, "", identifier};
  } else if (match('\'') || match('"')) {
    char m_string_literal_stop_char = m_current_char;

    size_t start_string_literal = m_position;

    consume();

    while (!is_eof() && m_current_char != m_string_literal_stop_char &&
           m_current_char != LINE_FEED && m_current_char != CARRIAGE_RETURN) {
      if (m_current_char == '\\') {
        return {TokenType::Invalid, "Unhandled", ""};
      }
      consume();
    }

    auto string_literal = m_source.substr(start_string_literal - 1,
                                          m_position - start_string_literal);

    if (m_current_char != m_string_literal_stop_char) {
      return {TokenType::UnterminatedStringLiteral, string_literal, ""};
    }

    consume();

    return {TokenType::StringLiteral, "", string_literal};
  } else {
    if (match('>', '>', '>', '=')) {
      consume();
      consume();
      consume();
      consume();
      return {TokenType::UnsignedShiftRightEquals, "", ""};
    }

    if (m_position + 1 < m_source.length()) {
      if (auto it =
              m_three_char_tokens.find(m_source.substr(m_position - 1, 3));
          it != m_three_char_tokens.end()) {
        consume();
        consume();
        consume();
        return {it->second, "", ""};
      }
    }

    if (m_position < m_source.length()) {
      if (auto it = m_two_char_tokens.find(m_source.substr(m_position - 1, 2));
          it != m_two_char_tokens.end()) {
        consume();
        consume();
        return {it->second, "", ""};
      }
    }

    if (auto it = m_one_char_tokens.find(m_current_char);
        it != m_one_char_tokens.end()) {
      consume();
      return {it->second, "", ""};
    }
  }

  std::cout << m_current_char << std::endl;
  return {m_token_type, m_message, ""};
}

void Lexer::consume() {
  auto did_reach_eof = [this] {
    if (m_position < m_source.length()) {
      return false;
    }

    m_current_char = '\0';
    m_position = m_source.length() + 1;
    m_is_eof = true;
    return true;
  };

  if (did_reach_eof()) {
    return;
  }

  if (is_line_terminator()) {
    std::cout << "Line terminator(" << std::dec << m_line_number << ", "
              << m_column_number << "): "
              << "0x" << std::hex << std::setw(4) << std::setfill('0')
              << (u32)m_current_char << std::endl;
    m_line_number++;
    m_column_number = 1;
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

    if (did_reach_eof()) {
      return;
    }

    m_column_number++;
  } else {
    m_column_number++;
  }

  m_current_char = m_source[m_position++];
}

bool Lexer::is_unicode_character() {
  return (m_current_char & 0b10000000) != 0;
}

u32 Lexer::current_code_point() {
  static constexpr u32 REPLACEMENT_CHARACTER = 0xFFFD;

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

    return (static_cast<u32>(c1_bits) << 6 | static_cast<u32>(c2_bits));
  }

  // Unicode 3 bytes
  if ((m_current_char & 0b00010000) == 0) {
    char c1_bits = m_current_char & 0b11111;
    char c2_bits = m_source[m_position] & 0b111111;
    char c3_bits = m_source[m_position + 1] & 0b111111;

    return (static_cast<u32>(c1_bits) << 12 | static_cast<u32>(c2_bits) << 6 |
            static_cast<u32>(c3_bits));
  }

  // Unicode 4 bytes
  if ((m_current_char & 0b00001000) == 0) {
    char c1_bits = m_current_char & 0b11111;
    char c2_bits = m_source[m_position] & 0b111111;
    char c3_bits = m_source[m_position + 1] & 0b111111;
    char c4_bits = m_source[m_position + 2] & 0b111111;

    return (static_cast<u32>(c1_bits) << 18 | static_cast<u32>(c2_bits) << 12 |
            static_cast<u32>(c3_bits) << 6 | static_cast<u32>(c4_bits));
  }

  assert(false);
}

bool Lexer::is_eof() { return m_is_eof; }

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

bool Lexer::is_latin_letter() {
  return (m_current_char >= 'a' && m_current_char <= 'z') ||
         (m_current_char >= 'A' && m_current_char <= 'Z');
}

bool Lexer::is_digit() {
  return (m_current_char >= '0' && m_current_char <= '9');
}

bool Lexer::is_valid_identifier_start() {
  return is_latin_letter() || m_current_char == '$' || m_current_char == '_';
}

bool Lexer::is_valid_identifier_part() {
  return is_latin_letter() || is_digit() || m_current_char == '$' ||
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