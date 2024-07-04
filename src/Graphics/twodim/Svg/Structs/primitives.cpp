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
	_output->ofs() << "<circle";
	_output->change_space(3);
}

void Primitives::circle_id (object_id_t id) {
	_output->ofs() << "id=\"circle" << id << "\"";
}



void Primitives::circle (Point const & p, coord_t r) {
	_output->ofs() << "cx=\"" << p.x << "\" cy=" << p.y << "\" r=\"" << r << "\""; 
}





void Primitives::ellipse_begin () {
	_output->ofs() << "<ellipse";
	_output->change_space(3);
}

void Primitives::ellipse_id (object_id_t id) {
	_output->ofs() << "id=\"ellipse" << id << "\"";
}



void Primitives::ellipse (Point const & p, coord_t rx, coord_t ry) {
	_output->ofs() << "cx=\"" << p.x << "\" cy=\"" << p.y << "\" rx=\"" << rx << "\" ry=\"" << ry << "\"";
}





void Primitives::line_begin () {
	_output->ofs() << "<line";
	_output->change_space(3);
}

void Primitives::line_id (object_id_t id) {
	_output->ofs() << "id=\"line" << id << "\"";
}



void Primitives::line (Point const & p1, Point const & p2) {
	_output->ofs() << "x1=\"" << p1.x << "\" x2=\"" << p2.x << "\" y1=\"" << p1.y << "\" y2=\"" << p2.y << "\"";
}





void Primitives::polyline_begin () {
	_output->ofs() << "<polyline";
	_output->change_space(3);
}

void Primitives::polyline_id (object_id_t id) {
	_output->ofs() << "id=\"polyline" << id << "\"";
}



void Primitives::polyline_start (Point const & p) {
	_output->ofs() << "points=\"" << p.x << " " << p.y;
}

void Primitives::polyline_stop () {
	_output->ofs() << "\"";
}

void Primitives::polyline_point (Point const & p) {
	_output->ofs() << ", " << p.x << " " << p.y;
}





void Primitives::polygon_begin () {
	_output->ofs() << "<polygon";
	_output->change_space(3);
}

void Primitives::polygon_id (object_id_t id) {
	_output->ofs() << "id=\"polygon" << id << "\"";
}





void Primitives::polygon_start (Point const & p) {
	_output->ofs() << "points=\"" << p.x << " " << p.y;
}

void Primitives::polygon_stop () {
	_output->ofs() << "\"";
}

void Primitives::polygon_point (Point const & p) {
	_output->ofs() << ", " << p.x << " " << p.y;
}
	
} // namespace graphics::twodim::svg
