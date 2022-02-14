#include "LibJS/Token.h"

namespace SN::LibJS
{
  const char *Token::name(TokenType type)
  {
    switch (type)
    {
#define __ENUMERATE_JS_TOKEN(type, category) \
  case TokenType::type:                      \
    return #type;
      ENUMERATE_JS_TOKENS
#undef __ENUMERATE_JS_TOKEN
    default:
      assert(false);
      return "<Unknown>";
    }
  }

  const char *Token::name() const
  {
    return name(m_type);
  }

  TokenCategory Token::category(TokenType type)
  {
    switch (type)
    {
#define __ENUMERATE_JS_TOKEN(type, category) \
  case TokenType::type:                      \
    return TokenCategory::category;
      ENUMERATE_JS_TOKENS
#undef __ENUMERATE_JS_TOKEN
    default:
      assert(false);
    }
  }

  TokenCategory Token::category() const
  {
    return category(m_type);
  }
}