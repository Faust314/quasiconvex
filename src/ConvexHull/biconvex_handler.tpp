#pragma once

#include "biconvex_handler.hpp"
#include "../Algo/convex_hull.tpp"

#include <iostream>

namespace hull {

template <typename value_t>
value_t & HullHandler<value_t>::PointAccess::operator() (coord_t coord) {
	return array->value(begin + step * coord);
}





template <typename value_t>
void HullHandler<value_t>::init (HullHandler::RealArray & array_) {
	array = & array_;
}

template <typename value_t>
HullHandler<value_t>::HullHandler (HullHandler::RealArray & array_) :
	array(& array_)
{}



template <typename value_t>
void HullHandler<value_t>::add_line (
	bool dim, Point const & first, Point const & step, coord_t segments
) {
	lines[dim].emplace_back(
		array->value_id(first),
		segments == 0 ? 0 :
		array->value_id(first + step) - array->value_id(first),
		segments
	);
}



template <typename value_t>
template <bool is_convex>
void HullHandler<value_t>::build_convex_hull (iter_id_t count) {
	PointAccess point_access (array);
	iter_id_t n = 1;
	for (iter_id_t iter_id = 0; iter_id < count; iter_id++) {
		while (iter_id >= n * (count / 10) && n <= 9) {
			std::cout << n << "0% ";
			n++;
		}
		for (uint8_t i = 0; i < 2; i++) {
			for (Line const & line : lines[i]) {
				point_access.begin = line.begin;
				point_access.step = line.step;
				algo::convex::convex_hull<false, coord_t, PointAccess>(point_access, 0, line.last);
			}
		}
	}
	std::cout << "100%\n";
}

} // namespace hull