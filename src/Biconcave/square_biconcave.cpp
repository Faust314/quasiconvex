#include "square_biconcave.hpp"

#include "../Utils/Basic/dir_utils.hpp"
#include "Graphics/threshold.hpp"
#include "Graphics/combine.hpp"
#include "../ConvexHull/max_biconcave.tpp"
#include "../Graphics/Threedim/Structs/func.hpp"
#include "../Algo/heap.tpp"
#include "../Math/Geometry/Multidimensional/multi_point.tpp"
#include "../Array/Basic/basic.tpp"

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
		-1
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
	
	ArrayPoint p0 = {value_t(grid_radius_length), value_t(grid_radius_length)};
	ArrayPoint p1 = {screen_width / 2, screen_height / 2};
	ArrayPoint p = p1 - plane_affine(p0);
	plane_affine.x0 = p.x;
	plane_affine.y0 = p.y;
}



void SquareBiconcave::calculate_min_function (steps_count_t steps_count) {
	HullHandler hull_handler(real_array);
	coord_t a = real_array.x_size();
	coord_t b = real_array.y_size();
	
	for (coord_t x = 0; x < a; x++) {
		hull_handler.add_line(0, {x, 0}, {0, 1}, b - 1);
	}
	for (coord_t y = 0; y < b; y++) {
		hull_handler.add_line(1, {0,y}, {1, 0}, a - 1);
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
//	graphics.apply_transform(transform, hessian);
}

void SquareBiconcave::calculate_graphics () {
	func::Func func("1 / (1 + 1000 * t)", {"t", "s"});
	calculate_graphics(func, 100);
}



void SquareBiconcave::print_function (std::string const & file_path, std::string const & file_name) {
	using ArrayPoint = math::geom::multi::Point<array::array_coord_t, 2>;
	graphics::threedim::str::Func func(ArrayPoint({0, 0}), ArrayPoint({real_array.x_size() - 1, real_array.y_size() - 1}));
	
	for (coord_t x = 0; x < real_array.x_size(); x++) {
		for (coord_t y = 0; y < real_array.y_size(); y++) {
			func.func_points()(ArrayPoint({x,y})).value() = real_array.value(Point({x,y}));
			func.func_points()(ArrayPoint({x,y})).color() = graphics.color(Point({x,y}));
		}
	}
	
	graphics::threedim::Model model;
	func.output(model, {0,0}, {1,1});
	aux::dir::process_path(file_path);
	model.output_to_obj(file_path, file_name);
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
			combine.add_point1(p);
		}
		combine.erase_extra_edges1();
		std::vector<std::vector<Point>> contours = combine.calculate_contours1();
		
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
