#pragma once

#include <concepts>
#include <cstdint>

namespace aux::math {

template <std::integral T>
int8_t sign (T t);
template <std::integral T>
int8_t f_sign (T t);
	
} // namespace aux::math