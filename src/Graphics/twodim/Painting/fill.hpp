#pragma once

#include "../../Color/colors.hpp"

#include <optional>

namespace graphics::twodim::paint {

class Fill {
public:
	Fill ();
	explicit Fill (color::RGB_O color_);
	
	bool is_empty () const;
	void clear ();
	
	color::RGB_O const & color () const;
	
	void assign_color (color::RGB_O const & color_);
	
private :
	bool _empty;
	color::RGB_O _color;
};

} // namespace graphics::twodim::paint