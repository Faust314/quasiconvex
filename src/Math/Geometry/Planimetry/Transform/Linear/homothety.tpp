#pragma once
#include "homothety.hpp"

#include <cassert>
#include <cmath>

namespace math::geom::plan::detail {

template <Coord_t coord_t>
void HomothetyT_int<coord_t>::reset () {
	_a = 1;
	_b = 0;
	_is_reflected = false;
}

template <Coord_t coord_t>
void HomothetyT_int<coord_t>::reset (ScalarT<coord_t> const & scalar) {
	_a = scalar.scale();
	_b = 0;
	_is_reflected = false;
}

template <Coord_t coord_t>
void HomothetyT_int<coord_t>::reset (DiagonalT<coord_t> const & diagonal) {
	assert(diagonal.is_homothety());
	_a = diagonal.a();
	_b = 0;
	if (diagonal.a() > 0) {
		_is_reflected = diagonal.b() > 0 ? true : false;
	} else {
		_is_reflected = diagonal.b() < 0 ? true : false;
	}
}

template <Coord_t coord_t>
void HomothetyT_int<coord_t>::reset (HomothetyT<coord_t> const & homothety) {
	_a = homothety.a();
	_b = homothety.b();
	_is_reflected = homothety.is_reflected();
}

template <Coord_t coord_t>
void HomothetyT_int<coord_t>::reset (LinearT<coord_t> const & linear) {
	assert(linear.is_homothety());
	_a = linear.a();
	_b = linear.c();
	_is_reflected = linear.is_negative_oriented();
}

template <Coord_t coord_t>
void HomothetyT_int<coord_t>::reset (coord_t a_, coord_t b_, bool is_reflected_) {
	_a = a_;
	_b = b_;
	_is_reflected = is_reflected_;
}

template <Coord_t coord_t>
HomothetyT_int<coord_t>::HomothetyT_int (coord_t a_, coord_t b_, bool is_reflected_) :
	_a(a_), _b(b_), _is_reflected(is_reflected_)
{}



template <Coord_t coord_t>
linear_t HomothetyT_int<coord_t>::type () const {
	return linear_t::homothety;
}



template <Coord_t coord_t>
bool HomothetyT_int<coord_t>::is_scalar () const {
	if constexpr (Int_t<coord_t>) {
		return _b == 0 && ! _is_reflected;
	} else {
		return std::abs(_b) < error && _is_reflected;
	}
}

template <Coord_t coord_t>
bool HomothetyT_int<coord_t>::is_diagonal () const {
	if constexpr (Int_t<coord_t>) {
		return _b == 0;
	} else {
		return std::abs(_b) < error;
	}
}

template <Coord_t coord_t>
bool HomothetyT_int<coord_t>::is_homothety () const {
	return true;
}



template <Coord_t coord_t>
coord_t HomothetyT_int<coord_t>::a () const {
	return _a;
}

template <Coord_t coord_t>
coord_t HomothetyT_int<coord_t>::b () const {
	return _b;
}

template <Coord_t coord_t>
bool HomothetyT_int<coord_t>::is_reflected () const {
	return _is_reflected;
}



template <Coord_t coord_t>
coord_t HomothetyT_int<coord_t>::det () const {
	return (_is_reflected ? -1 : 1) * (_a * _a + _b * _b);
}

template <Coord_t coord_t>
int8_t HomothetyT_int<coord_t>::orientation () const {
	if constexpr (Int_t<coord_t>) {
		return _a == 0 && _b == 0 ? 0 : _is_reflected ? -1 : 1;
	} else {
		return std::abs(_a) < error && std::abs(_b) < error ? 0 : _is_reflected ? -1 : 1;
	}
}



template <Coord_t coord_t>
HomothetyT_int<coord_t> HomothetyT_int<coord_t>::operator* (HomothetyT_int const & homothety) const {
	return {
		_a * homothety._a + (_is_reflected ? 1 : -1) * _b * homothety._b,
		_b * homothety._a + (_is_reflected ? -1 : 1) * _a * homothety._b,
		_is_reflected ^ homothety._is_reflected
	};
}



template <Coord_t coord_t>
HomothetyT_int<Real_t<coord_t>> HomothetyT_int<coord_t>::get_inverse () const {
	Real_t<coord_t> d = 1 / Real_t<coord_t>(_a * _a + _b * _b);
	return {
		Real_t<coord_t>(a) / d,
		(_is_reflected ? 1 : -1) * Real_t<coord_t>(b) / d,
		_is_reflected
	};
}



template <Coord_t coord_t>
void HomothetyT_int<coord_t>::apply (PointT<coord_t> & point) {
	point = {
		_a * point.x + (_is_reflected ? _b : -_b) * point.y,
		_b * point.x + (_is_reflected ? -_a : _a) * point.y
	};
}

template <Coord_t coord_t>
PointT<coord_t> HomothetyT_int<coord_t>::operator() (PointT<coord_t> const & point) const {
	return {
		_a * point.x + (_is_reflected ? _b : -_b) * point.y,
		_b * point.x + (_is_reflected ? -_a : _a) * point.y
	};
}



template <Coord_t coord_t>
std::pair<ScalarT<Real_t<coord_t>>, OrthogonalT<Real_t<coord_t>>> HomothetyT_int<coord_t>::get_decomposition () const {
	if (std::abs(_a) < error && std::abs(_b) < error) {
		return {{0}, {0, false}};
	} else {
		Real_t<coord_t> angle = std::atan(_a, _b);
		return {
			{std::sqrt(_a * _a + _b * _b)},
			{
				angle < 0 ? angle + 2 * std::numbers::pi_v<coord_t> : angle,
				_is_reflected
			}
		};
	}
}





template <Coord_t coord_t>
void HomothetyT_float<coord_t>::reset (OrthogonalT<coord_t> const & orthogonal) {
	HomothetyT_int<coord_t>::_a = std::cos(orthogonal.angle());
	HomothetyT_int<coord_t>::_b = std::sin(orthogonal.angle());
	HomothetyT_int<coord_t>::_is_reflected = orthogonal.is_reflected();
}



template <Coord_t coord_t>
bool HomothetyT_float<coord_t>::is_orthogonal () const {
	coord_t d =
		std::abs(
			HomothetyT_int<coord_t>::_a * HomothetyT_int<coord_t>::_a +
			HomothetyT_int<coord_t>::_b * HomothetyT_int<coord_t>::_b - 1
		);
	return d < error; 
}

template <Coord_t coord_t>
void HomothetyT_float<coord_t>::inverse () const {
	Real_t<coord_t> d = 1 / Real_t<coord_t>(
		HomothetyT_int<coord_t>::_a * HomothetyT_int<coord_t>::_a +
		HomothetyT_int<coord_t>::_b * HomothetyT_int<coord_t>::_b
	);
	HomothetyT_int<coord_t>::_a = HomothetyT_int<coord_t>::_a / d;
	HomothetyT_int<coord_t>::_b =
		(HomothetyT_int<coord_t>::_is_reflected ? 1 : -1) * Real_t<coord_t>(HomothetyT_int<coord_t>::_b) / d;
}

} // namespace math::geom::plan::detail
