#pragma once

#include "LibBase/Base.h"

namespace SN::LibJS
{
  class Source
  {
  public:
    Source(const std::string source_path);

    uint32_t length() const { return m_length; };

    u8 at(uint32_t index) const
    {
      assert(index < m_length);

      return m_source_text[index];
    };

    std::string substr(size_t start, size_t n)
    {
      return m_source_text.substr(start, n);
    }

    u8 operator[](uint32_t index)
    {
      assert(index < m_length);

      return m_source_text[index];
    }

  private:
    std::string m_source_text{};
    uint32_t m_length;
  };
}