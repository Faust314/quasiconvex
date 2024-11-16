#pragma once

#include "../point.tpp"

namespace math::geom::plan {

template <Coord_t coord_t>
struct PlaneAffine {
	coord_t a = 1;
	coord_t b = 0;
	coord_t c = 0;
	coord_t d = 1;
	coord_t x0 = 0;
	coord_t y0 = 0;
	
	PointT<coord_t> operator() (PointT<coord_t> const & p);
};

} // namespace math::geom::plan