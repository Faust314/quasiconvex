#include "biconcave.hpp"

#include "../Utils/Basic/dir_utils.hpp"
#include "Graphics/threshold.hpp"
#include "Graphics/combine.hpp"

namespace biconcave {

void Biconcave::init (
	graphics::twodim::svg::Settings const & settings_,
	value_t screen_width_,
	value_t screen_height_,
	value_t margin_,
	value_t slide_value_
) {
	settings = & settings_;
	screen_width = screen_width_;
	screen_height = screen_height_;
	margin = margin_;
	slide_value = slide_value_;
}

Biconcave::Biconcave (
	graphics::twodim::svg::Settings const & settings_,
	value_t screen_width_,
	value_t screen_height_,
	value_t margin_,
	value_t slide_value_
) :
	settings(& settings_),
	screen_width(screen_width_),
	screen_height(screen_height_),
	margin(margin_),
	slide_value(slide_value_)
{}


void Biconcave::init_array (
	value_t strip_width, value_t left_domain_pos_, value_t right_domain_pos_, coord_t strip_grid_width_
) {
	strip_grid_width = std::max(coord_t(1), strip_grid_width_);
	cell_diagonal = strip_width / strip_grid_width;
	cell_width = cell_diagonal / std::sqrt(2);
	left_domain_pos = left_domain_pos_;
	right_domain_pos = right_domain_pos_;
	strip_grid_length = coord_t(std::lround((right_domain_pos - left_domain_pos) / cell_diagonal));
	strip_grid_length = std::max(strip_grid_length, strip_grid_width);
	value_t strip_length = strip_grid_length * cell_diagonal;
	
	real_array.init(
		strip_grid_length + 1 + strip_grid_width, 2 * strip_grid_width + 1,
		-1e9
	);
	
	for (coord_t x = 0; x < strip_grid_width; x++) {
		for (coord_t y = 0; y < 2 * strip_grid_width - x; y++) {
			real_array.disable_point({x, y});
			real_array.disable_point({
				coord_t(strip_grid_length + strip_grid_width - x),
				coord_t(2 * strip_grid_width - y)
			});
		}
	}
	
	value_t scale = std::min(
		(screen_height - 2 * margin) / (strip_width + cell_diagonal),
		(screen_width - 2 * margin) / (strip_length + cell_diagonal)
	);
	
	scale = cell_width * scale / std::sqrt(2);
	plane_affine.a = 2 * scale;
	plane_affine.b = scale;
	plane_affine.c = 0;
	plane_affine.d = -scale;
	
	Point p0 = {value_t(real_array.x_size() - 1) / 2, value_t(real_array.y_size() - 1) / 2};
	Point p1 = {screen_width / 2, screen_height / 2};
	Point p = p1 - plane_affine(p0);
	plane_affine.x0 = p.x;
	plane_affine.y0 = p.y;
}



void Biconcave::print_function (
	std::string const & file_path, std::string const & file_name,
	func::Func const & function, size_t cell_grid
) {
	value_t scale;
	
	size_t grid_size = strip_grid_length * cell_grid;
	value_t delta = (right_domain_pos - left_domain_pos) / value_t(grid_size);
	
	value_t min_value = std::numeric_limits<value_t>::max();
	value_t max_value = std::numeric_limits<value_t>::min();
	
	for (size_t i = 0; i <= grid_size; i++) {
		min_value = std::min(min_value, function({left_domain_pos + value_t(i) * delta, slide_value}));
		max_value = std::max(max_value, function({left_domain_pos + value_t(i) * delta, slide_value}));
	}
	
	if (std::abs(max_value - min_value) < 1e-9) {
		scale = (screen_width - 4 * margin) / (right_domain_pos - left_domain_pos);
	} else {
		scale = std::min(
			(screen_height - 4 * margin - cell_diagonal) / (max_value - min_value),
			(screen_width - 4 * margin - cell_diagonal) / (right_domain_pos - left_domain_pos)
		);
	}
	
	PlaneAffine func_affine;
	func_affine.a = scale;
	func_affine.b = 0;
	func_affine.c = 0;
	func_affine.d = - scale;
	
	Point p0 = {(right_domain_pos + left_domain_pos) / 2, (min_value + max_value) / 2};
	Point p1 = {screen_width / 2, screen_height / 2};
	Point p = p1 - func_affine(p0);
	
	func_affine.x0 = p.x;
	func_affine.y0 = p.y;
	
	aux::dir::process_path(file_path);
	std::ofstream ofs (file_path);
	graphics::twodim::svg::Print svg_print(ofs, * settings);
	
	graphics::twodim::painting::Stroke axis_stroke (
		graphics::color::RGB_O(0, 0, 0),
		2
	);
	graphics::twodim::Paint func_paint (
		graphics::twodim::painting::Fill(),
		graphics::twodim::painting::Stroke(
			graphics::color::RGB_O(0, 0, 255),
			2
		)
	);
	graphics::twodim::Paint circle_paint (
		graphics::color::RGB_O(0, 0, 200),
		graphics::color::RGB_O(0, 0, 200),
		0
	);
	
	svg_print.file_structs().file_begin(screen_width, screen_height, file_name);
	
	svg_print.primitives().rect_begin();
	svg_print.file_structs().painting(graphics::twodim::painting::Fill(graphics::color::RGB_O(255, 255, 255)));
	svg_print.primitives().rect({0,0}, screen_width, screen_height);
	svg_print.file_structs().object_end();
	
	svg_print.primitives().line_begin();
	svg_print.file_structs().painting(axis_stroke);
	svg_print.primitives().line(
		func_affine({left_domain_pos, min_value}) + Point(- margin, margin),
		func_affine({left_domain_pos, max_value}) + Point(- margin, - margin)
	);
	svg_print.file_structs().object_end();
	
	svg_print.primitives().line_begin();
	svg_print.file_structs().painting(axis_stroke);
	svg_print.primitives().line(
		func_affine({left_domain_pos, min_value}) + Point(- margin, margin),
		func_affine({right_domain_pos, min_value}) + Point(margin, margin)
	);
	svg_print.file_structs().object_end();
	
	svg_print.primitives().polyline_begin();
	svg_print.file_structs().painting(func_paint);
	svg_print.primitives().polygon_start(func_affine({left_domain_pos, function({left_domain_pos, slide_value})}));
	for (size_t i = 1; i <= grid_size; i++) {
		svg_print.primitives().polyline_point(func_affine({
			left_domain_pos + value_t(i) * delta, function({left_domain_pos + value_t(i) * delta, slide_value})
		}));
	}
	svg_print.primitives().polyline_stop();
	svg_print.file_structs().object_end();
	
	delta *= cell_grid;
	
	for (size_t i = 0; i <= strip_grid_length; i++) {
		svg_print.primitives().circle_begin();
		svg_print.file_structs().painting(circle_paint);
		svg_print.primitives().circle(func_affine({
			left_domain_pos + value_t(i) * delta, function({left_domain_pos + value_t(i) * delta, slide_value})
		}), 2);
		svg_print.file_structs().object_end();
	}
	
	svg_print.file_structs().file_end();
}



void Biconcave::init_array_border_values (func::Func const & f, func::Func const & g) {
	for (coord_t i = 0; i <= strip_grid_length; i++) {
		real_array.value({strip_grid_width + i, 0}) = f({left_domain_pos + cell_diagonal * value_t(i), slide_value});
		real_array.value({i, coord_t(2 * strip_grid_width)}) = g({left_domain_pos + cell_diagonal * value_t(i), slide_value});
	}
}

void Biconcave::calculate_hull (steps_count_t steps_count) {
	HullHandler hull_handler(real_array);
	
	for (coord_t i = 1; i < strip_grid_width; i++) {
		hull_handler.add_line(0, {strip_grid_width, i}, {1, -1}, i);
		hull_handler.add_line(0, {strip_grid_length - i, 2 * strip_grid_width}, {1, -1}, i);
		hull_handler.add_line(1, {i, coord_t(2 * strip_grid_width - i)}, {0, 1}, i);
		hull_handler.add_line(1, {strip_grid_length + strip_grid_width - i, 0}, {0, 1}, i);
	}
	
	for (coord_t i = 0; i <= strip_grid_length - strip_grid_width; i++) {
		hull_handler.add_line(0, {i, coord_t(2 * strip_grid_width)}, {1, -1}, 2 * strip_grid_width);
		hull_handler.add_line(1, {strip_grid_width + i, 0}, {0, 1}, 2 * strip_grid_width);
	}
	
	hull_handler.build_convex_hull<false>(steps_count);
}

void Biconcave::calculate_hessian () {
	hessian.init(real_array, cell_width);
}

void Biconcave::calculate_graphics (func::Func const & color_func, uint16_t colors_number) {
	graphics.init(real_array);
	std::vector<uint8_t> transform = calculate_transform(
		graphics.set_colors(hessian, color_func, slide_value), colors_number
	);
	graphics.apply_transform(transform, hessian);
	
}



void Biconcave::print_profile (std::string const & file_path, std::string const & file_name) {
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
