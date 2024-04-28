#pragma once

#include "opacity.hpp"

#include <cassert>
#include <cmath>

namespace graphics::color {

template <color_c Color>
Opacity<Color>::Opacity (Color const & col_, arg_t op_) :
	col(col_),
	op(op_)
{}

template <color_c Color>
Opacity<Color>::Opacity (double op_, Color const & col_) :
	col(col_),
	op(std::fmax(0, std::fmin(255, std::round(255 * op_))))
{
	assert(0 < op_ && op_ <= 1);
}

} // namespace graphics::color