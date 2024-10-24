#pragma once
#include "affine.hpp"

namespace math::geom::plan {

template <Coord_t coord_t>
AffineT<coord_t>::AffineT (coord_t a_, coord_t b_, coord_t c_, coord_t d_, coord_t x0_, coord_t y0_) :
	_a(a_),
	_b(b_),
	_c(c_),
	_d(d_),
	_x0(x0_),
	_y0(y0)
{}

template <Coord_t coord_t>
AffineT<coord_t>::AffineT (coord_t a_, coord_t b_, coord_t c_, coord_t d_, PointT<coord_t> const & shift) :
	_a(a_),
	_b(b_),
	_c(c_),
	_d(d_),
	_x0(shift.x),
	_y0(shift.y)
{}

template <Coord_t coord_t>
AffineT<coord_t>::AffineT (coord_t x0_, coord_t y0_) :
	_a(1),
	_b(0),
	_c(0),
	_d(1),
	_x0(x0_),
	_y0(y0_)
{}

template <Coord_t coord_t>
AffineT<coord_t>::AffineT (PointT<coord_t> const & shift) :
	_a(1),
	_b(0),
	_c(0),
	_d(1),
	_x0(shift.x),
	_y0(shift.y)
{}



template <Coord_t coord_t>
coord_t AffineT<coord_t>::a () const {
	return _a;
}

template <Coord_t coord_t>
coord_t AffineT<coord_t>::b () const {
	return _b;
}

template <Coord_t coord_t>
coord_t AffineT<coord_t>::c () const {
	return _c;
}

template <Coord_t coord_t>
coord_t AffineT<coord_t>::d () const {
	return _d;
}

template <Coord_t coord_t>
coord_t AffineT<coord_t>::x0 () const {
	return _x0;
}

template <Coord_t coord_t>
coord_t AffineT<coord_t>::y0 () const {
	return _y0;
}



template <Coord_t coord_t>
coord_t AffineT<coord_t>::det () const {
	return _a * _d - _b * _c;
}

template <Coord_t coord_t>
bool AffineT<coord_t>::is_orthogonal () const {
	return
		std::abs(std::abs(_a) - std::abs(_d)) < math::geom::error &&
		std::abs(std::abs(_b) - std::abs(_c)) < math::geom::error &&
		std::abs(_a * _b + _c * _d) < math::geom::error;
}



template <Coord_t coord_t>
AffineT<coord_t> AffineT<coord_t>::operator* (AffineT<coord_t> const & affine) {
	return {
		_a * affine._a + _b * affine._c,
		_a * affine._b + _b * affine._d,
		_c * affine._a + _d * affine._c,
		_c * affine._b + _d * affine._d,
		_a * affine._x0 + _b * affine._y0 + _x0,
		_c * affine._x0 + _d * affine._y0 + _y0
	};
}



template <Coord_t coord_t>
AffineT<typename AffineT<coord_t>::real_t> AffineT<coord_t>::get_inverse () const {
	real_t D = 1 / (_a * _d - _b * _c);
	real_t a = real_t(_d) / D;
	real_t b = - real_t(_b) / D;
	real_t c = - real_t(_c) / D;
	real_t d = real_t(_a) / D;
	return {
		a, b, c, d,
		- a * _x0 - b * _y0, - c * _x0 - d * _y0
	};
}

template <Coord_t coord_t>
void AffineT<coord_t>::inverse () const requires is_float {
	real_t D = 1 / (_a * _d - _b * _c);
	std::swap(_a, _d);
	_a /= D;
	_b /= - D;
	_c /= - D;
	_d /= D;
	real_t x = - _a * _x0 - _b * _y0;
	_y0 = - _c * _x0 - _d * _y0;
	_x0 = x;
}



template <Coord_t coord_t>
void AffineT<coord_t>::apply (PointT<coord_t> & point) const {
	coord_t x = _a * point.x + _b * point.y + _x0;
	point.y = _c * point.x + _d * point.y + _y0;
	point.x = x;
}

template <Coord_t coord_t>
PointT<coord_t> AffineT<coord_t>::operator() (PointT<coord_t> const & point) const {
	return {
		_a * point.x + _b * point.y + _x0,
		_c * point.x + _d * point.y + _y0
	};
}





template <Coord_t coord_t>
AffineT<coord_t> affine_scale (coord_t scale) {
	return {scale, 0, 0, scale, 0, 0};
}

template <Coord_t coord_t>
AffineT<coord_t> plan::affine_scale (coord_t scale, PointT<coord_t> center) {
	return {scale, 0, 0, scale, center.x * (1 - scale), center.y * (1 - scale)};
}

template <Coord_t coord_t>
AffineT<coord_t> affine_rotate (coord_t rotation) requires Float_t<coord_t> {
	return {std::cos(rotation), - std::sin(rotation), std::sin(rotation), std::cos(rotation)};
}

template <Coord_t coord_t>
AffineT<coord_t> plan::affine_symmetry (coord_t rotation) requires Float_t<coord_t> {
	rotation *= 2;
	return {std::cos(rotation), std::sin(rotation), std::sin(rotation), - std::cos(rotation)};
}

} // namespace math::geom::plan