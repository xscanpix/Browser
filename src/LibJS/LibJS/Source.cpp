#include "LibJS/Source.h"

#include <iostream>
#include <fstream>

namespace SN::LibJS
{
  Source::Source(const std::string source_path)
  {
    if (source_path.empty())
    {
      std::cout << "[Error] - Source: Source path is empty." << std::endl;
      return;
    }

    auto input_stream = std::ifstream(source_path);

    if (!input_stream.is_open())
    {
      std::cout << "[Error] - Source: Could not open file." << std::endl;
      return;
    }

    m_source_text = std::string((std::istreambuf_iterator<char>(input_stream)), std::istreambuf_iterator<char>());
    m_length = m_source_text.length();
  }
}