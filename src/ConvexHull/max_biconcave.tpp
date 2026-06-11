#pragma once
#include "max_biconcave.hpp"

#include <cassert>

namespace hull {

template <typename value_t>
void calculate_max_biconcave_function (array::Twodim<value_t> & real_array, Point const & center) {
	detail::MaxBiconcaveFunction<value_t> max_biconcave_function(real_array);
	max_biconcave_function(center);
}





namespace detail {

template <typename value_t>
MaxBiconcaveFunction<value_t>::MaxBiconcaveFunction (array::Twodim<value_t> & real_array_) :
	real_array(& real_array_), single_edges_heap()
{}

template <typename value_t>
void MaxBiconcaveFunction<value_t>::operator() (Point const & center) {
	assert(check_center(center));
	
	for (array_size_t value_id = 0; value_id < real_array->size(); value_id++) {
		real_array->disable_point(value_id);
	}
	
	insert_point(center);
	
	while (! single_edges_heap.empty() || ! double_edges_ids.empty()) {
		if (single_edges_heap.top() < double_edges_heap.top()) {
			add_shift(single_edges_heap.top());
			insert_point(single_edge_endpoints[single_edges_heap.top_id()]);
		} else {
			add_shift(double_edges_heap.top());
			std::pair<Point, dir_id_t> const & endpoints = double_edge_endpoints[double_edges_heap.top_id()];
			insert_point(endpoints.first + dirs[endpoints.second]);
			insert_point(endpoints.first - dirs[endpoints.second]);
		}
	}
}



template <typename value_t>
bool MaxBiconcaveFunction<value_t>::in_array (Point const & p) const {
	return
		((0 <= p.x) && (p.x < real_array->x_size())) &&
		((0 <= p.y) && (p.y < real_array->y_size()));
}

template <typename value_t>
array_size_t MaxBiconcaveFunction<value_t>::edge_hash (Point p, dir_id_t dir) {
	return real_array->value_id(p) * 4 + dir;
}

template <typename value_t>
void MaxBiconcaveFunction<value_t>::add_shift (value_t new_shift) {
	shift += new_shift;
}

template <typename value_t>
void MaxBiconcaveFunction<value_t>::enable_point (Point const & p) {
	real_array->enable_point(p);
	real_array->value(p) += shift;
}

template <typename value_t>
void MaxBiconcaveFunction<value_t>::erase_single_point (Point const & p, MaxBiconcaveFunction::dir_id_t dir_id) {
	std::unordered_map<array_size_t, array_size_t>::iterator it
		= single_edge_ids.find(edge_hash(p, dir_id));
	single_edges_heap.erase(it->second);
	single_edge_ids.erase(it);
}

template <typename value_t>
void MaxBiconcaveFunction<value_t>::erase_double_point (Point const & p, MaxBiconcaveFunction::dir_id_t dir_id) {
	std::unordered_map<array_size_t, array_size_t>::iterator it
		= double_edges_ids.find(edge_hash(p, dir_id));
	double_edges_heap.erase(it->second);
	double_edges_ids.erase(it);
}

template <typename value_t>
void MaxBiconcaveFunction<value_t>::insert_single_edge (Point const & p, MaxBiconcaveFunction::dir_id_t dir_id) {
	assert(in_array(p) && in_array(p - dirs[dir_id]) && in_array(p + dirs[dir_id]));
	single_edges_heap.push(
		2 * real_array->value(p) - (real_array->value(p - dirs[dir_id]) + real_array->value(p + dirs[dir_id]))
	);
	single_edge_ids.emplace(real_array->value_id(p) * 4 + dir_id, single_edge_endpoints.size());
	single_edge_endpoints.push_back(p + dirs[dir_id]);
}

template <typename value_t>
void MaxBiconcaveFunction<value_t>::insert_double_edge (Point const & p, MaxBiconcaveFunction::dir_id_t dir_id) {
	assert(in_array(p) && in_array(p - dirs[dir_id]) && in_array(p + dirs[dir_id]));
	double_edges_heap.push(
		real_array->value(p) - (real_array->value(p - dirs[dir_id]) + real_array->value(p + dirs[dir_id]) * 0.5)
	);
	double_edges_ids.emplace(real_array->value_id(p) * 4 + dir_id % 2, double_edge_endpoints.size());
	double_edge_endpoints.emplace_back(p, dir_id);
}

template <typename value_t>
void MaxBiconcaveFunction<value_t>::insert_point (Point const & p) {
	Point p1, p2;
	enable_point(p);
	for (dir_id_t dir_id = 0; dir_id < 4; dir_id++) {
		p1 = p - dirs[dir_id];
		p2 = p - dirs[dir_id];
		if (in_array(p1) && in_array(p2)) {
			if (real_array->has_point(p1)) {
				erase_single_point(p1, dir_id);
				if (! real_array->has_point(p2)) {
					erase_double_point(p1, dir_id % 2);
				}
			}
		}
	}
	for (dir_id_t dir_id = 0; dir_id < 2; dir_id++) {
		p1 = p - dirs[dir_id];
		p2 = p + dirs[dir_id];
		if (in_array(p1) && in_array(p2)) {
			if (! real_array->has_point(p1)) {
				insert_single_edge(p, dir_id + 2);
				if (! real_array->has_point(p2)) {
					insert_single_edge(p, dir_id);
					insert_double_edge(p, dir_id);
				}
			} else if (! real_array->has_point(p2)) {
				insert_single_edge(p, dir_id);
			}
		}
	}
}



template <typename value_t>
bool MaxBiconcaveFunction<value_t>::check_center (Point const & center) {
	if (! in_array(center)) {
		return false;
	}
	for (dir_id_t dir_id = 0; dir_id < 4; dir_id++) {
		if (! in_array(center + dirs[dir_id])) {
			return false;
		}
	}
	return true;
}
	
} // namespace detail
	
} // namespace hull