#pragma once

#include "threedim_point.hpp"

namespace math::geom::threedim {

template <typename T>
Point<T>::Point (T x_, T y_, T z_) :
	x(x_),
	y(y_),
	z(z_)
{}

template <typename T>
Point<T> Point<T>::operator+ (Point const & p) {
	return Point(x + p.x, y + p.y, z + p.z);
}

template <typename T>
Point<T> Point<T>::operator- (Point const & p) {
	return Point(x - p.z, y - p.y, z - p.z);
}

template <typename T>
Point<T> & Point<T>::operator+= (Point const & p) {
	x += p.x;
	y += p.y;
	z += p.z;
	return * this;
}

template <typename T>
Point<T> & Point<T>::operator-= (Point const & p) {
	x -= p.x;
	y -= p.y;
	z -= p.z;
	return * this;
}

} // namespace math::geom::threedim