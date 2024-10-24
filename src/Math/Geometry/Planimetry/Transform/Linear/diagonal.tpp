#pragma once
#include "diagonal.hpp"

#include <cmath>

namespace math::geom::plan::detail {

template <Coord_t coord_t>
void DiagonalT_int<coord_t>::reset () {
	_a = 1;
	_b = 1;
}

template <Coord_t coord_t>
void DiagonalT_int<coord_t>::reset (ScalarT<coord_t> const & scalar) {
	_a = scalar.scale();
	_b = scalar.scale();
}

template <Coord_t coord_t>
void DiagonalT_int<coord_t>::reset (DiagonalT<coord_t> const & diagonal) {
	_a = diagonal.a();
	_b = diagonal.b();
}

template <Coord_t coord_t>
void DiagonalT_int<coord_t>::reset (HomothetyT<coord_t> const & homothety) {
	assert(homothety.is_diagonal());
	_a = homothety.a();
	_b = homothety.is_reflected() ? - homothety.a() : homothety.a();
}

template <Coord_t coord_t>
void DiagonalT_int<coord_t>::reset (LinearT<coord_t> const & linear) {
	assert(linear.is_diagonal());
	_a = linear.a();
	_b = linear.a();
}

template <Coord_t coord_t>
void DiagonalT_int<coord_t>::reset (coord_t a_, coord_t b_) {
	_a = a_;
	_b = b_;
}



template <Coord_t coord_t>
DiagonalT_int<coord_t>::DiagonalT_int (coord_t a_, coord_t b_) :
	_a(a_),
	_b(b_)
{}



template <Coord_t coord_t>
linear_t DiagonalT_int<coord_t>::type () const {
	return linear_t::diagonal;
}



template <Coord_t coord_t>
bool DiagonalT_int<coord_t>::is_scalar () const {
	if constexpr (Int_t<coord_t>) {
		_a == _b;
	} else {
		std::abs(_a - _b) <= error;
	}
}

template <Coord_t coord_t>
bool DiagonalT_int<coord_t>::is_diagonal () const {
	return true;
}

template <Coord_t coord_t>
bool DiagonalT_int<coord_t>::is_homothety () const {
	if constexpr (Int_t<coord_t>) {
		_a == _b || _a == -_b;
	} else {
		std::abs(std::abs(_a) - std::abs(_b)) <= error;
	}
}



template <Coord_t coord_t>
coord_t DiagonalT_int<coord_t>::a () const {
	return _a;
}

template <Coord_t coord_t>
coord_t DiagonalT_int<coord_t>::b () const {
	return _b;
}



template <Coord_t coord_t>
coord_t DiagonalT_int<coord_t>::det () const {
	return _a * _b;
}

template <Coord_t coord_t>
int8_t DiagonalT_int<coord_t>::orientation () const {
	if constexpr (Int_t<coord_t>) {
		int8_t x = _a > 0 ? 1 : _a < 0 ? -1 : 0;
		int8_t y = _b > 0 ? 1 : _b < 0 ? -1 : 0;
		return x * y;
	} else {
		int8_t x = _a > error ? 1 : _a < -error ? -1 : 0;
		int8_t y = _b > error ? 1 : _b < -error ? -1 : 0;
		return x * y;
	}
}



template <Coord_t coord_t>
DiagonalT_int<coord_t> DiagonalT_int<coord_t>::operator* (DiagonalT_int const & linear) const {
	return {_a * linear._a, _b * linear._b};
}



template <Coord_t coord_t>
DiagonalT_int<Real_t<coord_t>> DiagonalT_int<coord_t>::get_inverse () const {
	assert(! LinearAT<coord_t>::is_degenerate());
	return {1 / Real_t<coord_t>(_a), 1 / Real_t<coord_t>(_b)};
}



template <Coord_t coord_t>
void DiagonalT_int<coord_t>::apply (PointT<coord_t> & point) {
	point.x *= _a;
	point.y *= _b;
}

template <Coord_t coord_t>
PointT<coord_t> DiagonalT_int<coord_t>::operator() (PointT<coord_t> const & p) const {
	return {_a * p.x, _b * p.y};
}





template <Coord_t coord_t>
void DiagonalT_float<coord_t>::reset (OrthogonalT<coord_t> const & orthogonal) {
	assert(orthogonal.is_diagonal());
	DiagonalT_int<coord_t>::_a = orthogonal.angle() < std::numbers::pi / 2 ? 1 : -1;
	DiagonalT_int<coord_t>::_b = (orthogonal.angle() < std::numbers::pi / 2 ? 1 : -1) *
		orthogonal.is_reflected() ? - 1 : 1;
}



template <Coord_t coord_t>
bool DiagonalT_float<coord_t>::is_orthogonal () const {
	if constexpr (Int_t<coord_t>) {
		DiagonalT_int<coord_t>::_a == 1 || DiagonalT_int<coord_t>::_a == -1 &&
		DiagonalT_int<coord_t>::_b == 1 || DiagonalT_int<coord_t>::_b == -1;
	} else {
		std::abs(std::abs(DiagonalT_int<coord_t>::_a) - 1) < error &&
		std::abs(std::abs(DiagonalT_int<coord_t>::_b) - 1) < error;
	}
}

template <Coord_t coord_t>
void DiagonalT_float<coord_t>::inverse () const {
	assert(! LinearAT<coord_t>::is_degenerate());
	DiagonalT_int<coord_t>::_a = 1 / DiagonalT_int<coord_t>::_a;
	DiagonalT_int<coord_t>::_b = 1 / DiagonalT_int<coord_t>::_b;
}

} // namespace math::geom::plan::detail
