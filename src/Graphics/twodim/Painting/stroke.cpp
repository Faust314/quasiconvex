#include "stroke.hpp"

#include <cassert>

namespace graphics::twodim::paint {


Stroke::Stroke () :
	_empty(true)
{}

Stroke::Stroke (color::RGB_O color_, coord_t width_, Linecap linecap, Linejoin linejoin) :
	_empty(false),
	_color(color_),
	_width(width_),
	line_type(3 * int(linecap) + int(linejoin))
{}



bool Stroke::is_empty () const {
	return _empty;
}

void Stroke::clear () {
	_empty = true;
}

color::RGB_O const & Stroke::color () const {
	assert(! _empty);
	return _color;
}

coord_t const & Stroke::width () const {
	assert(! _empty);
	return _width;
}

Linecap Stroke::linecap () const {
	assert(! _empty);
	return Linecap(line_type / 3);
}

Linejoin Stroke::linejoin () const {
	assert(! _empty);
	return Linejoin(line_type % 3);
}



void Stroke::assign_stroke (color::RGB_O color_, coord_t width_, Linecap linecap, Linejoin linejoin) {
	_empty = false;
	_color = color_;
	_width = width_;
	line_type = 3 * int(linecap) + int(linejoin);
}

void Stroke::assign_color (color::RGB_O color_) {
	assert(! _empty);
	_color = color_;
}

void Stroke::assign_width (coord_t width_) {
	assert(! _empty);
	_width = width_;
}

void Stroke::assign_linecap (Linecap linecap) {
	line_type = 3 * int(linecap) + line_type % 3;
}

void Stroke::assign_linejoin (Linejoin linejoin) {
	line_type = line_type - line_type % 3 + int(linejoin);
}

} // namespace graphics::twodim::paint