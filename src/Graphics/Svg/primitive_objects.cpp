#include "primitive_objects.hpp"

namespace graphics::svg::object::basic {

Point::Point (double x_, double y_) :
	x(x_),
	y(y_)
{ }

Point Point::operator+ (Point const & p) const {
	return Point(x + p.x, y + p.y);
}

Point Point::operator- (Point const & p) const {
	return Point(x - p.x, y - p.y);
}

Point Origin::operator() (double x, double y) {
	return Point(x0 + x, y0 - y);
}

Point Origin::operator() (Point p) {
	return Point(x0 + p.x, y0 - p.y);
}

Origin::Origin (Point p) :
	x0(p.x),
	y0(p.y)
{ }

Origin::Origin (double x0_, double y0_) :
	x0(x0_),
	y0(y0_)
{ }


graphics::svg::Object line (Point p1, Point p2, Stroke const & stroke) {
	Object obj("line");
	obj.new_line(style(stroke));
	obj.new_line();
	obj() += "x1=\"" + std::to_string(p1.x)+ "\" ";
	obj() += "y1=\"" + std::to_string(p1.y)+ "\" ";
	obj() += "x2=\"" + std::to_string(p2.x)+ "\" ";
	obj() += "y2=\"" + std::to_string(p2.y)+ "\"";
	
	return obj;
}




bool Path::line_break = false;

bool Path::auto_mode = true;

Object Path::operator() () {
	return obj;
}

Path::Path (Fill const & fill, Stroke const & stroke) :
	obj("path")
{
	obj.new_line(style(fill));
	obj() += " " + style(stroke);
	if (auto_mode) {
		start();
	}
}

Object Path::get_object (Fill const & fill, Stroke const & stroke) {
	Object object("path");
	object.new_line(style(fill));
	object() += " " + style(stroke);
	
	return object;
}

void Path::assign_line_break (bool new_line_break) {
	line_break = new_line_break;
}

void Path::assign_auto_mode (bool new_auto_mode) {
	auto_mode = new_auto_mode;
}

std::string Path::get_start () {
	return "d=\"";
}

void Path::start () {
	obj.new_line(get_start());
}

std::string Path::get_end () {
	return "\"";
}

void Path::end () {
	obj() += get_end();
}



std::string Path::get_Move (Point const & p) {
	return "M " + File::to_str(p.x) + " " + File::to_str(p.y);
}

void Path::Move (Point const & p) {
	if (line_break) {
		obj.new_line(get_Move(p));
	} else {
		obj() += " " + get_Move(p);
	}
}

std::string Path::get_move (Point const & p) {
	return "m " + File::to_str(p.x) + " " + File::to_str(p.y);
}

void Path::move (Point const & p) {
	if (line_break) {
		obj.new_line(get_Move(p));
	} else {
		obj() += " " + get_Move(p);
	}
}

std::string Path::get_close () {
	return "z";
}

void Path::close () {
	if (line_break) {
		obj.new_line(get_close());
	} else {
		obj() += " " + get_close();
	}
}

std::string Path::get_Line (Point const & p) {
	return "L " + File::to_str(p.x) + " " + File::to_str(p.y);
}

void Path::Line (Point const & p) {
	if (line_break) {
		obj.new_line(get_Line(p));
	} else {
		obj() += " " + get_Line(p);
	}
}

std::string Path::get_line (Point const & p) {
	return "l " + File::to_str(p.x) + " " + File::to_str(p.y);
}

void Path::line (Point const & p) {
	if (line_break) {
		obj.new_line(get_Line(p));
	} else {
		obj() += " " + get_Line(p);
	}
}

} // namespace graphics::svg::object::basic
