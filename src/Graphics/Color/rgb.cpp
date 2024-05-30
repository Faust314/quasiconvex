#include "rgb.hpp"

#include "../../Utils/Basic/format_utils.hpp"

#include <bitset>
#include <cstdint>

namespace graphics::color {

RGB::RGB (arg_t r_, arg_t g_, arg_t b_) :
	r(r_), g(g_), b(b_)
{}

void RGB::compress (arg_t step) {
	r -= r % step;
	g -= g % step;
	b -= b % step;
}

uint32_t RGB::hash () {
	return (((r << 8) + g) << 8) + b;
}

std::string RGB::to_string_16 () const {
	return
		aux::format::uint8_t_to_string_16(r) +
		aux::format::uint8_t_to_string_16(g) +
		aux::format::uint8_t_to_string_16(b);
}
	
} // namespace graphics::color
