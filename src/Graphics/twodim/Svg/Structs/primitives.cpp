#include "primitives.hpp"

namespace graphics::twodim::svg {


void Primitives::init (Output & output) {
	_output = & output;
}

Primitives::Primitives (Output & output) :
	_output(& output)
{}





void Primitives::rect_begin () {
	_output->ofs() << "<rect";
	_output->change_space(3);
}

void Primitives::rect_id (object_id_t id) {
	_output->ofs() << "id=\"rect" << id << "\"";
}



void Primitives::rect (Point const & p, coord_t width, coord_t height) {
	_output->ofs() << "x=\"" << p.x << "\" y=\"" << p.y <<
		"\" width=\"" << width << "\" height=\"" << height << "\"";
}

void Primitives::rect (Point const & p, coord_t width, coord_t height, coord_t r) {
	_output->ofs() << "x=\"" << p.x << "\" y=\"" << p.y <<
		"\" width=\"" << width << "\" height=\"" << height <<
		"\" rx=\"" << r << "\" ry=\"" << r << "\"";
}

void Primitives::rect (Point const & p, coord_t width, coord_t height, coord_t rx, coord_t ry) {
	_output->ofs() << "x=\"" << p.x << "\" y=\"" << p.y <<
		"\" width=\"" << width << "\" height=\"" << height <<
		"\" rx=\"" << rx << "\" ry=\"" << ry << "\"";
}





void Primitives::circle_begin () {
	
}

void Primitives::circle_id () {
	
}

void Primitives::circle (Point const & p, coord_t r) {
	
}

void Primitives::ellipse_begin () {
	
}

void Primitives::ellipse_id () {
	
}

void Primitives::ellipse (Point const & p, coord_t rx, coord_t ry) {
	
}

void Primitives::line_begin () {
	
}

void Primitives::line_id () {
	
}

void Primitives::line (Point const & p1, Point const & p2) {
	
}

void Primitives::polyline_begin () {
	
}

void Primitives::polyline_id () {
	
}

void Primitives::polyline_next_point () {
	
}

void Primitives::polyline_point (Point const & p) {
	
}

void Primitives::polygon_begin () {
	
}

void Primitives::polygon_id () {
	
}

void Primitives::polygon_next_point () {
	
}

void Primitives::polygon_point (Point const & p) {
	
}
} // namespace graphics::twodim::svg
