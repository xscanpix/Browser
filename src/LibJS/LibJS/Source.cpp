#include "LibJS/Source.h"

#include <fstream>
#include <iostream>

namespace LibJS {
Source::Source() : m_length(0) {}

Source::Source(std::string const &source_text)
    : m_source_text(source_text), m_length(source_text.length()) {}

Source Source::from_path(std::string const &source_path) {
  if (source_path.empty()) {
    std::cout << "[Error] - Source: Source path is empty." << std::endl;
    return {};
  }

  auto input_stream = std::ifstream(source_path);

  if (!input_stream.is_open()) {
    std::cout << "[Error] - Source: Could not open file." << std::endl;
    return {};
  }

  auto source_text = std::string((std::istreambuf_iterator<char>(input_stream)),
                                 std::istreambuf_iterator<char>());

  return Source(source_text);
}

Source Source::from_text(std::string const &source_text) {
  return Source(source_text);
}
} // namespace LibJS
