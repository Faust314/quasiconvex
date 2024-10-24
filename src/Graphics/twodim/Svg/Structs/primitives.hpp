#pragma once

#include "../../../types.hpp"
#include "../svg_config.hpp"
#include "../../../../Math/Geometry/Planimetry/point.hpp"

namespace graphics::twodim::svg {

struct Primitives {
	Primitives () = default;
	void init (Output & output);
	explicit Primitives (Output & output);
	
	
	
	void rect_begin () const;
	void rect_id (object_id_t id) const;
	
	void rect (Point const & p, coord_t width, coord_t height) const;
	void rect (Point const & p, coord_t width, coord_t height, coord_t r) const;
	void rect (Point const & p, coord_t width, coord_t height, coord_t rx, coord_t ry) const;
	
	
	
	void circle_begin () const;
	void circle_id (object_id_t id) const;
	
	void circle (Point const & p, coord_t r) const;
	
	
	
	void ellipse_begin () const;
	void ellipse_id (object_id_t id) const;
	
	void ellipse (Point const & p, coord_t rx, coord_t ry) const;
	
	
	
	void line_begin () const;
	void line_id (object_id_t id) const;
	
	void line (Point const & p1, Point const & p2) const;
	
	
	
	void polyline_begin () const;
	void polyline_id (object_id_t id) const;
	
	void polyline_start (Point const & p) const;
	void polyline_stop () const;
	void polyline_point (Point const & p) const;
	
	
	
	void polygon_begin () const;
	void polygon_id (object_id_t id) const;
	
	void polygon_start (Point const & p) const;
	void polygon_stop () const;
	void polygon_point (Point const & p) const;
	
private:
	Output * _output;
};

} // namespace graphics::twodim::svg