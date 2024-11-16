#pragma once

#include "affine.hpp"

namespace math::geom::plan {

template <Coord_t coord_t>
PointT<coord_t> PlaneAffine<coord_t>::operator() (PointT<coord_t> const & p) {
	return {a * p.x + b * p.y + x0, c * p.x + d * p.y + y0};
}

} // namespace math::geom::plan