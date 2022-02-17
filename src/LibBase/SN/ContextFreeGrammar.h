#pragma once

#include "LibBase/Base.h"

#include <unordered_map>
#include <vector>

namespace SN {

enum class RulePartType { Terminal, NonTerminal };

class CFGSymbol {
public:
  CFGSymbol() = delete;

  explicit CFGSymbol(const RulePartType type, std::string value)
      : m_type(type), m_value(std::move(value)){};

  static CFGSymbol create_terminal_symbol(std::string value);
  static CFGSymbol create_non_terminal_symbol(std::string value);

  [[nodiscard]] constexpr RulePartType type() const { return m_type; };
  [[nodiscard]] std::string value() const { return m_value; };

  [[nodiscard]] constexpr bool is_terminal() const {
    return m_type == RulePartType::Terminal;
  };
  [[nodiscard]] constexpr bool is_non_terminal() const {
    return m_type == RulePartType::NonTerminal;
  };

  friend std::ostream &operator<<(std::ostream &os, const CFGSymbol &symbol);

private:
  const RulePartType m_type;
  const std::string m_value;
};

std::ostream &operator<<(std::ostream &os, const CFGSymbol &symbol) {
  os << symbol.m_value;

  return os;
}

class CFGRule {
public:
  CFGRule() = delete;
  CFGRule(CFGSymbol *left, std::vector<CFGSymbol *> right)
      : m_left(left), m_right(std::move(right)){};

  friend std::ostream &operator<<(std::ostream &os, const CFGRule &rule);

  [[nodiscard]] const CFGSymbol &left() const { return *m_left; };
  [[nodiscard]] const std::vector<CFGSymbol *> &right() const {
    return m_right;
  };

private:
  CFGSymbol *m_left;
  std::vector<CFGSymbol *> m_right;
};

std::ostream &operator<<(std::ostream &os, const CFGRule &rule) {
  os << rule.left() << " -->";

  for (auto symbol : rule.right()) {
    os << " " << *symbol;
  }

  os << "\n";

  return os;
}

class ContextFreeGrammar {
public:
  CFGSymbol *add_symbol(CFGSymbol symbol);
  CFGRule *add_rule(CFGSymbol *left, std::vector<CFGSymbol *> right);

private:
  std::unordered_map<std::string, CFGSymbol> m_symbols;
  std::unordered_map<std::string, CFGRule> m_rules;
};

} // namespace SN