#pragma once

#include "../model.hpp"
#include "../../../Array/Basic/basic.hpp"

namespace graphics::threedim::str {

class Func {
private:
	using array_coord_t = array::array_coord_t;
	using ArrayPoint = math::geom::multi::Point<array_coord_t, 2>;
	
public:
	class FuncPoint {
	public:
		FuncPoint() = default;
		
		bool is_empty () const;
		void clear ();
		
		color::RGB & color ();
		coord_t & value ();
		
	private:
		constexpr static coord_t _empty = std::numeric_limits<coord_t>::max();
	
		color::RGB _color;
		coord_t _value = _empty;
	};
	
public:
	Func () = default;
	void init (ArrayPoint const & a, ArrayPoint const & b);
	Func (ArrayPoint const & a, ArrayPoint const & b);
	
	array::Basic<FuncPoint, 2> & func_points ();
	
	void output (Model & model, math::geom::multi::Point<coord_t, 2> a, math::geom::multi::Point<coord_t, 2> b);
	
private:
	array::Basic<FuncPoint, 2> _func_points;
};

} // namespace graphics::threedim::str