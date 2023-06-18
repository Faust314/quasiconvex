#pragma once

#include "types.hpp"
#include "../Math/algebraic_structures.hpp"

#include <vector>
#include <cmath>
#include <functional>

namespace array {

template<typename T, unsigned char d>
class Basic {
public:
	using Point = math::type::Point<coord_t,d>;
	
private:
	std::vector<T> values;
	uint8_t _dim;
	Point _a;
	Point _b;
	Point _size;
	
	array_size_t _volume;
	
	array_size_t _shift;
	
	inline static uint8_t index = 0;
	inline static uint8_t id = 0;
	
	inline static Point corner;
	inline static Point hypercube_point;
	inline static std::array<T, array_size_t(std::pow(2,d))> buffer;
	inline static array_size_t hypercube_index;
	inline static array_size_t support_hypercube_index;
	
	static const std::function<coord_t (double)> ceil;
	
public:
	
	Basic(Point a_, Point b_);
	
	Point const & a() const;
	Point const & b() const;
	Point const & size() const;
	
	uint8_t get_dim() const;
	array_size_t get_shift() const;
	
	T & get_value(array_size_t hash);
	T const & get_value(array_size_t hash) const;
	
	T & operator() (Point const & p);
	T const & operator() (Point const & p) const;
	
	T aproxim_value(math::type::Point<double,d> p) requires requires (T t, double x) { x * t; x + t;};
};

template<typename T, unsigned char d>
const std::function<coord_t (double)> Basic<T,d>::ceil = [] (double x) { return std::ceil(x); };


} // namespace array

#include "basic.ipp"