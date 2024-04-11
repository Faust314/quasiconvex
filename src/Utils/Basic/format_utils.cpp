#include "format_utils.hpp"

#include <iomanip>

namespace aux::format {

std::string uint8_t_to_string_16 (uint8_t a) {
	return {
		a / 16 < 10 ? char('0' + a / 16) : char('A' + a / 16 - 10),
		a % 16 < 10 ? char('0' + a % 16) : char('A' + a % 16 - 10)
	};
}



void set_precision (std::fstream & ofs, precision_t const precision) {
	ofs << ::std::fixed << std::setprecision(precision);
}
	
} // namespace aux::format



