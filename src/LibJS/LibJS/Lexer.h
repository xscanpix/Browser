#pragma once

#include <sstream>
#include <vector>
#include <unordered_map>

#include "LibBase/Base.h"

#include "LibJS/Source.h"
#include "LibJS/Token.h"

namespace SN::LibJS
{
  class Lexer
  {
  public:
    Lexer(Source source);
    Token next();

  private:
    bool is_eof();
    bool is_unicode_character();
    bool is_ascii();
    bool is_latin_letter();
    bool is_digit();

    bool is_valid_identifier_start();
    bool is_valid_identifier_part();

    bool is_whitespace();
    bool is_line_terminator();

    u32 current_code_point();

    bool match(char a);
    bool match(char a, char b);
    bool match(char a, char b, char c);
    bool match(char a, char b, char c, char d);

    void consume();

    bool m_is_eof{false};
    char m_current_char;
    size_t m_start{0};
    size_t m_position{1};
    Source m_source;

    TokenType m_token_type{TokenType::Eof};
    std::string m_message{};

    bool m_unterminated_comment{false};
    size_t m_hit_invalid_unicode_character;

    size_t m_line_number{1};
    size_t m_column_number{1};

    std::unordered_map<std::string, TokenType> m_keywords{};
    std::unordered_map<char, TokenType> m_one_char_tokens{};
    std::unordered_map<std::string, TokenType> m_two_char_tokens{};
    std::unordered_map<std::string, TokenType> m_three_char_tokens{};
  };
}