#pragma once

#include "../../../types.hpp"
#include "../svg_config.hpp"
#include "../../Painting/painting.hpp"

#include <fstream>

namespace graphics::twodim::svg {

struct str {
	static void file_begin (coord_t width = settings->display_width, coord_t height = settings->display_height);
	static void file_end ();
	
	static void layer_begin (group_id_t layer_id, std::string const & layer_label;
	static void layer_begin (group_id_t layer_id);
	static void layer_end ();
	
	static void group_begin (group_id_t group_id);
	static void group_begin (std::string group_id);
	static void group_end ();
	
	static void painting (paint::Fill const & fill);
	static void painting (paint::Stroke const & stroke);
	static void painting (paint::Fill const & fill, paint::Stroke const & stroke);
	static void painting (Paint const & paint);
	
private:
	friend Settings;
	friend OutputParameters;
	
	static Settings const * settings;
	static OutputParameters const * parameters;
};

} // namespace graphics::twodim::svg