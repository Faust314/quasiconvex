#include "../modes.hpp"

#include "../../Ornstein/function.tpp"

#include <iostream>

namespace modes::working {

double f (double x) {
	return 5 * std::sin(x * 1000);
}

void ornstein () {
	DirStruct dirs;
	dirs.basic_init("final");
	
	constexpr uint8_t dim = 3;
	ornstein::coord_t p = 1.1;
	ornstein::coord_t c = 0.1;
	
	ornstein::array_coord_t n = 40;
	ornstein::coord_t l = 5;
	ornstein::array_coord_t w = 30;
	ornstein::array_coord_t du = 1;
	uint16_t N = 50;
	
	if (w >= n) {
		throw "error";
	}
	ornstein::Function<dim> orn(p, c, n, l);
	orn.calculate_convex_hull(N);
	orn.calculate_linearity();
	ornstein::Function<dim>::linearity const * lin;
	
	
	
//	graphics::threedim::Model func_model;
//	graphics::threedim::str::Func func({-orn.n() + 1,-orn.n() + 1}, {orn.n() - 1, orn.n() - 1});
//	
//	graphics::threedim::str::Func::FuncPoint * func_point;
//	for (ornstein::array_coord_t x = -orn.n() + 1; x < orn.n(); x++) {
//		for (ornstein::array_coord_t y = -orn.n() + 1; y < orn.n(); y++) {
//			func_point = & func.func_points()({x, y});
//			lin = & orn.linearity_values()({x, y, coord});
//			func_point->value() = orn.values()({x, y, coord});
//			func_point->color() = graphics::color::RGB(
//				255 * (* lin)[0],
//				255 * (* lin)[1],
//				255 * (* lin)[2]
//			);
//		}
//	}
//	
//	func.output(func_model, {-orn.l(), -orn.l()}, {orn.l(), orn.l()});
//	func_model.arrange_colors();
//	func_model.output_to_obj(dirs.get_working_catalog(), "func");
	
	
	


	ornstein::array_coord_t u = du;
	while (u <= w) {
		for (int8_t s = -1; s <= 1; s++) {
			graphics::threedim::Model profile_model;
			graphics::threedim::objects::add_axes(profile_model, {0,0,0}, {-1.1, -1.1, -1.1}, {1.2, 1.2, 1.2}, 0.01);
			
			graphics::threedim::str::Profile profile(
				{-u, 0, 0},
				{u, 0, 0}
			);
			
			graphics::threedim::str::Profile::ProfilePoint * profile_point;
			for (ornstein::array_coord_t x = -u; x <= u; x++) {
//				for (ornstein::array_coord_t y = -u; y <= u; y++) {
//					for (ornstein::array_coord_t z = -u; z <= u; z++) {
						profile_point = & profile.profile_cells()({x, 0, 0});
						lin = & orn.linearity_values()({x, s * u, w});
						if (
							true
//							(* lin)[0]
						) {
							profile_point->assign_color(graphics::color::RGB(
								255 * (* lin)[0],
								255 * (* lin)[1],
								255 * (* lin)[2]
							));
						} else {
							profile_point->clear();
						}
//					}
//				}
			}
			
			std::cout << "output profile\n";
			profile.output(profile_model, {-1, -1, -1}, {1, 1, 1});
			std::cout << "arrange colors\n";
			profile_model.arrange_colors();
			std::cout << "output model\n";
			profile_model.output_to_obj(dirs.get_working_catalog(), "profile " + std::to_string(s * u));
		}
		u += du;
	}
}

} // namespace modes::working
