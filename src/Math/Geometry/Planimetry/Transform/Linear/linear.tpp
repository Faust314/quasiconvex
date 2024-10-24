#pragma once
#include "linear.hpp"

#include <cmath>

namespace math::geom::plan::detail {

template <Coord_t coord_t>
void LinearT_int<coord_t>::reset () {
	_a = 1;
	_b = 0;
	_c = 0;
	_d = 1;
}

template <Coord_t coord_t>
void LinearT_int<coord_t>::reset (ScalarT<coord_t> const & scalar) {
	_a = scalar.scale();
	_b = 0;
	_c = 0;
	_d = scalar.scale();
}

template <Coord_t coord_t>
void LinearT_int<coord_t>::reset (DiagonalT<coord_t> const & diagonal) {
	_a = diagonal.a();
	_b = 0;
	_c = 0;
	_d = diagonal.b();
}

template <Coord_t coord_t>
void LinearT_int<coord_t>::reset (HomothetyT<coord_t> const & homothety) {
	_a = homothety.a();
	_b = (homothety.is_reflected() ? 1 : -1) * homothety.b();
	_c = homothety.b();
	_d = (homothety.is_reflected() ? -1 : 1) * homothety.a();
}

template <Coord_t coord_t>
void LinearT_int<coord_t>::reset (LinearT<coord_t> const & linear) {
	_a = linear.a();
	_b = linear.b();
	_c = linear.c();
	_d = linear.d();
}

template <Coord_t coord_t>
void LinearT_int<coord_t>::reset (coord_t a_, coord_t b_, coord_t c_, coord_t d_) {
	_a = a_;
	_b = b_;
	_c = c_;
	_d = d_;
}



template <Coord_t coord_t>
LinearT_int<coord_t>::LinearT_int (coord_t a_, coord_t b_, coord_t c_, coord_t d_) :
	_a(a_),
	_b(b_),
	_c(c_),
	_d(d_)
{}



template <Coord_t coord_t>
linear_t LinearT_int<coord_t>::type () const {
	return linear_t::linear;
}



template <Coord_t coord_t>
bool LinearT_int<coord_t>::is_scalar () const {
	if constexpr (Int_t<coord_t>) {
		return _b == 0 && _c == 0 && _a == _d;
	} else {
		return std::abs(_b) < error && std::abs(_c) < error && std::abs(_a - _d) < error;
	}
}

template <Coord_t coord_t>
bool LinearT_int<coord_t>::is_diagonal () const {
	if constexpr (Int_t<coord_t>) {
		return _b == 0 && _c == 0;
	} else {
		return std::abs(_b) < error && std::abs(_c) < error;
	}
}

template <Coord_t coord_t>
bool LinearT_int<coord_t>::is_homothety () const {
	if constexpr (Int_t<coord_t>) {
		return
			std::abs(_a) == std::abs(_d) &&
			std::abs(_b) == std::abs(_c) &&
			_a * _d + _b * _c == 0;
	} else {
		return
			std::abs(std::abs(_a) - std::abs(_d)) < error &&
			std::abs(std::abs(_b) - std::abs(_c)) < error &&
			std::abs(_a * _d + _b * _c) < error;
	}
}



template <Coord_t coord_t>
coord_t LinearT_int<coord_t>::det () const {
	return _a * _d - _b * _c;
}

template <Coord_t coord_t>
int8_t LinearT_int<coord_t>::orientation () const {
	if constexpr (Int_t<coord_t>) {
		coord_t d = det();
		return d > 0 ? 1 : d < 0 ? -1 : 0;
	} else {
		coord_t d = det();
		return d > error ? 1 : d < -error ? -1 : 0;
	}
}



template <Coord_t coord_t>
LinearT_int<coord_t> LinearT_int<coord_t>::operator* (LinearT_int const & linear) const {
	return {
		_a * linear._a + _b * linear._c,
		_a * linear._b + _b * linear._d,
		_c * linear._a + _d * linear._c,
		_c * linear._b + _d * linear._d
	};
}



template <Coord_t coord_t>
LinearT_int<Real_t<coord_t>> LinearT_int<coord_t>::get_inverse () const {
	coord_t D = Real_t<coord_t>(det());
	assert(std::abs(D) > error);
	return {
		Real_t<coord_t>(_d) / D,
		- Real_t<coord_t>(_b) / D,
		- Real_t<coord_t>(_c) / D,
		Real_t<coord_t>(_a) / D
	};
}



template <Coord_t coord_t>
void LinearT_int<coord_t>::apply (PointT<coord_t> & point) {
	point = {
		_a * point.x + _b * point.y,
		_c * point.x + _d * point.y
	};
}

template <Coord_t coord_t>
PointT<coord_t> LinearT_int<coord_t>::operator() (PointT<coord_t> const & point) const {
	return {
		_a * point.x + _b * point.y,
		_c * point.x + _d * point.y
	};
}



template <Coord_t coord_t>
std::tuple<OrthogonalT<coord_t>, DiagonalT<coord_t>, OrthogonalT<coord_t>> LinearT_int<coord_t>::get_svd () const {
	if (is_homothety()) {
		if (std::abs(_a) < error && std::abs(_c) < error) {
			return {{0, false}, {0,0}, {0, false}};
		} else {
			Real_t<coord_t> s = std::sqrt(_a * _a + _c * _c);
			Real_t<coord_t> angle = std::atan2(_c, _a);
			return {
				{0, false},
				{s, s},
				{
					angle < 0 ? angle + 2 * std::numbers::pi_v<coord_t> : angle,
					LinearAT<coord_t>::is_negative_oriented()
				}
			};
		}
	} else {
		coord_t A = _a * _a;
		coord_t B = _b * _b;
		coord_t C = _c * _c;
		coord_t D = _d * _d;
		coord_t E = _a * _b + _c * _d;
		coord_t F = _a * _c + _b * _d;
		
		Real_t<coord_t> R = std::sqrt(Real_t<coord_t>(
			std::pow(A - D, 2) + std::pow(B - C, 2) + 2 * E * E + 2 * F * F
		));
		Real_t<coord_t> l = (R + A + B + C + D) / 2;
		Real_t<coord_t> s1 = std::sqrt(l);
		Real_t<coord_t> s2 = std::sqrt(std::abs(l - R));
		
		Real_t<coord_t> G = A + C - l;
		Real_t<coord_t> H = B + D - l;
		Real_t<coord_t> v1;
		Real_t<coord_t> v2;
		Real_t<coord_t> v3;
		Real_t<coord_t> v4;
		if (std::abs(G) < error && std::abs(E) < error) {
			assert(std::abs(E) > error || std::abs(H) > error);
			Real_t<coord_t> t = std::sqrt(E * E + H * H);
			v1 = H / t;
			v2 = E / t;
			v3 = - E / t;
			v4 = H / t;
		} else {
			Real_t<coord_t> t = std::sqrt(G * G + E * E);
			v1 = E / t;
			v2 = G / t;
			v3 = - G / t;
			v4 = E / t;
		}
		Real_t<coord_t> w1 = _a * v1 + _b * v3;
		Real_t<coord_t> w2 = _a * v2 + _b * v4;
		Real_t<coord_t> w3 = _c * v1 + _d * v3;
		Real_t<coord_t> w4 = _c * v2 + _d * v4;
		
		Real_t<coord_t> u1;
		Real_t<coord_t> u3;
		if (std::abs(w1) < error && std::abs(w3) < error) {
			assert(std::abs(w2) > error || std::abs(w4) > error);
			u1 = w4;
			u3 = -w2;
		} else {
			u1 = w1;
			u3 = w3;
		}
		Real_t<coord_t> v_angle = - std::atan2(v3, v1);
		Real_t<coord_t> u_angle = std::atan2(u3, u1);
		
		return {
			{
				u_angle < 0 ? u_angle : u_angle + 2 * std::numbers::pi_v<coord_t>,
				LinearAT<coord_t>::is_negative_oriented()
			},
			{s1, s2},
			{v_angle < 0 ? v_angle : v_angle + 2 * std::numbers::pi_v<coord_t>, false}
		};
	}
}





template <Coord_t coord_t>
void LinearT_float<coord_t>::reset (OrthogonalT<coord_t> const & orthogonal) {
	coord_t x = std::cos(orthogonal.angle);
	coord_t y = std::sin(orthogonal.angle);
	LinearT_int<coord_t>::_a = x;
	LinearT_int<coord_t>::_b = orthogonal.is_reflected() ? y : -y;
	LinearT_int<coord_t>::_c = y;
	LinearT_int<coord_t>::_d = orthogonal.is_reflected() ? -x : x;
}



template <Coord_t coord_t>
bool LinearT_float<coord_t>::is_orthogonal () const {
	return
		std::abs(std::abs(LinearT_int<coord_t>::_a) - std::abs(LinearT_int<coord_t>::_d)) < error &&
		std::abs(std::abs(LinearT_int<coord_t>::_b) - std::abs(LinearT_int<coord_t>::_c)) < error &&
		std::abs(LinearT_int<coord_t>::_a * LinearT_int<coord_t>::_d +
		LinearT_int<coord_t>::_b * LinearT_int<coord_t>::_c) < error &&
		std::abs(
			LinearT_int<coord_t>::_a * LinearT_int<coord_t>::_a +
			LinearT_int<coord_t>::_c * LinearT_int<coord_t>::_c +
		- 1) < error;
}

template <Coord_t coord_t>
void LinearT_float<coord_t>::inverse () const {
	coord_t D = LinearT_int<coord_t>::det();
	assert(std::abs(D) > error);
	LinearT_int<coord_t>::_a = Real_t<coord_t>(LinearT_int<coord_t>::_d) / D;
	LinearT_int<coord_t>::_b = - Real_t<coord_t>(LinearT_int<coord_t>::_b) / D;
	LinearT_int<coord_t>::_c = - Real_t<coord_t>(LinearT_int<coord_t>::_c) / D;
	LinearT_int<coord_t>::_d = Real_t<coord_t>(LinearT_int<coord_t>::_a) / D;
}

} // namespace math::geom::plan::detail