#pragma once

#include "LibBase/Base.h"

namespace SN::LibJS {
static constexpr uint32_t ZERO_WIDTH_NON_JOINER{0x200C};
static constexpr uint32_t ZERO_WIDTH_JOINER{0x200D};
static constexpr uint32_t ZERO_WIDTH_NO_BREAK_SPACE{0xFEFF};
static constexpr uint32_t CHARACTER_TABULATION{0x0009};
static constexpr uint32_t LINE_FEED{0x000A};
static constexpr uint32_t LINE_TABULATION{0x000B};
static constexpr uint32_t FORM_FEED{0x000C};
static constexpr uint32_t CARRIAGE_RETURN{0x000D};
static constexpr uint32_t LINE_SEPARATOR{0x2028};
static constexpr uint32_t PARAGRAPH_SEPARATOR{0x2029};
static constexpr uint32_t SPACE{0x0020};
static constexpr uint32_t NO_BREAK_SPACE{0x00A0};
static constexpr uint32_t ORGHAM_SPACE_MARK{0x1680};
static constexpr uint32_t EN_QUAD{0x2000};
static constexpr uint32_t EM_QUAD{0x2001};
static constexpr uint32_t EN_SPACE{0x2002};
static constexpr uint32_t EM_SPACE{0x2003};
static constexpr uint32_t THREE_PER_EM_SPACE{0x2004};
static constexpr uint32_t FOUR_PER_EM_SPACE{0x2005};
static constexpr uint32_t SIX_PER_EM_SPACE{0x2006};
static constexpr uint32_t FIGURE_SPACE{0x2007};
static constexpr uint32_t PUNCTUATION_SPACE{0x2008};
static constexpr uint32_t THIN_SPACE{0x2009};
static constexpr uint32_t HAIR_SPACE{0x200A};
static constexpr uint32_t NARROW_NO_BREAK_SPACE{0x202F};
static constexpr uint32_t MEDIUM_MATHEMATICAL_SPACE{0x205F};
static constexpr uint32_t IDEOGRAPHIC_SPACE{0x3000};

#define ENUMERATE_JS_TOKENS                                                    \
  __ENUMERATE_JS_TOKEN(Ampersand, Operator)                                    \
  __ENUMERATE_JS_TOKEN(AmpersandEquals, Operator)                              \
  __ENUMERATE_JS_TOKEN(Arrow, Operator)                                        \
  __ENUMERATE_JS_TOKEN(Asterisk, Operator)                                     \
  __ENUMERATE_JS_TOKEN(AsteriskEquals, Operator)                               \
  __ENUMERATE_JS_TOKEN(Async, Keyword)                                         \
  __ENUMERATE_JS_TOKEN(Await, Keyword)                                         \
  __ENUMERATE_JS_TOKEN(BigIntLiteral, Number)                                  \
  __ENUMERATE_JS_TOKEN(BoolLiteral, Keyword)                                   \
  __ENUMERATE_JS_TOKEN(BracketClose, Punctuation)                              \
  __ENUMERATE_JS_TOKEN(BracketOpen, Punctuation)                               \
  __ENUMERATE_JS_TOKEN(Break, Keyword)                                         \
  __ENUMERATE_JS_TOKEN(Caret, Operator)                                        \
  __ENUMERATE_JS_TOKEN(CaretEquals, Operator)                                  \
  __ENUMERATE_JS_TOKEN(Case, ControlKeyword)                                   \
  __ENUMERATE_JS_TOKEN(Catch, ControlKeyword)                                  \
  __ENUMERATE_JS_TOKEN(Class, Keyword)                                         \
  __ENUMERATE_JS_TOKEN(Colon, Punctuation)                                     \
  __ENUMERATE_JS_TOKEN(Comma, Punctuation)                                     \
  __ENUMERATE_JS_TOKEN(Const, Keyword)                                         \
  __ENUMERATE_JS_TOKEN(Continue, ControlKeyword)                               \
  __ENUMERATE_JS_TOKEN(CurlyClose, Punctuation)                                \
  __ENUMERATE_JS_TOKEN(CurlyOpen, Punctuation)                                 \
  __ENUMERATE_JS_TOKEN(Debugger, Keyword)                                      \
  __ENUMERATE_JS_TOKEN(Default, ControlKeyword)                                \
  __ENUMERATE_JS_TOKEN(Delete, Keyword)                                        \
  __ENUMERATE_JS_TOKEN(Do, ControlKeyword)                                     \
  __ENUMERATE_JS_TOKEN(DoubleAmpersand, Operator)                              \
  __ENUMERATE_JS_TOKEN(DoubleAmpersandEquals, Operator)                        \
  __ENUMERATE_JS_TOKEN(DoubleAsterisk, Operator)                               \
  __ENUMERATE_JS_TOKEN(DoubleAsteriskEquals, Operator)                         \
  __ENUMERATE_JS_TOKEN(DoublePipe, Operator)                                   \
  __ENUMERATE_JS_TOKEN(DoublePipeEquals, Operator)                             \
  __ENUMERATE_JS_TOKEN(DoubleQuestionMark, Operator)                           \
  __ENUMERATE_JS_TOKEN(DoubleQuestionMarkEquals, Operator)                     \
  __ENUMERATE_JS_TOKEN(Else, ControlKeyword)                                   \
  __ENUMERATE_JS_TOKEN(Enum, Keyword)                                          \
  __ENUMERATE_JS_TOKEN(Eof, Invalid)                                           \
  __ENUMERATE_JS_TOKEN(Equals, Operator)                                       \
  __ENUMERATE_JS_TOKEN(EqualsEquals, Operator)                                 \
  __ENUMERATE_JS_TOKEN(EqualsEqualsEquals, Operator)                           \
  __ENUMERATE_JS_TOKEN(EscapedKeyword, Identifier)                             \
  __ENUMERATE_JS_TOKEN(ExclamationMark, Operator)                              \
  __ENUMERATE_JS_TOKEN(ExclamationMarkEquals, Operator)                        \
  __ENUMERATE_JS_TOKEN(ExclamationMarkEqualsEquals, Operator)                  \
  __ENUMERATE_JS_TOKEN(Export, Keyword)                                        \
  __ENUMERATE_JS_TOKEN(Extends, Keyword)                                       \
  __ENUMERATE_JS_TOKEN(Finally, ControlKeyword)                                \
  __ENUMERATE_JS_TOKEN(For, ControlKeyword)                                    \
  __ENUMERATE_JS_TOKEN(Function, Keyword)                                      \
  __ENUMERATE_JS_TOKEN(GreaterThan, Operator)                                  \
  __ENUMERATE_JS_TOKEN(GreaterThanEquals, Operator)                            \
  __ENUMERATE_JS_TOKEN(Identifier, Identifier)                                 \
  __ENUMERATE_JS_TOKEN(If, ControlKeyword)                                     \
  __ENUMERATE_JS_TOKEN(Implements, Keyword)                                    \
  __ENUMERATE_JS_TOKEN(Import, Keyword)                                        \
  __ENUMERATE_JS_TOKEN(In, Keyword)                                            \
  __ENUMERATE_JS_TOKEN(Instanceof, Keyword)                                    \
  __ENUMERATE_JS_TOKEN(Interface, Keyword)                                     \
  __ENUMERATE_JS_TOKEN(Invalid, Invalid)                                       \
  __ENUMERATE_JS_TOKEN(LessThan, Operator)                                     \
  __ENUMERATE_JS_TOKEN(LessThanEquals, Operator)                               \
  __ENUMERATE_JS_TOKEN(Let, Keyword)                                           \
  __ENUMERATE_JS_TOKEN(LineTerminator, LineTerminator)                         \
  __ENUMERATE_JS_TOKEN(Minus, Operator)                                        \
  __ENUMERATE_JS_TOKEN(MinusEquals, Operator)                                  \
  __ENUMERATE_JS_TOKEN(MinusMinus, Operator)                                   \
  __ENUMERATE_JS_TOKEN(New, Keyword)                                           \
  __ENUMERATE_JS_TOKEN(NullLiteral, Keyword)                                   \
  __ENUMERATE_JS_TOKEN(NumericLiteral, Number)                                 \
  __ENUMERATE_JS_TOKEN(Package, Keyword)                                       \
  __ENUMERATE_JS_TOKEN(ParenClose, Punctuation)                                \
  __ENUMERATE_JS_TOKEN(ParenOpen, Punctuation)                                 \
  __ENUMERATE_JS_TOKEN(Percent, Operator)                                      \
  __ENUMERATE_JS_TOKEN(PercentEquals, Operator)                                \
  __ENUMERATE_JS_TOKEN(Period, Operator)                                       \
  __ENUMERATE_JS_TOKEN(Pipe, Operator)                                         \
  __ENUMERATE_JS_TOKEN(PipeEquals, Operator)                                   \
  __ENUMERATE_JS_TOKEN(Plus, Operator)                                         \
  __ENUMERATE_JS_TOKEN(PlusEquals, Operator)                                   \
  __ENUMERATE_JS_TOKEN(PlusPlus, Operator)                                     \
  __ENUMERATE_JS_TOKEN(Private, Keyword)                                       \
  __ENUMERATE_JS_TOKEN(PrivateIdentifier, Identifier)                          \
  __ENUMERATE_JS_TOKEN(Protected, Keyword)                                     \
  __ENUMERATE_JS_TOKEN(Public, Keyword)                                        \
  __ENUMERATE_JS_TOKEN(QuestionMark, Operator)                                 \
  __ENUMERATE_JS_TOKEN(QuestionMarkPeriod, Operator)                           \
  __ENUMERATE_JS_TOKEN(RegexFlags, String)                                     \
  __ENUMERATE_JS_TOKEN(RegexLiteral, String)                                   \
  __ENUMERATE_JS_TOKEN(Return, ControlKeyword)                                 \
  __ENUMERATE_JS_TOKEN(Semicolon, Punctuation)                                 \
  __ENUMERATE_JS_TOKEN(ShiftLeft, Operator)                                    \
  __ENUMERATE_JS_TOKEN(ShiftLeftEquals, Operator)                              \
  __ENUMERATE_JS_TOKEN(ShiftRight, Operator)                                   \
  __ENUMERATE_JS_TOKEN(ShiftRightEquals, Operator)                             \
  __ENUMERATE_JS_TOKEN(Slash, Operator)                                        \
  __ENUMERATE_JS_TOKEN(SlashEquals, Operator)                                  \
  __ENUMERATE_JS_TOKEN(Static, Keyword)                                        \
  __ENUMERATE_JS_TOKEN(StringLiteral, String)                                  \
  __ENUMERATE_JS_TOKEN(Super, Keyword)                                         \
  __ENUMERATE_JS_TOKEN(Switch, ControlKeyword)                                 \
  __ENUMERATE_JS_TOKEN(TemplateLiteralEnd, String)                             \
  __ENUMERATE_JS_TOKEN(TemplateLiteralExprEnd, Punctuation)                    \
  __ENUMERATE_JS_TOKEN(TemplateLiteralExprStart, Punctuation)                  \
  __ENUMERATE_JS_TOKEN(TemplateLiteralStart, String)                           \
  __ENUMERATE_JS_TOKEN(TemplateLiteralString, String)                          \
  __ENUMERATE_JS_TOKEN(This, Keyword)                                          \
  __ENUMERATE_JS_TOKEN(Throw, ControlKeyword)                                  \
  __ENUMERATE_JS_TOKEN(Tilde, Operator)                                        \
  __ENUMERATE_JS_TOKEN(TripleDot, Operator)                                    \
  __ENUMERATE_JS_TOKEN(Try, ControlKeyword)                                    \
  __ENUMERATE_JS_TOKEN(Typeof, Keyword)                                        \
  __ENUMERATE_JS_TOKEN(UnsignedShiftRight, Operator)                           \
  __ENUMERATE_JS_TOKEN(UnsignedShiftRightEquals, Operator)                     \
  __ENUMERATE_JS_TOKEN(UnterminatedRegexLiteral, String)                       \
  __ENUMERATE_JS_TOKEN(UnterminatedStringLiteral, String)                      \
  __ENUMERATE_JS_TOKEN(UnterminatedTemplateLiteral, String)                    \
  __ENUMERATE_JS_TOKEN(Var, Keyword)                                           \
  __ENUMERATE_JS_TOKEN(Void, Keyword)                                          \
  __ENUMERATE_JS_TOKEN(While, ControlKeyword)                                  \
  __ENUMERATE_JS_TOKEN(With, ControlKeyword)                                   \
  __ENUMERATE_JS_TOKEN(Yield, ControlKeyword)

enum class TokenCategory {
  Invalid,
  Number,
  String,
  Punctuation,
  Operator,
  Keyword,
  ControlKeyword,
  Identifier,
  LineTerminator,
};

enum class TokenType {
#define __ENUMERATE_JS_TOKEN(type, category) type,
  ENUMERATE_JS_TOKENS
#undef __ENUMERATE_JS_TOKEN
};

class Token {
public:
  Token() = default;
  Token(TokenType type, std::string message, std::string value)
      : m_type(type), m_message(std::move(message)),
        m_value(std::move(value)){};

  [[nodiscard]] std::string message() const { return m_message; }
  [[nodiscard]] std::string value() const { return m_value; }

  TokenType type() { return m_type; }

  static const char *name(TokenType);
  [[nodiscard]] const char *name() const;

  static TokenCategory category(TokenType);
  [[nodiscard]] TokenCategory category() const;

  friend std::ostream &operator<<(std::ostream &os, const Token &token);

private:
  TokenType m_type{TokenType::Invalid};
  std::string m_message;
  std::string m_value;
};

std::ostream &operator<<(std::ostream &os, const Token &token);
} // namespace SN::LibJS
