#include "modes.hpp"
#include "includes.hpp"

#include "../Biconcave/square_biconcave.tpp"

namespace modes {

void max_biconcave_mode () {
	using namespace biconcave;
	
	graphics::twodim::svg::Settings settings;
	settings.program_type = graphics::twodim::svg::Settings::program_type_t::browser;
	SquareBiconcave master(settings, 1920, 1080, 100);
	
	std::random_device rd;
	// std::mt19937 gen(rd());
	std::mt19937 gen(1);
	
	struct Func {
		// ab^n
		double a;
		double b;
		double operator () (uint16_t n) {
			return a * std::pow(b, n);
		}
	};
	Func f {0.2, 0.9};
	
	master.init_array(1, 2);
	
	master.generate_borders<Func>(gen, f, 100);
	// master.calculate_min_function(100);
	master.generate_biconcave_function_with_borders(gen, f, 100, 100);
	master.calculate_max_function();
	
	master.calculate_hessian();
	master.calculate_graphics();
	master.print_function("output", "func");
	master.print_profile("output/profile.svg", "profile");
}
	
} // namespace modes

