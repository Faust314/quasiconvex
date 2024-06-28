#pragma once

#include "rectangular.hpp"
#include "../../../Utils/Basic/math_utils.hpp"

#include <cassert>
#include <cmath>

namespace math::geom::plan {

template <Coord_t coord_t>
RectangularT<coord_t>::RectangularT (coord_t a_, coord_t b_, coord_t x0_, coord_t y0_) :
	_a(a_),
	_b(b_),
	_x0(x0_),
	_y0(y0_)
{}
template <Coord_t coord_t>
RectangularT<coord_t>::RectangularT (coord_t a_, coord_t b_, PointT<coord_t> const & shift) :
	_a(a_),
	_b(b_),
	_x0(shift.x),
	_y0(shift.y)
{}
template <Coord_t coord_t>
RectangularT<coord_t>::RectangularT (coord_t x0_, coord_t y0_) :
	_a(1),
	_b(1),
	_x0(x0_),
	_y0(y0_)
{}
template <Coord_t coord_t>
RectangularT<coord_t>::RectangularT (PointT<coord_t> const & shift) :
	_a(1),
	_b(1),
	_x0(shift.x),
	_y0(shift.y)
{}



template <Coord_t coord_t>
coord_t RectangularT<coord_t>::a () const {
	return _a;
}

template <Coord_t coord_t>
coord_t RectangularT<coord_t>::b () const {
	return _b;
}

template <Coord_t coord_t>
coord_t RectangularT<coord_t>::x0 () const {
	return _x0;
}

template <Coord_t coord_t>
coord_t RectangularT<coord_t>::y0 () const {
	return _y0;
}



template <Coord_t coord_t>
RectangularT<coord_t> RectangularT<coord_t>::operator* (RectangularT<coord_t> const & rect) {
	return RectangularT<coord_t> (
		_a * rect._a, _b * rect._b,
		_a * rect._x0 + _x0, _b * rect._y0 + _y0
	);
}



template <Coord_t coord_t>
RectangularT<Real_t<coord_t>> RectangularT<coord_t>::get_inverse () const {
	real_t a = 1 / real_t(_a);
	real_t b = 1 / real_t(_b);
	return {
		a, b,
		- a * _x0, - b * _y0
	};
}

template <Coord_t coord_t>
void RectangularT<coord_t>::inverse () const requires is_float {
	_a = 1 / _a;
	_b = 1 / _b;
	_x0 = - _a * _x0;
	_y0 = - _b * _y0;
}



template <Coord_t coord_t>
PointT<coord_t> RectangularT<coord_t>::operator() (PointT<coord_t> const & point) {
	return {_a * point.x + _x0, _b * point.y + _y0};
}





template <Float_t coord_t>
RectangularT<coord_t> rectangular_translate (
	PointT<coord_t> const & p1, PointT<coord_t> const & p2,
	PointT<coord_t> const & q1, PointT<coord_t> const & q2
) {
	coord_t a = (q2.x - q1.x) / (p2.x - p1.x);
	coord_t b = (q2.y - q1.y) / (p2.y - p1.y);
	return  {a, b, q1.x - p1.x * a, q1.y - p1.y * b};
}



template <Float_t coord_t>
RectangularT<coord_t> proportional_translate (
	PointT<coord_t> const & p1, PointT<coord_t> const & p2,
	PointT<coord_t> const & q1, PointT<coord_t> const & q2,
	int8_t pos_x, int8_t pos_y
) {
	coord_t a = (q2.x - q1.x) / (p2.x - p1.x);
	coord_t b = (q2.y - q1.y) / (p2.y - p1.y);
	if (std::abs(a) < std::abs(b)) {
		b = aux::math::f_sign(b) * std::abs(a);
		return {
			a, b,
			q1.x - p1.x * a,
			q1.y - p1.y * b + 
			(pos_y + 1) * (q2.y - q1.y - b * (p2.y - p1.y)) / 2
		};
	} else {
		a = aux::math::f_sign(a) * std::abs(b);
		return {
			a, b,
			q1.x - p1.x * a +
			(pos_x + 1) * (q2.x - q1.x - a * (p2.x - p1.x)) / 2,
			q1.y - p1.y * b
		};
	}

}



template <Coord_t coord_t>
RectangularT<coord_t> rectangular_scale (coord_t scale) {
	return {scale, scale, 0, 0};
}

template <Coord_t coord_t>
RectangularT<coord_t> rectangular_scale (coord_t scale_x, coord_t scale_y) {
	return {scale_x, scale_y, 0, 0};
}

template <Coord_t coord_t>
RectangularT<coord_t> rectangular_scale (coord_t scale, PointT<coord_t> center) {
	return {scale, scale, center.x * (1 - scale), center.y * (1 - scale)};
}

template <Coord_t coord_t>
RectangularT<coord_t> rectangular_scale (coord_t scale_x, coord_t scale_y, PointT<coord_t> center) {
	return {scale_x, scale_y, center.x * (1 - scale_x), center.y * (1 - scale_y)};
}

} // namespace math::geom::plan