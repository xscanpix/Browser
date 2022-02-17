#include "SN/ContextFreeGrammar.h"

namespace SN {
CFGSymbol *ContextFreeGrammar::add_symbol(CFGSymbol symbol) {
  // FIXME: Check if symbol already exists.
  return &m_symbols.emplace(symbol.value(), std::move(symbol)).first->second;
}

CFGRule *ContextFreeGrammar::add_rule(CFGSymbol *left,
                                      std::vector<CFGSymbol *> right) {
  // FIXME: Check if rule already exists.
  return &m_rules.emplace(left->value(), CFGRule(left, {std::move(right)}))
              .first->second;
}

CFGSymbol CFGSymbol::create_terminal_symbol(std::string value) {
  return CFGSymbol(RulePartType::Terminal, std::move(value));
}
CFGSymbol CFGSymbol::create_non_terminal_symbol(std::string value) {
  return CFGSymbol(RulePartType::NonTerminal, std::move(value));
}

} // namespace SN