#pragma once

#include "../types.hpp"

namespace graphics::color {

template <color_c Color>
struct Opacity {
	Color col;
	arg_t op;
	
	explicit Opacity (Color const & col_ = Color(), arg_t op_ = 255);
	Opacity (double op_, Color const & col_);
};
	
} // graphics::color