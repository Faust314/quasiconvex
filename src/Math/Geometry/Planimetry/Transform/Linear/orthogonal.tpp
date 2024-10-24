#pragma once
#include "orthogonal.hpp"

#include <cassert>
#include <cmath>

namespace math::geom::plan {

template <Coord_t coord_t>
void OrthogonalT<coord_t>::reset () {
	_angle = 0;
	_is_reflected = false;
}

template <Coord_t coord_t>
void OrthogonalT<coord_t>::reset (ScalarT<coord_t> const & scalar) {
	assert(scalar.is_orthogonal());
	if (scalar.scale() > 0) {
		_angle = 0;
	} else {
		_angle = std::numbers::pi_v<coord_t>;
	}
}

template <Coord_t coord_t>
void OrthogonalT<coord_t>::reset (DiagonalT<coord_t> const & diagonal) {
	assert(diagonal.is_orthogonal());
	if (diagonal.a() > 0) {
		_angle = std::numbers::pi_v<coord_t>;
		_is_reflected = diagonal.b() > 0 ? true : false;
	} else {
		_angle = 0;
		_is_reflected = diagonal.b() < 0 ? true : false;
	}
}

template <Coord_t coord_t>
void OrthogonalT<coord_t>::reset (OrthogonalT<coord_t> const & orthogonal) {
	_angle = orthogonal._angle;
	_is_reflected = orthogonal._is_reflected;
}

template <Coord_t coord_t>
void OrthogonalT<coord_t>::reset (HomothetyT<coord_t> const & homothety) {
	assert(homothety.is_orthogonal());
	_angle = std::atan2(homothety.a(), homothety.b());
	_angle = _angle < 0 ? _angle + 2 * std::numbers::pi_v<coord_t> : _angle;
	_is_reflected = homothety.is_reflected();
}

template <Coord_t coord_t>
void OrthogonalT<coord_t>::reset (LinearT<coord_t> const & linear) {
	assert(linear.is_orthogonal());
	_angle = std::atan2(linear.a(), linear.c());
	_is_reflected = linear.is_negative_oriented;
}

template <Coord_t coord_t>
void OrthogonalT<coord_t>::reset (coord_t angle_, bool is_reflected_) {
	_angle = angle_;
	_is_reflected = is_reflected_;
}

template <Coord_t coord_t>
OrthogonalT<coord_t>::OrthogonalT (coord_t angle_, bool is_reflected_) :
	_angle(angle_), _is_reflected(is_reflected_)
{}



template <Coord_t coord_t>
linear_t OrthogonalT<coord_t>::type () const {
	return linear_t::orthogonal;
}



template <Coord_t coord_t>
bool OrthogonalT<coord_t>::is_scalar () const {
	return ! _is_reflected && (std::abs(_angle) < error || std::abs(_angle - std::numbers::pi_v<coord_t>) < error);
}

template <Coord_t coord_t>
bool OrthogonalT<coord_t>::is_diagonal () const {
	return std::abs(_angle) < error || std::abs(_angle - std::numbers::pi_v<coord_t>) < error;
}

template <Coord_t coord_t>
bool OrthogonalT<coord_t>::is_orthogonal () const {
	return true;
}

template <Coord_t coord_t>
bool OrthogonalT<coord_t>::is_homothety () const {
	return true;
}



template <Coord_t coord_t>
coord_t OrthogonalT<coord_t>::angle () const {
	return _angle;
}

template <Coord_t coord_t>
coord_t OrthogonalT<coord_t>::is_reflected () const {
	return _is_reflected;
}



template <Coord_t coord_t>
coord_t OrthogonalT<coord_t>::det () const {
	return _is_reflected ? -1 : 1;
}

template <Coord_t coord_t>
int8_t OrthogonalT<coord_t>::orientation () const {
	return _is_reflected ? -1 : 1;
}



template <Coord_t coord_t>
OrthogonalT<coord_t> OrthogonalT<coord_t>::operator* (OrthogonalT const & orthogonal) const {
	return {
		_angle + (_is_reflected ? - orthogonal._angle : orthogonal._angle),
		_is_reflected ^ orthogonal._is_reflected
	};
}



template <Coord_t coord_t>
OrthogonalT<Real_t<coord_t>> OrthogonalT<coord_t>::get_inverse () const {
	return {_is_reflected ? _angle : - _angle, _is_reflected};
}

template <Coord_t coord_t>
void OrthogonalT<coord_t>::inverse () const {
	_angle = _is_reflected ? _angle : - _angle;
}



template <Coord_t coord_t>
void OrthogonalT<coord_t>::apply (PointT<coord_t> & point) {
	coord_t a = std::cos(_angle);
	coord_t b = std::sin(_angle);
	point = {
		a * point.x + (_is_reflected ? 1 : -1) * b * point.y,
		b * point.x + (_is_reflected ? -1 : 1) * a * point.y
	};
}

template <Coord_t coord_t>
PointT<coord_t> OrthogonalT<coord_t>::operator() (PointT<coord_t> const & point) const {
	coord_t a = std::cos(_angle);
	coord_t b = std::sin(_angle);
	return {
		a * point.x + (_is_reflected ? 1 : -1) * b * point.y,
		b * point.x + (_is_reflected ? -1 : 1) * a * point.y
	};
}



template <Coord_t coord_t>
coord_t OrthogonalT<coord_t>::get_positive_angle (coord_t angle_) {
	return angle_ - 2 * std::numbers::pi_v<coord_t> * std::floor(angle_ / (2 * std::numbers::pi_v<coord_t>));
}

template <Coord_t coord_t>
coord_t OrthogonalT<coord_t>::get_signed_angle (coord_t angle_) {
	angle_ = angle_ - 2 * std::numbers::pi_v<coord_t> * std::floor(angle_ / (2 * std::numbers::pi_v<coord_t>));
	return angle_ < 0 ? angle_ + 2 * std::numbers::pi_v<coord_t> : angle_;
}

} // namespace math::geom::plan
