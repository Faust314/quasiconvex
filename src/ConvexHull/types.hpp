#pragma once

#include "../Array/twodim.hpp"

namespace hull {

typedef array::value_id_t array_size_t;
typedef array::coord_t coord_t;

typedef uint16_t iter_id_t;

using Point = math::geom::plan::PointT<coord_t>;

} // namespace hull