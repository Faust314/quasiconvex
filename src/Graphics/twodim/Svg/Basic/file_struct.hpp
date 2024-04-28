#pragma once

#include "../svg_config.hpp"

#include <fstream>

namespace graphics::twodim::svg {

struct str {
	static void file_begin (coord_t width = settings->display_width, coord_t height = settings->display_height);
	static void file_end ();
	
	static void layer_begin ();
	static void layer_end ();
	
	static void group_begin ();
	static void group_end ();
	
	static void painting ();
	
private:
	friend Settings;
	friend OutputParameters;
	
	static Settings const * settings;
	static OutputParameters const * parameters;
};

} // namespace graphics::twodim::svg