#pragma once

#include "../../Color/colors.hpp"

#include <optional>

namespace graphics::twodim {

enum class Linecap {butt, round, square};
enum class Linejoin {bevel, round, miter};

} // namespace graphics::twodim

namespace graphics::twodim::paint {

class Stroke {
public:
	Stroke ();
	explicit Stroke (
		color::RGB_O color_,
		coord_t width_,
		Linecap linecap = Linecap::round,
		Linejoin linejoin = Linejoin::round
	);
	
	bool is_empty () const;
	void clear ();
	
	color::RGB_O const & color () const;
	coord_t const & width () const;
	Linecap linecap () const;
	Linejoin linejoin () const;
	
	void assign_stroke (
		color::RGB_O color_,
		coord_t width_,
		Linecap linecap = Linecap::round,
		Linejoin linejoin = Linejoin::round
	);
	void assign_color (color::RGB_O color_);
	void assign_width (coord_t width_);
	void assign_linecap (Linecap linecap);
	void assign_linejoin (Linejoin linejoin);

private:
	bool _empty;
	color::RGB_O _color;
	double _width;
	uint8_t line_type;
	
};

} // namespace graphics::twodim::paint