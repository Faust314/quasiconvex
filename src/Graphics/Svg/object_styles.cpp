#include "object_styles.hpp"

namespace graphics::svg::object {

RGB_O::RGB_O (uint8_t r, uint8_t g, uint8_t b, double t_) :
	rgb(r,g,b),
	t(t_)
{ }

RGB_O::RGB_O (RGB const & rgb_, double t_) :
	rgb(rgb_),
	t(t_)
{ }





void print (std::ofstream & ofs, Stroke const & stroke, Fill const & fill) {

}





Fill::Fill () :
	empty(true),
	color(RGB_O())
{ }

Fill::Fill (RGB_O color_) :
	empty(false),
	color(color_)
{ }

std::string Fill::operator() () const {
	std::string fill;
	if (empty) {
		fill == "fill:none";
		return fill;
	}
	fill += "stroke:#" + color.rgb.to_string_16() + ";";
	if(color.t != 1.0) {
		fill += "stroke-opacity:" + std::to_string(color.t);
	}
	
	return fill;
}



std::string style(Fill const & fill) {
	std::string style;
	style += "style=\"" + fill() + "\"";
	
	return style;
}





Stroke::Stroke () :
	empty(true),
	color(RGB_O()),
	width(5),
	linecap(Linecap::round),
	linejoin(Linejoin::round)
{ }

Stroke::Stroke (RGB_O color_, double width_, Linecap linecap_, Linejoin linejoin_) :
	empty(false),
	color(color_),
	width(width_),
	linecap(linecap_),
	linejoin(linejoin_)
{ }

std::string Stroke::operator() () const {
	std::string stroke;
	if (empty) {
		stroke += "stroke:none";
		return stroke;
	}
	stroke += "stroke:#" + color.rgb.to_string_16() + ";";
	stroke += "stroke-width:" + std::to_string(width) + ";";
	stroke += "stroke-linecap:" + Stroke::linecaps[int(linecap)] + ";";
	stroke += "stroke-linejoin:" + Stroke::linejoins[int(linejoin)] + ";";
	if(color.t != 1.0) {
		stroke += "stroke-opacity:" + std::to_string(color.t);
	}
	
	return stroke;
}



std::string style(Stroke const & stroke) {
	std::string style;
	style += "style=\"" + stroke() + "\"";
	
	return style;
}

std::string style(Fill const & fill, Stroke const & stroke) {
	std::string style;
	style += "style=\"" + fill() + ";" + stroke() + "\"";
	
	return style;
}

} // namespace graphics::svg::object

