#pragma once

#include "../Math/Geometry/Planimetry/point.tpp"

#include <cstdint>

namespace array {

typedef uint8_t dim_t;

typedef uint64_t value_id_t;
typedef int16_t coord_t;

using Point = math::geom::plan::PointT<coord_t>;

} // namespace array