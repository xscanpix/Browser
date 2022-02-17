#pragma once

#include "LibBase/Base.h"

namespace LibJS {
class Source {
public:
  Source();
  explicit Source(std::string const &source_text);

  static Source from_path(std::string const &source_path);
  static Source from_text(std::string const &source_text);

  [[nodiscard]] uint32_t length() const { return m_length; };

  [[nodiscard]] std::string substr(const size_t start,
                                          const size_t n) const {
    return m_source_text.substr(start, n);
  }

  char operator[](const uint32_t index) const {
    assert(index < m_length);

    return m_source_text[index];
  }

private:
  const std::string m_source_text;
  const uint32_t m_length;
};
} // namespace LibJS
