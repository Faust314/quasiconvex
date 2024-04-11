#pragma once

#include "types.hpp"

#include <string>
#include <cstdint>
#include <fstream>

namespace aux::format {

std::string uint8_t_to_string_16 (uint8_t a);


void set_precision (std::fstream & ofs, precision_t const precision);
template<typename T>
std::string double_to_string (T const x, precision_t const precision);

} // namespace aux::format