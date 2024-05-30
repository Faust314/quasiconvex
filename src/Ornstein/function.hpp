#pragma once

#include "types.hpp"
#include "../Array/array.hpp"

namespace ornstein {

template<int d>
class Function {
public:
	using linearity = math::geom::multi::Point<bool,d>;
	
public:
	Function () = default;
	void init (value_t p_, value_t c_, array_coord_t n_, coord_t l_ = 1);
	Function (value_t p_, value_t c_, array_coord_t n_, coord_t l_ = 1);
	
	array::Basic<value_t, d> const & values () const;
	
	value_t const & p () const;
	value_t const & c () const;
	
	array_coord_t const & n () const;
	coord_t const & l () const;
	value_t const & delta () const;
	
	void calculate_convex_hull (uint16_t number = 1);
	
	void calculate_linearity ();
	
	array::Basic<linearity, d> const & linearity_values () const;
	
private:
	array::Basic<value_t, d> _values;
	
	value_t _p;
	value_t _c;
	
	array_coord_t _n;
	coord_t _l;
	value_t _delta;
	value_t sqr_delta;
	
	struct F {
		F (array::Basic<value_t, d> & values_);
		
		array::Basic<value_t, d> * values;
		array_coord_t a;
		array_coord_t b;
		
		value_t & operator() (array_coord_t id);
	};
	F f;
	
	void init_array ();
	
	void convex_hull (index_t dir);
	
	array::Basic<linearity, d> _linearity_values;
	
	static bool onedim_linearity (value_t derivative);
};
	
} // namespace ornstein