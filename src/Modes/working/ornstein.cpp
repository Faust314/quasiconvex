#include "../modes.hpp"

#include "../../Ornstein/function.tpp"
#include "../../Ornstein/asymp.tpp"

#include <iostream>

namespace modes::working {

double f (double x) {
	return 5 * std::sin(x * 1000);
}

void ornstein () {
	DirStruct dirs;
	dirs.basic_init("final");
	
	enum class task_type {convexity, harmonic};
	
	constexpr uint8_t dim = 4;
	ornstein::coord_t p = 1;
	ornstein::coord_t c = 1;
	
	ornstein::array_coord_t n = 20;
	ornstein::coord_t l = 1;
	double alpha = 0.7;
	double hom = 0.5;
	ornstein::array_coord_t w = std::round(alpha * n);
	ornstein::array_coord_t step = 1;
	uint16_t M = 1;
	uint16_t N = 100;
	ornstein::coord_t T = -1;
	
//	{
//		ornstein::coord_t p0 = 1;
//		ornstein::coord_t p1 = 1.1;
//		size_t func_size = 20;
//		size_t iterations = 15;
//		
//		std::vector<ornstein::coord_t> p_arr (func_size + 1);
//		ornstein::coord_t delta = (p1 - p0) / func_size;
//		for (size_t i = 0; i <= func_size; i++) {
//			p_arr[i] = p0 + i * delta;
//		}
//		auto values = ornstein::compute_asymp<dim>(p_arr, iterations, n, N, M, T, hom);
//		
//		std::ofstream ofs (dirs.get_working_catalog() + "/asymp.csv");
//		ofs << "X,Y\n";
//		for (size_t i = 0; i < p_arr.size(); i++) {
//			ofs << "\"" << p_arr[i] << "\",\"" << values[i] <<"\"\n";
//		}
//	}
	
	
		
	
	if (w >= n) {
		throw "error";
	}
	ornstein::Function<dim> orn(p, c, n, l);
//	orn.calculate_convex_hull(N, M, hom);
	orn.calculate_harmonic_hull(N, M, hom);
	orn.calculate_linearity();

	if constexpr (dim == 4) {
		ornstein::Function<dim>::linearity const * lin;
		graphics::threedim::Model profile_model;
		graphics::threedim::objects::add_axes(profile_model, {0,0,0}, {-1.1, -1.1, -1.1}, {1.1, 1.1, 1.1}, 0.01);
		graphics::threedim::str::Profile profile(
			{-w, -w, -w},
			{w, w, w}
		);
		graphics::threedim::str::Profile::ProfilePoint * profile_point;
		for (ornstein::array_coord_t x = -w; x <= w; x++) {
			for (ornstein::array_coord_t y = -w; y <= w; y++) {
				for (ornstein::array_coord_t z = -w; z <= w; z++) {
					profile_point = &profile.profile_cells()({x, y, z});
					lin = &orn.linearity_values()({x, y, z, w});
					profile_point->assign_color(
						graphics::color::RGB(
							255 * (*lin)[0], 255 * (*lin)[1], 255 * (*lin)[2]
						));
				}
			}
		}
		std::cout << "output profile\n";
		profile.output(profile_model, {-1, -1, -1}, {1, 1, 1});
		std::cout << "arrange colors\n";
		profile_model.arrange_colors();
		std::cout << "output model\n";
		profile_model.output_to_obj(dirs.get_working_catalog(), "profile");


		for (ornstein::array_coord_t z = -w; z <= w; z++) {
			graphics::threedim::Model func_model;
			graphics::threedim::str::Func func({-n,-n}, {n, n});
			graphics::threedim::objects::add_axes(func_model, {0,0,0}, {-1.1, -1.1, -1.1}, {1.1, 1.1, 1.1}, 0.01);

			graphics::threedim::str::Func::FuncPoint * func_point;
			for (ornstein::array_coord_t x = -n; x <= n; x++) {
				for (ornstein::array_coord_t y = -n; y <= n; y++) {
					func_point = & func.func_points()({x, y});
					lin = & orn.linearity_values()({x, y, z, w});
					func_point->value() = orn.values()({x, y, z, w});
					func_point->color() = graphics::color::RGB(
						255 * (* lin)[0],
						255 * (* lin)[1],
						255 * (* lin)[2]
					);
				}
			}
			func.output(func_model, {-orn.l(), -orn.l()}, {orn.l(), orn.l()});
			func_model.arrange_colors();
			func_model.output_to_obj(dirs.get_working_catalog(), "func" + std::to_string(z));
		}

		graphics::threedim::Model func_model;
		graphics::threedim::str::Func func({-n,-n}, {n, n});
		graphics::threedim::objects::add_axes(func_model, {0,0,0}, {-1.1, -1.1, -1.1}, {1.1, 1.1, 1.1}, 0.01);

		graphics::threedim::str::Func::FuncPoint * func_point;
		for (ornstein::array_coord_t x = -n; x <= n; x++) {
			for (ornstein::array_coord_t y = -n; y <= n; y++) {
				func_point = & func.func_points()({x, y});
				lin = & orn.linearity_values()({x, y, 0, 0});
				func_point->value() = orn.values()({x, y, 0, 0});
				func_point->color() = graphics::color::RGB(
					255 * (* lin)[0],
					255 * (* lin)[1],
					255 * (* lin)[2]
				);
			}
		}
		func.output(func_model, {-orn.l(), -orn.l()}, {orn.l(), orn.l()});
		func_model.arrange_colors();
		func_model.output_to_obj(dirs.get_working_catalog(), "func");

		std::ofstream ofs (dirs.get_working_catalog() + "/info.txt");
		ofs << orn.values()({0,0,0,0});
	} else {
		w = n-1;
		ornstein::Function<dim>::linearity const * lin;
		graphics::threedim::Model func_model;
		graphics::threedim::str::Func func({-n,-n}, {n, n});
		graphics::threedim::objects::add_axes(func_model, {0,0,0}, {-1.1, -1.1, -1.1}, {1.1, 1.1, 1.1}, 0.01);

		graphics::threedim::str::Func::FuncPoint * func_point;
		for (ornstein::array_coord_t x = -n; x <= n; x++) {
			for (ornstein::array_coord_t y = -n; y <= n; y++) {
				func_point = & func.func_points()({x, y});
				lin = & orn.linearity_values()({x, y});
				func_point->value() = orn.values()({x, y});
				func_point->color() = graphics::color::RGB(
					255 * (* lin)[0],
					255 * (* lin)[1],
					0
				);
			}
		}

		func.output(func_model, {-1, -1}, {1, 1});
		func_model.arrange_colors();
		func_model.output_to_obj(dirs.get_working_catalog(), "func");

		std::ofstream ofs (dirs.get_working_catalog() + "/info.txt");
		ofs << orn.values()({0,0});
	}
}

} // namespace modes::working
