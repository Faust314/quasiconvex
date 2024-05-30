#pragma once

#include "../Math/math.hpp"

#include <cstdint>

namespace ornstein {

typedef uint8_t index_t;
typedef double value_t;
typedef double coord_t;
typedef int32_t array_coord_t;
template <int d>
using ArrayPoint = math::geom::multi::Point<array_coord_t, d>;
template <int d>
using Point = math::geom::multi::Point<coord_t, d>;

} // namespace ornstein
