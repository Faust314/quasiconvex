#pragma once

#include "types.hpp"
#include "fill.hpp"
#include "stroke.hpp"

namespace graphics::twodim {

class Paint {
public:
	Paint (painting::Fill const & fill_, painting::Stroke const & stroke_);
	Paint (
		color::RGB_O fill_color,
		color::RGB_O stroke_color,
		coord_t width,
		Linecap linecap = Linecap::round,
		Linejoin linejoin = Linejoin::round
	);
	
	Paint (painting::Fill const & fill_);
	Paint (color::RGB_O fill_color);
	
	Paint (painting::Stroke const stroke_);
	Paint (
		color::RGB_O color_,
		coord_t width_,
		Linecap linecap = Linecap::round,
		Linejoin linejoin = Linejoin::round
	);
	
	painting::Fill const & fill() const;
	painting::Fill & fill();
	painting::Stroke const & stroke() const;
	painting::Stroke & stroke();
	
private:
	painting::Fill _fill;
	painting::Stroke _stroke;
};

} // namespace graphics::twodim::paint