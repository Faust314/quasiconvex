#include "path.hpp"

namespace graphics::twodim::svg {

void Path::init (Output & output)
{
	_output = & output;
}

Path::Path (Output & output) {
	_output = & output;
}





void Path::begin () const {
	_output->ofs() << "<path";
	_output->change_space(3);
}

void Path::path_id (object_id_t id) const {
	_output->ofs() << "id=\"path" << id << "\"";
}





void Path::start (Point const & p) const {
	_output->get_ofs() << "M " << p.x << " " << p.y;
}

void Path::Move (Point const & p) const {
	_output->get_ofs() << " M " << p.x << " " << p.y;
}

void Path::move (Point const & dp) const {
	_output->get_ofs() << " m " << dp.x << " " << dp.y;
}





void Path::Line (Point const & p) const {
	_output->get_ofs() << " L " << p.x << " " << p.y;	
}

void Path::line (Point const & dp) const {
	_output->get_ofs() << " l " << dp.x << dp.y;
}



void Path::Line_horizontal (coord_t x) const {
	_output->get_ofs() << " H " << x;
}

void Path::line_horizontal (coord_t dx) const {
	_output->get_ofs() << " h " << dx;
}

void Path::Line_vertical (coord_t y) const {
	_output->get_ofs() << " V " << y;
}

void Path::line_vertical (coord_t dy) const {
	_output->get_ofs() << " v " << dy;
}





void Path::Bezier_curve (Point const & p1, Point const & p2, Point const & p) const {
	_output->get_ofs() <<
		" C " << p1.x << " " << p1.y << ", " << p2.x << " " << p2.y << ", " << p.x << " " << p.y;
}

void Path::bezier_curve (Point const & dp1, Point const & dp2, Point const & dp) const {
	_output->get_ofs() <<
		" c " << dp1.x << " " << dp1.y << ", " << dp2.x << " " << dp2.y << ", " << dp.x << " " << dp.y;
}

void Path::Bezier_curve_short (Point const & p2, Point const & p) const {
	_output->get_ofs() <<
		" C " << p2.x << " " << p2.y << ", " << p.x << " " << p.y;
}

void Path::bezier_curve_short (Point const & dp2, Point const & dp) const {
	_output->get_ofs() <<
		" c " << dp2.x << " " << dp2.y << ", " << dp.x << " " << dp.y;
}



void Path::Quadratic_curve (Point const & p1, Point const & p) const {
	_output->get_ofs() <<
		" Q " << p1.x << " " << p1.y << ", " << p.x << " " << p.y;
}

void Path::quadratic_curve (Point const & dp1, Point const & dp) const {
	_output->get_ofs() <<
		" q " << dp1.x << " " << dp1.y << ", " << dp.x << " " << dp.y;
}

void Path::Quadratic_curve_short (Point const & p) const {
	_output->get_ofs() <<
		" Q " << p.x << " " << p.y;
}

void Path::quadratic_curve_short (Point const & dp) const {
	_output->get_ofs() <<
		" Q " << dp.x << " " << dp.y;
}





void Path::Arc (
	coord_t rx, coord_t ry, coord_t rotation, bool is_large_arc, bool is_counterclockwise, Point const & p
) const {
	_output->get_ofs() <<
		" A " << rx << " " << ry << " " << rotation << " " <<
		is_large_arc << " " << is_counterclockwise << " " << p.x << " " << p.y;
}
void Path::arc (
	coord_t rx, coord_t ry, coord_t rotation, bool is_large_arc, bool is_counterclockwise, Point const & dp
) const {
	_output->get_ofs() <<
		" a " << rx << " " << ry << " " << rotation << " " <<
		is_large_arc << " " << is_counterclockwise << " " << dp.x << " " << dp.y;
}





void Path::close_path () const {
	_output->get_ofs() << " Z";
}
	
} // namespace graphics::twodim::svg
