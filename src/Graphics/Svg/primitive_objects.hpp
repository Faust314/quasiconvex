#pragma once

#include "basic.hpp"
#include "object_styles.hpp"

namespace graphics::svg::object::basic {

struct Point {
	double x;
	double y;
	Point(double x_, double y_);
	
	Point operator + (Point const & p) const;
	Point operator - (Point const & p) const;
};

struct Origin {
	double x0;
	double y0;
	
	Origin() = default;
	Origin(Point p);
	Origin(double x0_, double y0_);
	
	Point operator()(double x, double y);
	Point operator() (Point p);
};

graphics::svg::Object line(Point p1, Point p2, Stroke const & stroke = Stroke(RGB_O()));

struct Path {
private:
	Object obj;
	static bool line_break;
	static bool auto_mode;
	
public:
	Object operator() ();
	
	explicit Path(Fill const & fill = Fill(), Stroke const & stroke = Stroke(RGB_O()));
	static Object get_object(Fill const & fill = Fill(), Stroke const & stroke = Stroke(RGB_O()));
	
	static void assign_line_break(bool new_line_break);
	static void assign_auto_mode(bool new_auto_mode);
	
	static std::string get_start();
	void start();
	static std::string get_end();
	void end();
	
	static std::string get_Move(Point const & p);
	void Move(Point const & p);
	static std::string get_move(Point const & p);
	void move(Point const & p);
	
	static std::string get_close();
	void close();
	
	static std::string get_Line(Point const & p);
	void Line(Point const & p);
	static std::string get_line(Point const & p);
	void line(Point const & p);
};




} // namespace graphics::svg::object::basic
