#pragma once

#include "../types.hpp"
#include "../../Math/Geometry/Multidimensional/multi_point.hpp"

#include <vector>
#include <cmath>
#include <functional>

namespace array {

template<typename T, unsigned char d>
class Basic {
public:
	using Point = math::geom::multi::Point<array_coord_t,d>;
	
public:
	Basic () = default;
	void init (Point a_, Point b_);
	Basic (Point a_, Point b_);
	
	Point const & a () const;
	Point const & b () const;
	Point const & size () const;
	id_t const & volume () const;
	
	index_t get_dim () const;
	id_t get_shift () const;
	
	id_t get_hash (Point const & p);
	
	T & get_value (id_t hash);
	T const & get_value (id_t hash) const;
	
	T & operator() (Point const & p);
	T const & operator() (Point const & p) const;
	
	T approxim_value (math::geom::multi::Point<real_coord_t,d> p) requires requires (T t, double x) { x * t; x + t;};
	
private:
	std::vector<T> values;
	Point _a;
	Point _b;
	
	Point _size;
	id_t _volume;
	id_t _shift;
	
//	inline static uint8_t index = 0;
//	inline static uint8_t id = 0;
//	
//	inline static Point corner;
//	inline static Point hypercube_point;
//	inline static std::array<T, array_size_t(std::pow(2,d))> buffer;
//	inline static array_size_t hypercube_index;
//	inline static array_size_t support_hypercube_index;
//	
//	static const std::function<array_coord_t (double)> ceil;
};

//template<typename T, unsigned char d>
//const std::function<array_coord_t (double)> Basic<T,d>::ceil = [] (double x) { return std::ceil(x); };


} // namespace array
