#pragma once

#include "fill.hpp"
#include "stroke.hpp"

namespace graphics::twodim {

class Style {
public:
	Style (paint::Fill const & fill_, paint::Stroke const & stroke_);
	Style (
		color::RGB_O fill_color,
		color::RGB_O stroke_color,
		coord_t width,
		Linecap linecap = Linecap::round,
		Linejoin linejoin = Linejoin::round
	);
	
	Style (paint::Fill const & fill_);
	Style (color::RGB_O fill_color);
	
	Style (paint::Stroke const stroke_);
	Style (
		color::RGB_O color_,
		coord_t width_,
		Linecap linecap = Linecap::round,
		Linejoin linejoin = Linejoin::round
	);
	
	paint::Fill & fill();
	paint::Stroke & stroke();
	
private:
	paint::Fill _fill;
	paint::Stroke _stroke;
};

} // namespace graphics::twodim::paint