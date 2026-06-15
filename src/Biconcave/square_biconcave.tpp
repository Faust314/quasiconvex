#pragma once
#include "square_biconcave.hpp"

namespace biconcave {

template <AddFunc Func>
void SquareBiconcave::generate_borders (
	std::mt19937 & gen, Func f, steps_count_t total_steps
) {
	real_array.set_values(-1);
	coord_t a = real_array.x_size();
	coord_t b = real_array.y_size();
	std::vector<ArrayPoint> starts = {ArrayPoint(0,0), ArrayPoint(a - 1, 0), ArrayPoint(a - 1, b - 1), ArrayPoint(0, b - 1)};
	std::vector<ArrayPoint> dirs = {ArrayPoint(1,0), ArrayPoint(0,1), ArrayPoint(-1, 0), ArrayPoint(0, -1)};
	std::vector<coord_t> sizes = {a, b, a, b};
	
	class ConvexLine {
	public:
		RealArray * arr;
		void set_line (ArrayPoint p, ArrayPoint dir) {
			b = arr->value_id(p);
			a = arr->value_id(p + dir) - b;
		}
		value_t & operator() (coord_t coord) {
			return arr->value(a * coord + b);
		}
	
	private:
		value_id_t a;
		value_id_t b;
	};
	ConvexLine line;
	line.arr = & real_array;
	
	std::vector<std::uniform_int_distribution<coord_t>> distrib;
	distrib.emplace_back(1, a - 1);
	distrib.emplace_back(1, b - 1);
	
	for (uint8_t border_id = 0; border_id < 4; border_id++) {
		for (coord_t t = 0; t < sizes[border_id]; t++) {
			real_array.value(starts[border_id] + dirs[border_id] * t) = 0;
		}
	}
	
	for (uint8_t border_id = 0; border_id < 4; border_id++) {
		line.set_line(starts[border_id], dirs[border_id]);
		for (steps_count_t step = 0; step < total_steps; step++) {
			coord_t t = distrib[border_id % 2](gen);
			real_array.value(starts[border_id] + dirs[border_id] * t) += f(step);
			algo::convex::convex_hull<false>(line, 0, sizes[border_id] - 1);
		}
	}
}

template <AddFunc Func>
void SquareBiconcave::generate_biconcave_function_with_borders (
	std::mt19937 & gen, Func f, steps_count_t total_steps, steps_count_t minimal_steps
) {
	coord_t a = real_array.x_size();
	coord_t b = real_array.y_size();
	std::uniform_int_distribution<coord_t> distrib_x(1, a - 1);
	std::uniform_int_distribution<coord_t> distrib_y(1, b - 1);
	
	HullHandler hull_handler(real_array);
	for (coord_t x = 0; x < a; x++) {
		hull_handler.add_line(0, {x, 0}, {0, 1}, b - 1);
	}
	for (coord_t y = 0; y < b; y++) {
		hull_handler.add_line(1, {0, y}, {1, 0}, a - 1);
	}
	
	hull_handler.build_convex_hull<false>(minimal_steps);
	
	for (steps_count_t step = 0; step < total_steps; step++) {
		real_array.value({distrib_x(gen), distrib_y(gen)}) += f(step);
		hull_handler.build_convex_hull<false>(minimal_steps);
	}
}

} // namespace biconcave