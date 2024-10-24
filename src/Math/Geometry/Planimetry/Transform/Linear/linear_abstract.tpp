#pragma once
#include "linear_abstract.hpp"

namespace math::geom::plan::detail {

template <Coord_t coord_t>
template <LinearT_c<coord_t> LinearTransform>
requires Int_t<coord_t>
LinearAT_int<coord_t>::LinearAT_int (LinearTransform const & linear) {
	reset(linear);
}



template <Coord_t coord_t>
ScalarT<coord_t> LinearAT_int<coord_t>::get_scalar () {
	return ScalarT<coord_t>(* this);
}

template <Coord_t coord_t>
DiagonalT<coord_t> LinearAT_int<coord_t>::get_diagonal () {
	return DiagonalT<coord_t>(* this);
}

template <Coord_t coord_t>
OrthogonalT<coord_t> LinearAT_int<coord_t>::get_orthogonal () {
	return OrthogonalT<coord_t>(* this);
}

template <Coord_t coord_t>
HomothetyT<coord_t> LinearAT_int<coord_t>::get_homothety () {
	return HomothetyT<coord_t>(* this);
}

template <Coord_t coord_t>
LinearT<coord_t> LinearAT_int<coord_t>::get_linear () {
	return LinearT<coord_t>(* this);
}



template <Coord_t coord_t>
bool LinearAT_int<coord_t>::is_degenerate () const {
	return orientation() == 0;
}

template <Coord_t coord_t>
bool LinearAT_int<coord_t>::is_positive_oriented () const {
	return orientation() == 1;
}

template <Coord_t coord_t>
bool LinearAT_int<coord_t>::is_negative_oriented () const {
	return orientation() == -1;
}





template <Coord_t coord_t>
template <LinearT_c<coord_t> LinearTransform>
LinearAT_float<coord_t>::LinearAT_float (LinearTransform const & linear) {
	reset(linear);
}

} // namespace math::geom::plan::detail