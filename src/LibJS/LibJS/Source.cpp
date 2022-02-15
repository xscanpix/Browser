#include "LibJS/Source.h"

#include <fstream>
#include <iostream>

namespace SN::LibJS {
Source::Source(const std::string source_text)
    : m_source_text(source_text), m_length(source_text.length()) {}

Source Source::from_path(const std::string source_path) {
  if (source_path.empty()) {
    std::cout << "[Error] - Source: Source path is empty." << std::endl;
    return {""};
  }

  auto input_stream = std::ifstream(source_path);

  if (!input_stream.is_open()) {
    std::cout << "[Error] - Source: Could not open file." << std::endl;
    return {""};
  }

  return {std::string((std::istreambuf_iterator<char>(input_stream)),
                      std::istreambuf_iterator<char>())};
}

Source Source::from_text(const std::string source_text) {
  return {source_text};
}
} // namespace SN::LibJS