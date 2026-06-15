#pragma once

#include "../types.hpp"

namespace math::geom::threedim {

template <typename T>
class Point {
public:
	T x;
	T y;
	T z;
	
	Point (T x_, T y_, T z_);
	
	Point operator + (Point const & p);
	Point operator - (Point const & p);
	Point & operator += (Point const & p);
	Point & operator -= (Point const & p);
};
	
} // namespace math::geom