#pragma once

#include "multi_point.hpp"

namespace math::geom::multi {

template <typename T, unsigned char d>
template <typename T1>
Point<T, d>::Point(Point<T1, d> const & p) {
	for (uint8_t index = 0; index < d; index++) {
		values[index] = T(p[index]);
	}
}

template <typename T, unsigned char d>
Point<T, d>::Point (T * values_)
{
	for (index_t index = 0; index < d; index++) {
		values[index] = values_[index];
	}
}

template <typename T, unsigned char d>
Point<T, d>::Point (std::vector<T> const & values_) {
	for (index_t index = 0; index < d; index++) {
		values[index] = values_[index];
	}
}

template <typename T, unsigned char d>
Point<T, d>::Point (std::initializer_list<T> values_) {
	for (index_t index = 0; index < d; index++) {
		values[index] = * (values_.begin() + index);
	}
}

template <typename T, unsigned char d>
Point<T, d> & Point<T, d>::operator= (Point<T, d> p) {
	for (index_t index = 0; index < d; index++) {
		values[index] = p.values[index];
	}
	return *this;
}

template <typename T, unsigned char d>
T & Point<T, d>::operator[] (index_t k) {
	return values[k];
}

template <typename T, unsigned char d>
T const & Point<T, d>::operator[] (index_t k) const {
	return values[k];
}

template <typename T, unsigned char d>
Point<T, d> Point<T, d>::operator+ (Point<T, d> p) {
	Point p1;
	for (index_t index = 0; index < d; index++) {
		p1.values[index] = values[index] + p.values[index];
	}
	return p1;
}

template <typename T, unsigned char d>
Point<T, d> Point<T, d>::operator- (Point<T, d> p) {
	Point p1;
	for (index_t index = 0; index < d; index++) {
		p1.values[index] = values[index] - p.values[index];
	}
	return p1;
}

template <typename T, unsigned char d>
Point<T, d> Point<T, d>::operator- () {
	Point p;
	for (index_t index = 0; index < d; index++) {
		p.values[index] = - values[index];
	}
	return p;
}

template <typename T, unsigned char d>
Point<T, d> Point<T, d>::operator* (T r) requires requires (T r1, T r2) { r1 * r2; } {
	Point p;
	for (index_t index = 0; index < d; index++) {
		p.values[index] = r * values[index];
	}
	return p;
}

template <typename T, unsigned char d>
void Point<T, d>::operator+= (Point<T, d> p) {
	for (index_t index = 0; index < d; index++) {
		values[index] += values[index];
	}
}

template <typename T, unsigned char d>
void Point<T, d>::operator-= (Point<T, d> p) {
	for (index_t index = 0; index < d; index++) {
		values[index] -= values[index];
	}
}

template <typename T, unsigned char d>
void Point<T, d>::assign (T const & t) {
	for (index_t index = 0; index < d; index++) {
		values[index] = t;
	}
}

template <typename T, unsigned char d>
template <class Func>
void Point<T, d>::modify (Func const & f) requires requires (Func f_, T & p) { f_(p); } {
	for (index_t index = 0; index < d; index++) {
		f(values[index]);
	}
}

template <typename T, unsigned char d>
template <class T1, class Func>
Point<T1, d> Point<T, d>::convert (Func const & f)
requires requires (Func f_, T & p) { std::is_same_v<T1, decltype(f_(p))>; } {
	Point<T1, d> p1;
	for (index_t index = 0; index < d; index++) {
		p1[index] = f(values[index]);
	}
	return p1;
}

} // namespace math::geom::multi

template <typename T, unsigned char d>
std::ostream & operator<< (std::ostream & ofs, math::geom::multi::Point<T, d> const & p) {
	ofs << "(";
	for (math::geom::index_t index = 0; index < d - 1; index++) {
		ofs << p.values[math::geom::multi::Point<T,d>::index] << ", ";
	}
	ofs << p.values[d-1] << ")";
	return ofs;
}