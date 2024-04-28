#include "paint.hpp"

namespace graphics::twodim {

Style::Style (paint::Fill const & fill_, paint::Stroke const & stroke_) :
	_fill(fill_),
	_stroke(stroke_)
{}

Style::Style (
	color::RGB_O fill_color,
	color::RGB_O stroke_color,
	coord_t width,
	Linecap linecap,
	Linejoin linejoin
) :
	_fill(fill_color),
	_stroke(stroke_color, width, linecap, linejoin)
{}



Style::Style (paint::Fill const & fill_) :
	_fill(fill_),
	_stroke()
{}

Style::Style (color::RGB_O fill_color) :
	_fill(fill_color),
	_stroke()
{}



Style::Style (paint::Stroke const stroke_) :
	_fill(),
	_stroke(stroke_)
{}

Style::Style (color::RGB_O color_, coord_t width_, Linecap linecap, Linejoin linejoin) :
	_fill(),
	_stroke(color_, width_, linecap, linejoin)
{}



paint::Fill & Style::fill () {
	return _fill;
}

paint::Stroke & Style::stroke () {
	return _stroke;
}

} // namespace graphics::twodim::paint
