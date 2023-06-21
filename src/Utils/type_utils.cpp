#include "type_utils.hpp"

namespace aux::types {

std::string removing_leading_zeros (std::string const & number) {
	int k = 0;
	while (number[k + 1] != '.' && number[k] == '0') {
		k++;
	}
	return number.substr(k);
}

std::string lead_zeros (int number, int zeros_count) {
	if (zeros_count >= std::to_string(number).length()) {
		return std::string(zeros_count - std::to_string(number).length(), '0') + std::to_string(number);
 	} else {
		return std::to_string(number);
	}
}

std::string to_string (double x) {
	return std::to_string(x);
}

} // namespace aux::types
