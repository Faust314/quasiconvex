#include "profile.hpp"

#include "../Objects/cuboid.hpp"
#include "../../../Array/Basic/basic.tpp"
#include "../../../Math/Geometry/Stereometry/threedim_point.tpp"
#include "../../../Math/Geometry/Multidimensional/multi_point.tpp"

#include <cassert>

namespace graphics::threedim::str {

bool Profile::ProfilePoint::is_empty () const {
	return _empty;
}

void Profile::ProfilePoint::clear () {
	_empty = true;
}

void Profile::ProfilePoint::assign_color (color::RGB const & color_) {
	_color = color_;
}

color::RGB & Profile::ProfilePoint::color () {
	assert(!_empty);
	return _color;
}



void Profile::init (Profile::ArrayPoint const & a, Profile::ArrayPoint const & b) {
	_profile_cells.init({a.x, a.y, a.z}, {b.x, b.y, b.z});
}

Profile::Profile (Profile::ArrayPoint const & a, Profile::ArrayPoint const & b) :
	_profile_cells({a.x, a.y, a.z}, {b.x, b.y, b.z})
{}

array::Basic<Profile::ProfilePoint, 3> & Profile::profile_cells () {
	return _profile_cells;
}

void Profile::output (Model & model, math::geom::threedim::Point<coord_t> a, math::geom::threedim::Point<coord_t> b) {
	// TODO сделать вывод более оптимальным
	
	coord_t step[3];
	coord_t shift[3];
	
	step[0] = (b.x - a.x) / (_profile_cells.b()[0] - _profile_cells.a()[0] + 1);
	step[1] = (b.y - a.y) / (_profile_cells.b()[1] - _profile_cells.a()[1] + 1);
	step[2] = (b.z - a.z) / (_profile_cells.b()[2] - _profile_cells.a()[2] + 1);
	shift[0] = -_profile_cells.a()[0] * step[0] + a.x;
	shift[1] = -_profile_cells.a()[1] * step[1] + a.y;
	shift[2] = -_profile_cells.a()[2] * step[2] + a.z;
	
	math::geom::multi::Point<array_coord_t , 3> point, point1;
	math::geom::index_t index = 2;
	point[2] = _profile_cells.a()[2];
	math::geom::index_t dir, dir1, dir2;
	
	using MultiPoint = math::geom::multi::Point<coord_t, 3>;
	
	auto output_front_rect = [& model, & shift, & step, & dir1, & dir2] (
		math::geom::multi::Point<array_coord_t , 3> const & q, ProfilePoint * cell
	) {
		model.add_color(cell->color());
		MultiPoint p = {shift[0] + step[0] * q[0], shift[1] + step[1] * q[1], shift[2] + step[2] * q[2]};
		MultiPoint p0 = p;
		p[dir1] += step[dir1];
		MultiPoint p1 = p;
		p[dir2] += step[dir2];
		MultiPoint p2 = p;
		p[dir1] -= step[dir1];
		
		model.add_face({{p0[0], p0[1], p0[2]}, {p1[0], p1[1], p1[2]}, {p2[0], p2[1], p2[2]}, {p[0], p[1], p[2]}});
	};
	
	auto output_back_rect = [& model, & shift, & step, & dir, & dir1, & dir2] (
		math::geom::multi::Point<array_coord_t , 3> const & q, ProfilePoint * cell
	) {
		model.add_color(cell->color());
		MultiPoint p = {shift[0] + step[0] * q[0], shift[1] + step[1] * q[1], shift[2] + step[2] * q[2]};
		p[dir] += step[dir];
		MultiPoint p0 = p;
		p[dir2] += step[dir2];
		MultiPoint p1 = p;
		p[dir1] += step[dir1];
		MultiPoint p2 = p;
		p[dir2] -= step[dir2];
		
		model.add_face({{p0[0], p0[1], p0[2]}, {p1[0], p1[1], p1[2]}, {p2[0], p2[1], p2[2]}, {p[0], p[1], p[2]}});
	};
	
	ProfilePoint * cell, * cell1;
	for (dir = 0; dir < 3; dir++) {
		if (dir == 0) {
			dir1 = 1; dir2 = 2;
		} else if (dir == 1) {
			dir1 = 0; dir2 = 2;
		} else {
			dir1 = 0; dir2 = 1;
		}
		index = 2;
		point[2] = _profile_cells.a()[2];
		for (;;) {
			if (point[index] > _profile_cells.b()[index]) {
				index++;
				if (index == dir) {
					index++;
				}
				if (index > 2) {
					break;
				}
				point[index]++;
				continue;
			}
			if (index > 0) {
				index--;
				point[index] = _profile_cells.a()[index];
				continue;
			}
			
			cell = & _profile_cells(point);
			if (! cell->is_empty()) {
				output_front_rect(point, cell);
			}
			point1 = point;
			point1[dir]++;
			
			while (point1[dir] <= _profile_cells.b()[dir]) {
				cell1 = & _profile_cells(point1);
				if (! cell->is_empty() && cell1->is_empty()) {
					output_back_rect(point, cell);
				} else if (cell->is_empty() && ! cell1->is_empty()) {
					output_front_rect(point1, cell1);
				}
				point[dir]++;
				point1[dir]++;
				cell = cell1;
			}
			if (! cell->is_empty()) {
				output_back_rect(point, cell);
			}
			
			point[dir] = _profile_cells.a()[dir];
			
			if (index == dir) {
				point[index] = _profile_cells.b()[index] + 1;
				continue;
			}
			
			point[index]++;
		}
	}
}

} // namespace graphics::threedim::str
