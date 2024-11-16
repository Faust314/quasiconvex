#pragma once

#include "rgb.hpp"
#include "opacity.hpp"

namespace graphics::color {

struct RGB_O : public Opacity<RGB> {
	using arg_t = arg_t;
	
	explicit RGB_O (arg_t r_ = 0, arg_t g_ = 0, arg_t b_ = 0, double op_ = 1);
	explicit RGB_O (RGB const & rgb, double op_ = 1);
	
	template <color_c Color>
	explicit RGB_O (Opacity<Color> const & opacity_color);
};

} // namespace graphics::color