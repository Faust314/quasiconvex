#pragma once

#include "format_utils.hpp"

#include <sstream>
#include <iomanip>
#include <string>

namespace aux::format {

template <typename T>
std::string double_to_string (T const x, precision_t const precision) {
	std::ostringstream stream;
	stream << std::fixed << std::setprecision(static_cast<int>(precision)) << x;
	return stream.str();
}

} // namespace aux::format 