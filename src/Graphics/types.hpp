#pragma once

#include "../Math/Geometry/Planimetry/point.hpp"
#include "../Math/Geometry/Planimetry/rectangular.hpp"

#include <cstdint>
#include <concepts>
#include <string>

namespace graphics {

typedef double coord_t;
typedef uint16_t group_id_t;
typedef uint32_t object_id_t;

namespace color {

typedef uint8_t arg_t;

class RGB;

template<class T>
concept color_c = requires (T t) {
	std::is_same_v<decltype(t.to_string_16()), std::string>;
	std::is_convertible_v<T, RGB>;
};

} // namespace color'

using Point = math::geom::plan::PointT<coord_t>;
using Rectangular = math::geom::plan::RectangularT<coord_t>;

} // namespace graphics