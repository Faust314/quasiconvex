#pragma once

#include "../Math/Geometry/Planimetry/point.tpp"
#include "../Math/Geometry/types.hpp"

#include <cstdint>

namespace array {

typedef uint8_t dim_t;

typedef uint64_t value_id_t;
typedef int16_t coord_t;

using Point = math::geom::plan::PointT<coord_t>;





typedef int64_t id_t;
typedef int32_t array_coord_t;
typedef double real_coord_t;
using index_t = math::geom::index_t;

} // namespace array