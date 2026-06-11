#include "square_biconcave.hpp"

#include "../Utils/Basic/dir_utils.hpp"
#include "Graphics/threshold.hpp"
#include "Graphics/combine.hpp"
#include "../ConvexHull/max_biconcave.tpp"

namespace biconcave {

void SquareBiconcave::init (
	graphics::twodim::svg::Settings const & settings_,
	value_t screen_width_,
	value_t screen_height_,
	value_t margin_
) {
	settings = & settings_;
	screen_width = screen_width_;
	screen_height = screen_height_;
	margin = margin_;
}

SquareBiconcave::SquareBiconcave (
	graphics::twodim::svg::Settings const & settings_,
	value_t screen_width_,
	value_t screen_height_,
	value_t margin_
) :
	settings(& settings_),
	screen_width(screen_width_),
	screen_height(screen_height_),
	margin(margin_)
{}


void SquareBiconcave::init_array (
	value_t square_radius_,
	coord_t grid_radius_length_
) {
	grid_radius_length = std::max(coord_t(1), grid_radius_length_);
	grid_length = grid_radius_length_ * 2 + 1;
	
	cell_width = square_radius_ / grid_radius_length;
	value_t square_length = (grid_length - 1) * cell_width;
	
	real_array.init(
		grid_length, grid_length,
		-1e9
	);
	
	value_t scale = std::min(
		(screen_height - 2 * margin) / (square_length + cell_width),
		(screen_width - 2 * margin) / (square_length + cell_width)
	);
	
	scale = cell_width * scale;
	plane_affine.a = scale;
	plane_affine.b = 0;
	plane_affine.c = 0;
	plane_affine.d = scale;
	
	Point p0 = {value_t(grid_radius_length), value_t(grid_radius_length)};
	Point p1 = {screen_width / 2, screen_height / 2};
	Point p = p1 - plane_affine(p0);
	plane_affine.x0 = p.x;
	plane_affine.y0 = p.y;
}



template <AddFunc Func>
void SquareBiconcave::generate_borders (
	std::mt19937 & gen, Func f, steps_count_t total_steps
) {
	real_array.set_values(-1e9);
	coord_t a = real_array.x_size();
	coord_t b = real_array.y_size();
	std::vector<Point> starts = {Point(0,0), Point(a, 0), Point(a, b), Point(0, b)};
	std::vector<Point> dirs = {Point(1,0), Point(0,1), Point(-1, 0), Point(0, -1)};
	std::vector<coord_t> sizes = {a, b, a, b};
	
	class ConvexLine {
	public:
		RealArray * arr;
		void set_line (Point p, Point dir) {
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
	line.arr = real_array;
	
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
			algo::convex::convex_hull(line, 0, sizes[border_id] - 1);
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
		hull_handler.add_line(0, {x, 0}, {0, 1}, b);
	}
	for (coord_t y = 0; y < b; y++) {
		hull_handler.add_line(1, {y,0}, {1, 0}, a);
	}
	
	hull_handler.build_convex_hull<false>(minimal_steps);
	
	for (steps_count_t step = 0; step < total_steps; step++) {
		real_array.value({distrib_x(gen), distrib_y(gen)}) += f(step);
		hull_handler.build_convex_hull<false>(minimal_steps);
	}
}



void SquareBiconcave::calculate_min_function (steps_count_t steps_count) {
	HullHandler hull_handler(real_array);
	coord_t a = real_array.x_size();
	coord_t b = real_array.y_size();
	
	for (coord_t x = 0; x < a; x++) {
		hull_handler.add_line(0, {x, 0}, {0, 1}, b);
	}
	for (coord_t y = 0; y < b; y++) {
		hull_handler.add_line(1, {y,0}, {1, 0}, a);
	}
	
	hull_handler.build_convex_hull<false>(steps_count);
}

void SquareBiconcave::calculate_max_function () {
	hull::calculate_max_biconcave_function<value_t>(real_array, Point(grid_radius_length));
}



value_t SquareBiconcave::calculate_min_function_by_border_and_compare (steps_count_t steps_count) {
	auto copied_array = real_array;
	for (coord_t x = 1; x < real_array.x_size() - 1; x++) {
		for (coord_t y = 1; y < real_array.y_size() - 1; y++) {
			real_array.value({x, y}) = -1e9;
		}
	}
	calculate_min_function(steps_count);
	value_t diff = 0;
	for (coord_t x = 1; x < real_array.x_size() - 1; x++) {
		for (coord_t y = 1; y < real_array.y_size() - 1; y++) {
			diff = std::max(diff, copied_array.value({x, y}) - real_array.value({x, y}));
		}
	}
	return diff;
}



void SquareBiconcave::calculate_hessian () {
	hessian.init(real_array, cell_width);
}

void SquareBiconcave::calculate_graphics (func::Func const & color_func, uint16_t colors_number) {
	graphics.init(real_array);
	std::vector<uint8_t> transform = calculate_transform(
		graphics.set_colors(hessian, color_func, 0), colors_number
	);
	graphics.apply_transform(transform, hessian);
}



void SquareBiconcave::print_function (std::string const & file_path, std::string const & file_name) {
	
}


void SquareBiconcave::print_profile (std::string const & file_path, std::string const & file_name) {
	aux::dir::process_path(file_path);
	std::ofstream ofs (file_path);
	graphics::twodim::svg::Print svg_print(ofs, * settings);
	
	graphics::color::RGB_O border_color (0, 0, 0);
	
	std::unordered_map<uint32_t, uint32_t> colors_map;
	std::vector<graphics::color::RGB> colors;
	std::vector<std::vector<ArrayPoint>> points;
	for (coord_t x = 0; x < real_array.x_size(); x++) {
		for (coord_t y = 0; y < real_array.y_size(); y++) {
			if (real_array.has_point({x, y})) {
				graphics::color::RGB color = graphics.color({x, y});
				uint32_t key = color.r + color.g * 256 + color.b * 256 * 256;
				if (! colors_map.contains(key)) {
					colors_map[key] = colors.size();
					colors.push_back(color);
					points.emplace_back();
				}
				points[colors_map[key]].emplace_back(x, y);
			}
		}
	}
	
	svg_print.file_structs().file_begin(screen_width, screen_height, file_name);
	
	svg_print.primitives().rect_begin();
	svg_print.file_structs().painting(graphics::twodim::painting::Fill(graphics::color::RGB_O(255, 255, 255)));
	svg_print.primitives().rect({0,0}, screen_width, screen_height);
	svg_print.file_structs().object_end();
	
	for (uint32_t i = 0; i < colors.size(); i++) {
		Combine combine(real_array.x_size(), real_array.y_size());
		for (ArrayPoint const & p : points[i]) {
			combine.add_point(p);
		}
		combine.erase_extra_edges();
		std::vector<std::vector<Point>> contours = combine.calculate_contours();
		
		svg_print.path().begin();
		svg_print.file_structs().painting({
			graphics::color::RGB_O(colors[i]),
			border_color,
			0
		});
		svg_print.path().start(plane_affine(contours.front().front()));
		for (std::vector<Point> const & contour : contours) {
			svg_print.path().Move(plane_affine(contour.front()));
			for (uint32_t k = 1; k < contour.size(); k++) {
				svg_print.path().Line(plane_affine(contour[k]));
			}
			svg_print.path().Line(plane_affine(contour.front()));
		}
		svg_print.path().stop();
		svg_print.file_structs().object_end();
	}
	
	svg_print.file_structs().file_end();
}
	
} // namespace biconcave
