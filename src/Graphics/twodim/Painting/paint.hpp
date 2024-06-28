#pragma once

#include "types.hpp"
#include "fill.hpp"
#include "stroke.hpp"

namespace graphics::twodim {

class Paint {
public:
	Paint (paint::Fill const & fill_, paint::Stroke const & stroke_);
	Paint (
		color::RGB_O fill_color,
		color::RGB_O stroke_color,
		coord_t width,
		Linecap linecap = Linecap::round,
		Linejoin linejoin = Linejoin::round
	);
	
	Paint (paint::Fill const & fill_);
	Paint (color::RGB_O fill_color);
	
	Paint (paint::Stroke const stroke_);
	Paint (
		color::RGB_O color_,
		coord_t width_,
		Linecap linecap = Linecap::round,
		Linejoin linejoin = Linejoin::round
	);
	
	paint::Fill const & fill() const;
	paint::Fill & fill();
	paint::Stroke const & stroke() const;
	paint::Stroke & stroke();
	
private:
	paint::Fill _fill;
	paint::Stroke _stroke;
};

} // namespace graphics::twodim::paint