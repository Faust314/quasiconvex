#pragma once

#include "format_utils.hpp"

#include <iomanip>

namespace aux::format {

template <typename T>
std::string double_to_string (T const x, precision_t const precision) {
	std::stringstream stream;
	stream << std::fixed << std::setprecision(precision) << x;
	return stream.str();
}

} // namespace aux::format 