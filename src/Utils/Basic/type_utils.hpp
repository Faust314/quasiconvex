#pragma once

#include <string>

namespace aux::types {

std::string removing_leading_zeros (std::string const & number);
std::string lead_zeros (int number, int zeros_count);

std::string to_string (double x);

bool is_real (std::string const & s);

} // namespace aux::types