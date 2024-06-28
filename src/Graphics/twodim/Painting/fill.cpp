#include "../../../Custom/Graphics/2d_painting/fills.hpp"
#include "fill.hpp"

#include <cassert>

namespace graphics::twodim::paint {

Fill::Fill () :
	_empty(true)
{}

Fill::Fill (color::RGB_O color_) : 
	_empty(false),
	_color(color_)
{}

bool Fill::is_empty () const {
	return _empty;
}

color::RGB_O const & Fill::color () const {
	assert(!_empty);
	return _color;
}

void Fill::clear () {
	_empty = true;
}

void Fill::assign_color (color::RGB_O const & color_) {
	_empty = false;
	_color = color_;
}

} // namespace graphics::twodim::paint
