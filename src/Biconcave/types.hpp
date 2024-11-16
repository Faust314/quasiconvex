#pragma once

#include "../Array/twodim.tpp"
#include "../ConvexHull/biconvex_handler.tpp"
#include "../Math/Geometry/Planimetry/Transform/affine.tpp"

namespace biconcave {

typedef array::dim_t dim_t;

typedef double value_t;
typedef array::value_id_t value_id_t;
typedef array::coord_t coord_t;

typedef uint16_t steps_count_t;

using ArrayPoint = math::geom::plan::PointT<coord_t>;
using Point = math::geom::plan::PointT<value_t>;
using PlaneAffine = math::geom::plan::PlaneAffine<value_t>;

using RealArray = array::Twodim<value_t>;
using HullHandler = hull::HullHandler<value_t>;

} // namespace biconvex