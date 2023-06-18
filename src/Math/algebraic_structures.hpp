#pragma once

#include <cstdint>

#include <fstream>

namespace math::type {
template <typename T, unsigned char d>
struct Point;
}

template <typename T, unsigned char d>
std::ostream & operator<< (std::ostream & ofs, math::type::Point<T,d> const & p);

namespace math::type {

template <typename T, unsigned char d>
struct Point {
	Point() = default;
	explicit Point(T* values_);
	
	template<typename T1>
	explicit Point(Point<T1, d> const & p);
	
	inline T & operator[] (uint16_t k);
	inline T const & operator[] (uint16_t k) const;
	
	Point<T, d> & operator = (Point<T,d> p);
	
	Point<T, d> operator+ (Point<T,d> p);
	Point<T, d> operator- (Point<T,d> p);
	Point<T, d> operator- ();
	Point<T, d> operator* (T r) requires requires (T r1, T r2) { r1 * r2; };
	
	void operator+= (Point<T,d> p);
	void operator-= (Point<T,d> p);
	
	void assign (T const & t);
	
	template<class Func>
	void modify (Func & f) requires requires (Func f, Point<T,d> & p) { f(p);};
	
	template<class Func, class T1>
	Point<T1,d> convert (Func & f)
	requires requires (Func f, Point<T,d> p) { std::is_same_v<T1, decltype(f(p))>;};
	
	template <typename T_, unsigned char d_>
	friend std::ostream & (::operator<< (std::ostream & ofs, Point<T_,d_> const & p));
	
private:
	T values[d];
	inline static uint8_t index = 0;
};

} // namespace math::type

#include "algebraic_structures.ipp"