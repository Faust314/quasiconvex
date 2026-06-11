#pragma once

#include "../model.hpp"
#include "../../../Array/Basic/basic.hpp"

namespace graphics::threedim::str {

class Profile {
private:
	using array_coord_t = array::array_coord_t;
	using ArrayPoint = math::geom::threedim::Point<array_coord_t>;
	
public:
	class ProfilePoint {
	public:
		ProfilePoint() = default;
		
		bool is_empty () const;
		void clear ();
		
		void assign_color (color::RGB const & color_);
		color::RGB & color ();
	
	private:
		bool _empty;
		color::RGB _color;
	};
	
public:
	Profile () = default;
	void init (ArrayPoint const & a, ArrayPoint const & b);
	Profile (ArrayPoint const & a, ArrayPoint const & b);
	
	array::Basic<ProfilePoint, 3> & profile_cells ();
	
	void output (Model & model, math::geom::threedim::Point<coord_t> a, math::geom::threedim::Point<coord_t> b);
	
private:
	array::Basic<ProfilePoint, 3> _profile_cells;
};

} // namespace graphics::threedim::str