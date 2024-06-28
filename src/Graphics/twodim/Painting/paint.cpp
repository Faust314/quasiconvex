#include "paint.hpp"

namespace graphics::twodim {

Paint::Paint (paint::Fill const & fill_, paint::Stroke const & stroke_) :
	_fill(fill_),
	_stroke(stroke_)
{}

Paint::Paint (
	color::RGB_O fill_color,
	color::RGB_O stroke_color,
	coord_t width,
	Linecap linecap,
	Linejoin linejoin
) :
	_fill(fill_color),
	_stroke(stroke_color, width, linecap, linejoin)
{}



Paint::Paint (paint::Fill const & fill_) :
	_fill(fill_),
	_stroke()
{}

Paint::Paint (color::RGB_O fill_color) :
	_fill(fill_color),
	_stroke()
{}



Paint::Paint (paint::Stroke const stroke_) :
	_fill(),
	_stroke(stroke_)
{}

Paint::Paint (color::RGB_O color_, coord_t width_, Linecap linecap, Linejoin linejoin) :
	_fill(),
	_stroke(color_, width_, linecap, linejoin)
{}



paint::Fill const & Paint::fill () const {
	return _fill;
}

paint::Fill & Paint::fill () {
	return _fill;
}

paint::Stroke const & Paint::stroke () const {
	return _stroke;
}

paint::Stroke & Paint::stroke () {
	return _stroke;
}
	
} // namespace graphics::twodim::paint
