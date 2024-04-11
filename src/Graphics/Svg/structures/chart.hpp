#pragma once

#include "../primitive_objects.hpp"

#include <optional>

namespace graphics::svg::object::str {

struct Chart {
	using Point = graphics::svg::object::basic::Point;
	
private:
	File * _file = nullptr;
	bool with_file = false;
	
	double _axis_width = 4;
	double _border_width = 24;
	
	std::optional<double> _svg_cell = std::nullopt;
	
	// with file
	
	std::optional<double> _extra_border_width = std::nullopt;
	
	std::optional<double> _left_cells = std::nullopt;
	std::optional<double> _right_cells = std::nullopt;
	std::optional<double> _lower_cells = std::nullopt;
	std::optional<double> _upper_cells = std::nullopt;
	
	// whithout file
	
	std::optional<Point> _begin_externel = std::nullopt;
	std::optional<Point> _end_externel = std::nullopt;
	
	std::optional<Point> _svg_origin = std::nullopt;
	std::optional<Point> _svg_origin_relative = std::nullopt;
	
	std::optional<uint16_t> _cell_count = std::nullopt;
	
	// chart
	
	Point _chart_origin = Point(0,0);
	
	double _chart_cell = 1;
	
	std::optional<double> _delta = std::nullopt;
	std::optional<uint16_t> _scale = 20;
	
	void update_file ();
	
public:
	File const * get_file () const;
	
	bool chart_complete () const;
	bool file_parameters_complete () const;
	
	double axis_width () const;
	double border_width () const;
	double extra_border_width () const;
	
	Point begin_internal () const;
	Point end_internal () const;
	Point begin_external () const;
	Point end_external () const;
	
	double internal_chart_width () const;
	double external_chart_width () const;
	double internal_chart_height () const;
	double external_chart_height () const;
	
	Point svg_origin () const;
	double svg_cell () const;

	
	
	Point const & chart_origin () const;
	double chart_cell () const;
	
	std::optional<double> delta_opt () const;
	std::optional<uint16_t> scale_opt () const;
	double delta () const;
	
	
	
	explicit Chart (Point chart_origin_ = Point(0,0), double chart_cell_ = 1, uint16_t scale_ = 20);
	
	
	
	void set_axis_width (double width);
	void set_border_width (double width);
	
	
	
	void set_with_file();
	void set_without_file();
	
	void set_file (File & file);
	void erase_file();
	void set_chart_size (double left, double right, double lower, double upper);
	void set_cell (double cell);
	void set_extra_border_width(double extra_border_width);
	void set_chart_with_file (File & file, double left, double right, double lower, double upper, double cell);
	
	
	
	void set_external_border (Point begin, Point end);
	void set_external_border (File const & file);
	
	void set_svg_origin (Point const & origin);
	void set_svg_origin_relative(Point const & origin = Point(0.5, 0.5));
	
	void set_svg_cell(double cell);
	void set_svg_cell_count(uint16_t count);
	
	
	
	void set_chart_origin (Point const & chart_origin);
	
	void set_chart_cell (double cell);
	
	void set_delta (double delta_);
	void set_scale (uint16_t count);
	
	
	
	void print_borders(graphics::svg::File::Layer & layer);
	void print_fine_grid(graphics::svg::File::Layer & layer, uint16_t count);
	void print_grid(graphics::svg::File::Layer & layer, double width);
	void print_arrows(graphics::svg::File::Layer & layer, double width);
};

} // namespace graphics::svg::object::str

#include "structure.ipp"