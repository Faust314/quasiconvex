#pragma once

#include "math_utils.hpp"

namespace aux::math {

template <std::integral T>
int8_t sign (T t) {
	if (t > 0) {
		return 1;
	} else if (t < 0) {
		return -1;
	} else {
		return 0;
	}
}

template <std::integral T>
int8_t f_sign (T t) {
	if (t > 0) {
		return 1;
	} else {
		return -1;
	};
}
	
} // namespace aux::math