#pragma once

#include "../types.hpp"

namespace graphics::color {

template <color_c Color>
struct Opacity {
	explicit Opacity (Color const & col_ = Color(), arg_t op_ = 255);
	Opacity (double op_, Color const & col_);
	
	Color col;
	arg_t op;
	
	bool has_op () const;
	double op_norm () const;
};
	
} // graphics::color