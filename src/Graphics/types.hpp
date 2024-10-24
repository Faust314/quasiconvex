#pragma once

#include "../Math/Geometry/Planimetry/point.hpp"
#include "../Math/Geometry/Planimetry/Transform/Linear/diagonal.hpp"
#include "../Math/Geometry/Planimetry/Transform/affine.hpp"
#include "../Math/Geometry/Planimetry/types.hpp"

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

template <class T>
concept Transform_t = math::geom::plan::Transform_T<coord_t, T>;

using Point = math::geom::plan::PointT<coord_t>;
using Rectangular = math::geom::plan::RectangularT<coord_t>;
using Affine = math::geom::plan::AffineT<coord_t>;

static_assert(Transform_t<Rectangular>, "Class Rectangular is not a Transform.");
static_assert(Transform_t<Affine>, "Class Affine is not a Transform.");

} // namespace graphics