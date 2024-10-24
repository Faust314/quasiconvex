#pragma once
#include "scalar.hpp"

#include <cassert>

namespace math::geom::plan::detail {

template <Coord_t coord_t>
void ScalarT_int<coord_t>::reset () {
	_scale = 1;
}

template <Coord_t coord_t>
void ScalarT_int<coord_t>::reset (ScalarT<coord_t> const & scalar) {
	_scale = scalar.scale();
}

template <Coord_t coord_t>
void ScalarT_int<coord_t>::reset (DiagonalT<coord_t> const & diagonal) {
	assert(scalar.is_scalar());
	_scale = diagonal.a();
}

template <Coord_t coord_t>
void ScalarT_int<coord_t>::reset (HomothetyT<coord_t> const & homothety) {
	assert(homothety.is_scalar());
	_scale = homothety.a();
}

template <Coord_t coord_t>
void ScalarT_int<coord_t>::reset (LinearT<coord_t> const & linear) {
	assert(scalar.is_scalar());
	_scale = linear.a();
}

template <Coord_t coord_t>
void ScalarT_int<coord_t>::reset (coord_t scale_) {
	_scale = scale_;
}



template <Coord_t coord_t>
ScalarT_int<coord_t>::ScalarT_int (coord_t scale_) :
	_scale(scale_)
{}



template <Coord_t coord_t>
linear_t ScalarT_int<coord_t>::type () const {
	return linear_t::scalar;
}



template <Coord_t coord_t>
bool ScalarT_int<coord_t>::is_scalar () const {
	return true;
}

template <Coord_t coord_t>
bool ScalarT_int<coord_t>::is_diagonal () const {
	return true;
}

template <Coord_t coord_t>
bool ScalarT_int<coord_t>::is_homothety () const {
	return true;
}



template <Coord_t coord_t>
coord_t ScalarT_int<coord_t>::scale () const {
	return _scale;
}



template <Coord_t coord_t>
coord_t ScalarT_int<coord_t>::det () const {
	return _scale * _scale;
}

template <Coord_t coord_t>
int8_t ScalarT_int<coord_t>::orientation () const {
	if constexpr (Int_t<coord_t>) {
		return _scale > 0 ? 1 : _scale < -0 ? -1 : 0;
	} else {
		return _scale > error ? 1 : _scale < -error ? -1 : 0;
	}
}



template <Coord_t coord_t>
ScalarT_int<coord_t> ScalarT_int<coord_t>::operator* (ScalarT_int const & linear) const {
	return {_scale * linear._scale};
}



template <Coord_t coord_t>
ScalarT_int<Real_t<coord_t>> ScalarT_int<coord_t>::get_inverse () const {
	assert(! LinearAT<coord_t>::is_degenerate());
	return {1 / Real_t<coord_t>(_scale)};
}



template <Coord_t coord_t>
void ScalarT_int<coord_t>::apply (PointT<coord_t> & point) {
	point.x *= _scale;
	point.y *= _scale;
}

template <Coord_t coord_t>
PointT<coord_t> ScalarT_int<coord_t>::operator() (PointT<coord_t> const & p) const {
	return {_scale * p.x, _scale * p.y};
}





template <Coord_t coord_t>
void ScalarT_float<coord_t>::reset (OrthogonalT<coord_t> const & orthogonal) {
	assert(orthogonal.is_scalar());
	ScalarT_int<coord_t>::_scale = orthogonal.angle() < std::numbers::pi / 2 ? 1 : -1;
}



template <Coord_t coord_t>
bool ScalarT_float<coord_t>::is_orthogonal () const {
	return std::abs(std::abs(ScalarT_int<coord_t>::_scale) - 1) < error;
}

template <Coord_t coord_t>
void ScalarT_float<coord_t>::inverse () const {
	assert(! LinearAT<coord_t>::is_degenerate());
	ScalarT_int<coord_t>::_scale = 1 / ScalarT_int<coord_t>::_scale;
}


} // namespace math::geom::plan::detail
