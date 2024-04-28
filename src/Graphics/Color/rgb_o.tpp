#pragma once

#include "rgb_o.hpp"

namespace graphics::color {

template <color_c Color>
RGB_O::RGB_O (Opacity<Color> const & opacity_color) :
	Opacity<RGB>(RGB(opacity_color.col), opacity_color.op)
{ }

} // namespace graphics::color