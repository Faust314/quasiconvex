#pragma once

#include <cstdint>
#include <concepts>
#include <string>

namespace graphics {

typedef double coord_t;

namespace color {

typedef uint8_t arg_t;

class RGB;

template<class T>
concept color_c = requires (T t) {
	std::is_same_v<decltype(t.to_string_16()), std::string>;
	std::is_convertible_v<T, RGB>;
};

} // namespace color

} // namespace graphics