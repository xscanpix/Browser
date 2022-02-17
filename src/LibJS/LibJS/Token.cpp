#include "LibJS/Token.h"

namespace LibJS {

std::ostream &operator<<(std::ostream &os, const Token &token) {
  os << "Type: '" << token.name() << "'";

  if (!token.message().empty()) {
    os << " | Message: '" << token.message() << "'";
  }

  if (!token.value().empty()) {
    os << " | Value: '" << token.value() << "'";
  }

  return os;
}

const char *Token::name(TokenType type) {
  switch (type) {
#define __ENUMERATE_JS_TOKEN(type, category)                                   \
  case TokenType::type:                                                        \
    return #type;
    ENUMERATE_JS_TOKENS
#undef __ENUMERATE_JS_TOKEN
  default:
    assert(false);
  }
}

const char *Token::name() const { return name(m_type); }

TokenCategory Token::category(TokenType type) {
  switch (type) {
#define __ENUMERATE_JS_TOKEN(type, category)                                   \
  case TokenType::type:                                                        \
    return TokenCategory::category;
    ENUMERATE_JS_TOKENS
#undef __ENUMERATE_JS_TOKEN
  default:
    assert(false);
  }
}

TokenCategory Token::category() const { return category(m_type); }
} // namespace LibJS
