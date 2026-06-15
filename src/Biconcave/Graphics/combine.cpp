#include "combine.hpp"

#include <iostream>

namespace biconcave {

void Combine::init (coord_t const & x_size, coord_t const & y_size) {
	edges.init(x_size + 1, y_size + 1, {false, false, false, false}, false);
}

Combine::Combine (coord_t const & x_size, coord_t const & y_size) {
	init(x_size, y_size);
}

void Combine::add_point (ArrayPoint const & p) {
	include_point(ArrayPoint(p.x, p.y + 1));
	include_point(ArrayPoint(p.x, p.y + 2));
	include_point(ArrayPoint(p.x + 1, p.y));
	include_point(ArrayPoint(p.x + 1, p.y + 1));
	
	edges.value(ArrayPoint(p.x, p.y + 1))[3] = true;
	edges.value(ArrayPoint(p.x, p.y + 2))[2] = true;
	edges.value(ArrayPoint(p.x + 1, p.y))[0] = true;
	edges.value(ArrayPoint(p.x + 1, p.y + 1))[1] = true;
}

void Combine::add_point1 (ArrayPoint const & p) {
	include_point(ArrayPoint(p.x, p.y));
	include_point(ArrayPoint(p.x, p.y + 1));
	include_point(ArrayPoint(p.x + 1, p.y));
	include_point(ArrayPoint(p.x + 1, p.y + 1));
	
	edges.value(ArrayPoint(p.x, p.y))[3] = true;
	edges.value(ArrayPoint(p.x, p.y + 1))[2] = true;
	edges.value(ArrayPoint(p.x + 1, p.y))[0] = true;
	edges.value(ArrayPoint(p.x + 1, p.y + 1))[1] = true;
}

void Combine::erase_extra_edges () {
	for (ArrayPoint p: using_nodes) {
		if (edges.value(p)[0]) {
			if (edges.value(ArrayPoint(p.x, p.y + 1))[2]) {
				edges.value(p)[0] = false;
				edges.value(ArrayPoint(p.x, p.y + 1))[2] = false;
			}
		}
		if (edges.value(p)[1]) {
			if (edges.value(ArrayPoint(p.x - 1, p.y + 1))[3]) {
				edges.value(p)[1] = false;
				edges.value(ArrayPoint(p.x - 1, p.y + 1))[3] = false;
			}
		}
	}
}

void Combine::erase_extra_edges1 () {
	for (ArrayPoint p: using_nodes) {
		if (edges.value(p)[0]) {
			if (edges.value(ArrayPoint(p.x, p.y + 1))[2]) {
				edges.value(p)[0] = false;
				edges.value(ArrayPoint(p.x, p.y + 1))[2] = false;
			}
		}
		if (edges.value(p)[1]) {
			if (edges.value(ArrayPoint(p.x - 1, p.y))[3]) {
				edges.value(p)[1] = false;
				edges.value(ArrayPoint(p.x - 1, p.y))[3] = false;
			}
		}
	}
}

std::vector<std::vector<Point>> Combine::calculate_contours () {
	std::vector<std::vector<Point>> contours;
	std::vector<ArrayPoint> contour;
	for (ArrayPoint p : using_nodes) {
		while (is_using(p)) {
			contour.clear();
			uint8_t dir = next_dir(p);
			edges.value(p)[dir] = false;
			contour.push_back(p);
			p = next_point(p, dir);
			while (p != contour.front()) {
				dir = opposite_dir(dir);
				dir = next_dir(p, dir);
				edges.value(p)[dir] = false;
				contour.emplace_back(p);
				p = next_point(p, dir);
			}
			contours.emplace_back();
			for (ArrayPoint const & q : contour) {
				contours.back().emplace_back(q.x - 0.5, q.y - 1);
			}
		}
	}
	
	return contours;
}

std::vector<std::vector<Point>> Combine::calculate_contours1 () {
	std::vector<std::vector<Point>> contours;
	std::vector<ArrayPoint> contour;
	for (ArrayPoint p : using_nodes) {
		while (is_using(p)) {
			contour.clear();
			uint8_t dir = next_dir(p);
			edges.value(p)[dir] = false;
			contour.push_back(p);
			p = next_point1(p, dir);
			while (p != contour.front()) {
				dir = opposite_dir(dir);
				dir = next_dir(p, dir);
				edges.value(p)[dir] = false;
				contour.emplace_back(p);
				p = next_point1(p, dir);
			}
			contours.emplace_back();
			for (ArrayPoint const & q : contour) {
				contours.back().emplace_back(q.x - 0.5, q.y - 0.5);
			}
		}
	}
	
	return contours;
}



void Combine::include_point (ArrayPoint const & p) {
	if (! edges.has_point(p)) {
		edges.enable_point(p);
		using_nodes.push_back(p);
	}
}

ArrayPoint Combine::next_point (ArrayPoint const & p, uint8_t dir) {
	if (dir == 0) {
		return ArrayPoint(p.x, p.y + coord_t(1));
	} else if (dir == 1) {
		return ArrayPoint(p.x - 1, p.y + 1);
	} else if (dir == 2) {
		return ArrayPoint(p.x, p.y - 1);
	} else {
		return ArrayPoint(p.x + 1, p.y - 1);
	}
}

ArrayPoint Combine::next_point1 (ArrayPoint const & p, uint8_t dir) {
	if (dir == 0) {
		return ArrayPoint(p.x, p.y + coord_t(1));
	} else if (dir == 1) {
		return ArrayPoint(p.x - 1, p.y);
	} else if (dir == 2) {
		return ArrayPoint(p.x, p.y - 1);
	} else {
		return ArrayPoint(p.x + 1, p.y);
	}
}

uint8_t Combine::opposite_dir (uint8_t dir) {
	return (dir + 2) % 4;
}

uint8_t Combine::next_dir (ArrayPoint const & p, uint8_t dir) const {
	dir = (dir + 1) % 4;
	while (! edges.value(p)[dir]) {
		dir = (dir + 1) % 4;
	}
	return dir;
}

uint8_t Combine::next_dir (ArrayPoint const & p) const {
	uint8_t dir = 0;
	while (! edges.value(p)[dir]) {
		dir = (dir + 1) % 4;
	}
	return dir;
}

bool Combine::is_using (ArrayPoint const & p) const {
	return edges.value(p)[0] || edges.value(p)[1] || edges.value(p)[2] || edges.value(p)[3];
}
	
} // namespace biconcave
