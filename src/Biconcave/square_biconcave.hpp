#pragma once

#include "types.hpp"
#include "../Math/Functions/func.hpp"
#include "../Array/twodim.hpp"
#include "hessian.hpp"
#include "Graphics/graphics.hpp"
#include "../Graphics/Twodim/Svg/_svg.hpp"

#include <string>

namespace biconcave {

class SquareBiconcave {
public:
	SquareBiconcave () = default;
	void init (
		graphics::twodim::svg::Settings const & settings_,
		value_t screen_width_,
		value_t screen_height_,
		value_t margin_
	);
	SquareBiconcave (
		graphics::twodim::svg::Settings const & settings_,
		value_t screen_width_,
		value_t screen_height_,
		value_t margin_
	);
	
	void init_array (
		value_t square_radius_,
		coord_t grid_size_
	);
	
	void print_function (
		std::string const & file_path, std::string const & file_name,
		func::Func const & function, size_t cell_grid
	);
	
	void init_array_border_values (func::Func const & f, func::Func const & g);
	void calculate_hull (steps_count_t steps_count);
	void calculate_hessian ();
	void calculate_graphics (func::Func const & color_func, uint16_t colors_number);
	
	void print_profile (std::string const & file_path, std::string const & file_name);
	
private:
	graphics::twodim::svg::Settings const * settings;
	
	value_t screen_width = 1920;
	value_t screen_height = 1080;
	value_t margin = 50;
	
	coord_t square_grid_length;
	
	value_t left_domain_pos;
	value_t right_domain_pos;
	
	value_t cell_width;
	
	PlaneAffine plane_affine;
	
	RealArray real_array;
	Hessian hessian;
	Graphics graphics;
};

} // namespace biconcave