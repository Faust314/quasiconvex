#include "time_utils.hpp"

#include "type_utils.hpp"

#include <ctime>

namespace aux::time {

std::string date (time_t timer) {
	std::tm date = *std::localtime(& timer);
	return std::to_string(date.tm_year + 1900) +
		"-" + types::lead_zeros(date.tm_mon + 1, 2) +
		"-" + types::lead_zeros(date.tm_mday, 2) +
		"_" + types::lead_zeros(date.tm_hour, 2) +
		"-" + types::lead_zeros(date.tm_min, 2) +
		"-" + types::lead_zeros(date.tm_sec, 2);
}

} // namespace aux::date
