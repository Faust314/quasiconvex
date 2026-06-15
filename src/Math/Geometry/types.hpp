#pragma once

#include <concepts>
#include <type_traits>
#include <numbers>
#include <cstdint>

namespace math::geom {

extern double error;
extern double error_sqr;

template<typename coord_t>
concept Int_t = requires () {std::is_integral_v<coord_t>;};

template<typename coord_t>
concept Float_t = requires () {std::is_floating_point_v<coord_t>;};

template<typename coord_t>
concept Coord_t = Int_t<coord_t> || Float_t<coord_t>;

template<typename coord_t>
using Real_t = typename std::conditional<Int_t<coord_t>, double, coord_t>::type;







typedef double coord_t;
typedef uint8_t index_t;

} // namespace math::geom