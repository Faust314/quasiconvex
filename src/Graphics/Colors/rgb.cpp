#include "rgb.hpp"

#include "../../Utils/format_utils.hpp"

#include <bitset>

namespace graphics {

RGB::RGB (uint8_t r_, uint8_t g_, uint8_t b_) :
	r(r_), g(g_), b(b_)
{}

RGB RGB::res (uint8_t step) const {
	return RGB(r - r % step, g - g % step, b - b % step);
}

RGB RGB::res_3 () const { return res(85); }
RGB RGB::res_5 () const { return res(51); }
RGB RGB::res_15 () const { return res(17); }
RGB RGB::res_17 () const { return res(15); }
RGB RGB::res_51 () const { return res(5); }
RGB RGB::res_85 () const { return res(3); }

std::string RGB::to_string_16 () const {
	return
		aux::format::uint8_t_to_string_16(r) +
		aux::format::uint8_t_to_string_16(g) +
		aux::format::uint8_t_to_string_16(b);
}


} // namespace graphics
