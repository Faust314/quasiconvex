#include "primitives.hpp"

namespace graphics::twodim::svg {


void Primitives::init (Output & output) {
	_output = & output;
}

Primitives::Primitives (Output & output) :
	_output(& output)
{}





void Primitives::rect_begin () const {
	_output->os() << "<rect";
	_output->change_space(3);
}

void Primitives::rect_id (object_id_t id) const {
	_output->os() << "id=\"rect" << id << "\"";
}



void Primitives::rect (Point const & p, coord_t width, coord_t height) const {
	_output->os() << "x=\"" << p.x << "\" y=\"" << p.y <<
		"\" width=\"" << width << "\" height=\"" << height << "\"";
}

void Primitives::rect (Point const & p, coord_t width, coord_t height, coord_t r) const {
	_output->os() << "x=\"" << p.x << "\" y=\"" << p.y <<
		"\" width=\"" << width << "\" height=\"" << height <<
		"\" rx=\"" << r << "\" ry=\"" << r << "\"";
}

void Primitives::rect (Point const & p, coord_t width, coord_t height, coord_t rx, coord_t ry) const {
	_output->os() << "x=\"" << p.x << "\" y=\"" << p.y <<
		"\" width=\"" << width << "\" height=\"" << height <<
		"\" rx=\"" << rx << "\" ry=\"" << ry << "\"";
}





void Primitives::circle_begin () const {
	_output->os() << "<circle";
	_output->change_space(3);
}

void Primitives::circle_id (object_id_t id) const {
	_output->os() << "id=\"circle" << id << "\"";
}



void Primitives::circle (Point const & p, coord_t r) const {
	_output->os() << "cx=\"" << p.x << "\" cy=\"" << p.y << "\" r=\"" << r << "\""; 
}





void Primitives::ellipse_begin () const {
	_output->os() << "<ellipse";
	_output->change_space(3);
}

void Primitives::ellipse_id (object_id_t id) const {
	_output->os() << "id=\"ellipse" << id << "\"";
}



void Primitives::ellipse (Point const & p, coord_t rx, coord_t ry) const {
	_output->os() << "cx=\"" << p.x << "\" cy=\"" << p.y << "\" rx=\"" << rx << "\" ry=\"" << ry << "\"";
}





void Primitives::line_begin () const {
	_output->os() << "<line";
	_output->change_space(3);
}

void Primitives::line_id (object_id_t id) const {
	_output->os() << "id=\"line" << id << "\"";
}



void Primitives::line (Point const & p1, Point const & p2) const {
	_output->os() << "x1=\"" << p1.x << "\" x2=\"" << p2.x << "\" y1=\"" << p1.y << "\" y2=\"" << p2.y << "\"";
}





void Primitives::polyline_begin () const {
	_output->os() << "<polyline";
	_output->change_space(3);
}

void Primitives::polyline_id (object_id_t id) const {
	_output->os() << "id=\"polyline" << id << "\"";
}



void Primitives::polyline_start (Point const & p) const {
	_output->os() << "points=\"" << p.x << " " << p.y;
}

void Primitives::polyline_stop () const {
	_output->os() << "\"";
}

void Primitives::polyline_point (Point const & p) const {
	_output->os() << ", " << p.x << " " << p.y;
}





void Primitives::polygon_begin () const {
	_output->os() << "<polygon";
	_output->change_space(3);
}

void Primitives::polygon_id (object_id_t id) const {
	_output->os() << "id=\"polygon" << id << "\"";
}





void Primitives::polygon_start (Point const & p) const {
	_output->os() << "points=\"" << p.x << " " << p.y;
}

void Primitives::polygon_stop () const {
	_output->os() << "\"";
}

void Primitives::polygon_point (Point const & p) const {
	_output->os() << ", " << p.x << " " << p.y;
}
	
} // namespace graphics::twodim::svg
