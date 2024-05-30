#pragma once

#include "../types.hpp"

#include <cstdint>
#include <fstream>
#include <vector>

namespace math::geom::multi {

template <typename T, unsigned char d>
struct Point;

} // namespace math::geom::multi



template <typename T, unsigned char d>
std::ostream & operator<< (std::ostream & ofs, math::geom::multi::Point<T,d> const & p);



namespace math::geom::multi {

template <typename T, unsigned char d>
class Point {
public:
	Point () = default;
	Point (T* values_);
	Point (std::vector<T> const & values_);
	Point (std::initializer_list<T> values_);
	
	// TODO convertible T1 -> T
	template<typename T1>
	explicit Point(Point<T1, d> const & p);
	
	T & operator[] (index_t k);
	T const & operator[] (index_t k) const;
	
	Point<T, d> & operator = (Point<T,d> p);
	
	Point<T, d> operator+ (Point<T,d> p);
	Point<T, d> operator- (Point<T,d> p);
	Point<T, d> operator- ();
	Point<T, d> operator* (T r) requires requires (T r1, T r2) { r1 * r2; };
	
	void operator+= (Point<T,d> p);
	void operator-= (Point<T,d> p);
	
	void assign (T const & t);
	
	template<class Func>
	void modify (Func const & f) requires requires (Func f_, T & p) { f_(p);};
	
	template<class T1, class Func>
	Point<T1,d> convert (Func const & f)
	requires requires (Func f_, T & p) { std::is_same_v<T1, decltype(f_(p))>;};
	
	template <typename T_, unsigned char d_>
	friend std::ostream & operator<< (std::ostream & ofs, Point<T_,d_> const & p);
	
private:
	T values[d];
};
	
} // namespace math::geom::multi