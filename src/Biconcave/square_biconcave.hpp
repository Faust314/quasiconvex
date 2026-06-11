#pragma once

#include "types.hpp"
#include "../Math/Functions/func.hpp"
#include "../Array/twodim.hpp"
#include "hessian.hpp"
#include "Graphics/graphics.hpp"
#include "../Graphics/Twodim/Svg/_svg.hpp"

#include <string>
#include <random>

namespace biconcave {

template <class Func>
concept AddFunc = requires (Func f, steps_count_t step) {
	std::is_same_v<decltype(f(step)), value_t>;
};

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
		coord_t grid_radius_length_
	);
	template <AddFunc Func>
	void generate_borders (
		std::mt19937 & gen, Func f, steps_count_t total_steps
	);
	template <AddFunc Func>
	void generate_biconcave_function_with_borders (
		std::mt19937 & gen, Func f, steps_count_t total_steps, steps_count_t minimal_steps
	);
	
	void calculate_min_function (steps_count_t steps_count);
	void calculate_max_function ();
	
	value_t calculate_min_function_by_border_and_compare (steps_count_t steps_count);
	
	void calculate_hessian ();
	void calculate_graphics (func::Func const & color_func, uint16_t colors_number);
	
	void print_function (std::string const & file_path, std::string const & file_name);
	void print_profile (std::string const & file_path, std::string const & file_name);
	
private:
	graphics::twodim::svg::Settings const * settings;
	
	value_t screen_width = 1920;
	value_t screen_height = 1080;
	value_t margin = 50;
	
	coord_t grid_radius_length;
	coord_t grid_length;
	
	value_t cell_width;
	
	PlaneAffine plane_affine;
	
	RealArray real_array;
	Hessian hessian;
	Graphics graphics;
};

} // namespace biconcave