#pragma once

#include "point.hpp"

#include <cassert>
#include <cmath>

namespace math::geom::plan {

template <Coord_t coord_t>
PointT<coord_t>::PointT (coord_t a) : 
	x(a), y(a)
{}

template <Coord_t coord_t>
PointT<coord_t>::PointT (coord_t x_, coord_t y_) :
	x(x_), y(y_)
{}

template <Coord_t coord_t>
template <Coord_t coord_t1>
PointT<coord_t>::PointT (coord_t1 x_, coord_t1 y_) :
	x(coord_t(x_)), y(coord_t(y_))
{}



template <Coord_t coord_t>
template <Coord_t coord_t1>
PointT<coord_t>::PointT (PointT<coord_t1> const & p) :
    x(coord_t(p.x)), y(coord_t(p.y))
{}



template <Coord_t coord_t>
PointT<coord_t>::real_t PointT<coord_t>::abs () const {
	return std::sqrt(x * x + y * y);
}

template <Coord_t coord_t>
coord_t PointT<coord_t>::abs_sqr () const {
	return x * x + y * y;
}

template <Coord_t coord_t>
PointT<coord_t>::real_t PointT<coord_t>::angle () const {
	return std::atan2(x, y) + std::numbers::pi_v<PointT<coord_t>::real_t>;
}

template <Coord_t coord_t>
bool PointT<coord_t>::f_less (PointT p) requires is_float {
	return x < p.x && y < p.y;
}

template <Coord_t coord_t>
bool PointT<coord_t>::f_grt (PointT p) requires is_float {
	return x > p.x && y > p.y;
}

template <Coord_t coord_t>
bool PointT<coord_t>::f_less (coord_t a) requires is_float {
	return x < a && y < a;
}

template <Coord_t coord_t>
bool PointT<coord_t>::f_grt (coord_t a) requires is_float {
	return x > a && y > a;
}



template <Coord_t coord_t>
bool PointT<coord_t>::operator== (PointT const & p) const {
	if constexpr (is_float) {
		return std::max(std::abs(x - p.x), std::abs(y - p.y)) < error;
	} else {
		return x == p.x && y == p.y;
	}
}

template <Coord_t coord_t>
bool PointT<coord_t>::operator!= (PointT const & p) const {
	if constexpr (is_float) {
		return std::max(std::abs(x - p.x), std::abs(y - p.y)) >= error;
	} else {
		return x != p.x || y != p.y;
	}
}

template <Coord_t coord_t>
bool PointT<coord_t>::operator<= (PointT const & p) const {
	if constexpr (is_float) {
		return x < p.x + error && y < p.y + error;
	} else {
		return x <= p.x && y <= p.y;
	}
}

template <Coord_t coord_t>
bool PointT<coord_t>::operator>= (PointT const & p) const {
	if constexpr (is_float) {
		return x + error > p.x && y + error > p.y;
	} else {
		return x >= p.x && y >= p.y;
	}
}

template <Coord_t coord_t>
bool PointT<coord_t>::operator< (PointT const & p) const {
	if constexpr (is_float) {
		return x < p.x - error && y < p.y - error;
	} else {
		return x < p.x && y < p.y;
	}
}

template <Coord_t coord_t>
bool PointT<coord_t>::operator> (PointT const & p) const {
	if constexpr (is_float) {
		return x - error > p.x && y - error > p.y;
	} else {
		return x > p.x && y > p.y;
	}
}



template <Coord_t coord_t>
PointT<coord_t> PointT<coord_t>::operator- () const {
	return PointT(-x, -y);
}

template <Coord_t coord_t>
PointT<coord_t> PointT<coord_t>::operator+ (PointT const & p) const {
	return PointT(x + p.x, y + p.y);
}

template <Coord_t coord_t>
PointT<coord_t> PointT<coord_t>::operator- (PointT const & p) const {
	return PointT(x - p.x, y - p.y);
}

template <Coord_t coord_t>
PointT<coord_t> PointT<coord_t>::operator* (PointT const & p) const {
	return PointT(x * p.x - y * p.y, x * p.y + y * p.x);
}

template <Coord_t coord_t>
PointT<typename PointT<coord_t>::real_t> PointT<coord_t>::operator/ (PointT const & p) const requires is_float{
	PointT<coord_t>::real_t d = p.x * p.x + p.y + p.y;
	assert(d > error_sqr);
	return {real_t(x * p.x + y * p.y) / d, real_t(y * p.x - x * p.y) / d};
}



template <Coord_t coord_t>
PointT<coord_t> & PointT<coord_t>::operator+= (PointT const & p) {
	x += p.x;
	y += p.y;
	return * this;
}

template <Coord_t coord_t>
PointT<coord_t> & PointT<coord_t>::operator-= (PointT const & p) {
	x -= p.x;
	y -= p.y;
	return * this;
}

template <Coord_t coord_t>
PointT<coord_t> & PointT<coord_t>::operator*= (PointT const & p) {
	* this = {x * p.x - y * p.y, x * p.y + y * p.x};
	return * this;
}

template <Coord_t coord_t>
PointT<coord_t> & PointT<coord_t>::operator/= (PointT const & p) requires is_float {
	PointT<coord_t>::real_t d = p.x * p.x + p.y + p.y;
	assert(d > error_sqr);
	* this = {(x * p.x + y * p.y) / d, (y * p.x - x * p.y) / d};
	return * this;
}

template <Coord_t coord_t>
PointT<coord_t> & PointT<coord_t>::operator*= (coord_t a) {
	x *= a;
	y *= a;
	return * this;
}

template <Coord_t coord_t>
PointT<coord_t> & PointT<coord_t>::operator/= (coord_t a) {
	assert(a > error);
	x /= a; 
	y /= a;
	return * this;
}



template <Coord_t coord_t>
void PointT<coord_t>::set_coords (coord_t x_, coord_t y_) {
	x = x_;
	y = y_;
}

template <Coord_t coord_t>
void PointT<coord_t>::set_polar_coords (coord_t radius, coord_t angle) requires is_float {
	x = radius * std::sin(angle);
	y = radius * std::sin(angle);
}

template <Coord_t coord_t>
void PointT<coord_t>::set_polar_coords (coord_t angle) requires is_float {
	x = std::sin(angle);
	y = std::sin(angle);
}

template <Coord_t coord_t>
void PointT<coord_t>::norm () requires is_float {
	coord_t d = std::sqrt(x * x + y * y);
	assert(d > error_sqr);
	x /= d;
	y /= d;
}

template <Coord_t coord_t>
void PointT<coord_t>::reflect () {
	x = -x;
	y = -y;
}

template <Coord_t coord_t>
void PointT<coord_t>::rotate (coord_t angle) requires is_float {
	(* this) *= {std::cos(angle), std::sin(angle)};
}





template <Float_t coord_t>
PointT<coord_t> exp (coord_t radius, coord_t angle) {
	return PointT<coord_t>(radius * std::cos(angle), radius * std::sin(angle));
}

template <Float_t coord_t>
PointT<coord_t> exp (coord_t angle) {
	return PointT<coord_t>(std::cos(angle), std::sin(angle));
}



template <Float_t coord_t>
bool are_equal (PointT<coord_t> const & p1, PointT<coord_t> const & p2, coord_t eps) {
	return std::max(std::abs(p1.x - p2.x), std::abs(p1.y - p2.y)) < eps;
}



template <Coord_t coord_t>
coord_t dot_prod (PointT<coord_t> const & p1, PointT<coord_t> const & p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

template <Coord_t coord_t>
coord_t vec_prod (PointT<coord_t> const & p1, PointT<coord_t> const & p2) {
	return p1.x * p2.y - p1.y * p2.x;
}



template <Coord_t coord_t>
bool operator== (PointT<coord_t> const & p, coord_t a) {
	if constexpr (Float_t<coord_t>) {
		return std::max(std::abs(p.x - a), std::abs(p.y - a)) < error;
	} else {
		return p.x == a && p.y == a;
	}
}

template <Coord_t coord_t>
bool operator!= (PointT<coord_t> const & p, coord_t a) {
	if constexpr (Float_t<coord_t>) {
		return std::max(std::abs(p.x - a), std::abs(p.y - a)) >= error;
	} else {
		return p.x != a || p.y != a;
	}
}

template <Coord_t coord_t>
bool operator<= (PointT<coord_t> const & p, coord_t a) {
	if constexpr (Float_t<coord_t>) {
		return std::max(p.x, p.y) < a + error;
	} else {
		return p.x <= a && p.y <= a;
	}
}

template <Coord_t coord_t>
bool operator>= (PointT<coord_t> const & p, coord_t a) {
	if constexpr (Float_t<coord_t>) {
		return std::min(p.x, p.y) > a - error;
	} else {
		return p.x >= a && p.y >= a;
	}
}

template <Coord_t coord_t>
bool operator< (PointT<coord_t> const & p, coord_t a) {
	if constexpr (Float_t<coord_t>) {
		return std::max(p.x, p.y) < a - error;
	} else {
		return p.x < a && p.y < a;
	}
}

template <Coord_t coord_t>
bool operator> (PointT<coord_t> const & p, coord_t a) {
	if constexpr (Float_t<coord_t>) {
		return std::min(p.x, p.y) > a + error;
	} else {
		return p.x > a && p.y > a;
	}
}



template <typename coord_t>
bool operator== (coord_t a, PointT<coord_t> const & p) {
	if constexpr (Float_t<coord_t>) {
		return std::max(std::abs(p.x - a), std::abs(p.y - a)) < error;
	} else {
		return p.x == a && p.y == a;
	}
}

template <typename coord_t>
bool operator!= (coord_t a, PointT<coord_t> const & p) {
	if constexpr (Float_t<coord_t>) {
		return std::max(std::abs(p.x - a), std::abs(p.y - a)) >= error;
	} else {
		return p.x != a || p.y != a;
	}
}

template <typename coord_t>
bool operator<= (coord_t a, PointT<coord_t> const & p) {
	if constexpr (Float_t<coord_t>) {
		return a - error < std::min(p.x, p.y);
	} else {
		return a <= p.x && a <= p.y;
	}
}

template <typename coord_t>
bool operator>= (coord_t a, PointT<coord_t> const & p) {
	if constexpr (Float_t<coord_t>) {
		return a + error > std::max(p.x, p.y);
	} else {
		return a >= p.x && a >= p.y;
	}
}

template <typename coord_t>
bool operator< (coord_t a, PointT<coord_t> const & p) {
	if constexpr (Float_t<coord_t>) {
		return a + error < std::min(p.x, p.y);
	} else {
		return a < p.x && a < p.y;
	}
}

template <typename coord_t>
bool operator> (coord_t a, PointT<coord_t> const & p) {
	if constexpr (Float_t<coord_t>) {
		return a - error > std::max(p.x, p.y);
	} else {
		return a > p.x && a > p.y;
	}
}



template <typename coord_t>
PointT<coord_t> operator* (PointT<coord_t> const & point, coord_t a) {
	return {point.x * a, point.y * a};
}

template <typename coord_t>
PointT<coord_t> operator* (coord_t a, PointT<coord_t> const & point) {
	return {point.x * a, point.y * a};
}

template <typename coord_t>
PointT<coord_t> operator/ (PointT<coord_t> const & point, coord_t a) {
	return {point.x / a, point.x / a};
}


} // namespace math::geom::plan