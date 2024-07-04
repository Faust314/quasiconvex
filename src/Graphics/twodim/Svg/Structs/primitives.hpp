#pragma once

#include "../../../types.hpp"
#include "../svg_config.hpp"
#include "../../../../Math/Geometry/Planimetry/point.hpp"

namespace graphics::twodim::svg {

struct Primitives {
	Primitives () = default;
	void init (Output & output);
	explicit Primitives (Output & output);
	
	
	
	void rect_begin ();
	void rect_id (object_id_t id);
	
	void rect (Point const & p, coord_t width, coord_t height);
	void rect (Point const & p, coord_t width, coord_t height, coord_t r);
	void rect (Point const & p, coord_t width, coord_t height, coord_t rx, coord_t ry);
	
	
	
	void circle_begin ();
	void circle_id (object_id_t id);
	
	void circle (Point const & p, coord_t r);
	
	
	
	void ellipse_begin ();
	void ellipse_id (object_id_t id);
	
	void ellipse (Point const & p, coord_t rx, coord_t ry);
	
	
	
	void line_begin ();
	void line_id (object_id_t id);
	
	void line (Point const & p1, Point const & p2);
	
	
	
	void polyline_begin ();
	void polyline_id (object_id_t id);
	
	void polyline_start (Point const & p);
	void polyline_stop ();
	void polyline_point (Point const & p);
	
	
	
	void polygon_begin ();
	void polygon_id (object_id_t id);
	
	void polygon_start (Point const & p);
	void polygon_stop ();
	void polygon_point (Point const & p);
	
private:
	Output * _output;
};

} // namespace graphics::twodim::svg