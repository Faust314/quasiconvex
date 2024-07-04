#pragma once

#include "../../../types.hpp"
#include "../svg_config.hpp"
#include "../../../../Math/Geometry/Planimetry/point.hpp"

namespace graphics::twodim::svg {

struct Path {
public:
	Path () = default;
	void init (Output & output);
	explicit Path (Output & output);
	
	
	
	void begin () const;
	void path_id (object_id_t id) const;
	
	void start (Point const & p) const;
	void stop () const;
	void Move (Point const & p) const;
	void move (Point const & dp) const;
	
	
	
	void Line (Point const & p) const;
	void line (Point const & dp) const;
	
	void Line_horizontal (coord_t x) const;
	void line_horizontal (coord_t dx) const;
	void Line_vertical (coord_t y) const;
	void line_vertical (coord_t dy) const;
	
	
	
	void Bezier_curve (Point const & p1, Point const & p2, Point const & p) const;
	void bezier_curve (Point const & dp1, Point const & dp2, Point const & dp) const;
	void Bezier_curve_short (Point const & p2, Point const & p) const;
	void bezier_curve_short (Point const & dp2, Point const & dp) const;
	
	void Quadratic_curve (Point const & p1, Point const & p) const;
	void quadratic_curve (Point const & dp1, Point const & dp) const;
	void Quadratic_curve_short (Point const & p) const;
	void quadratic_curve_short (Point const & dp) const;
	
	
	
	void Arc (
		coord_t rx, coord_t ry, coord_t rotation, bool is_large_arc, bool is_counterclockwise, Point const & p
	) const;
	void arc (
		coord_t rx, coord_t ry, coord_t rotation, bool is_large_arc, bool is_counterclockwise, Point const & dp
	) const;
	
	
	
	void close_path () const;
	
private:
	Output * _output;
};

} // namespace graphics::twodim::svg