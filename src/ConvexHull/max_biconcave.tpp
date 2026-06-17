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
	real_array(& real_array_)
{}

template <typename value_t>
void MaxBiconcaveFunction<value_t>::operator() (Point const & center) {
	std::ofstream ofs("output/error.txt");
	
	assert(check_center(center));
	
	for (array_size_t value_id = 0; value_id < real_array->size(); value_id++) {
		real_array->disable_point(value_id);
	}
	
	insert_point(center);
	
	// std::cout << check_values() << "\n";
	int t = 0;
	
	while (! single_edges_heap.empty() || ! double_edges_heap.empty()) {
		if (
			double_edges_heap.empty() ||
			(! single_edges_heap.empty() && (single_edges_heap.top() < double_edges_heap.top()))
		) {
			// std::cout << "1 " << check_values() << "\n";
			// check_struct();
			add_shift(single_edges_heap.top());
			insert_point(single_edge_endpoints[single_edges_heap.top_id()]);
			// std::cout << "2 " << check_values() << "\n";
			// check_struct();
		} else {
			// std::cout << "3 " << check_values() << "\n";
			// check_struct();
			add_shift(double_edges_heap.top());
			// check_struct();
			std::pair<Point, dir_id_t> endpoints = double_edge_endpoints[double_edges_heap.top_id()];
			insert_point(endpoints.first + dirs[endpoints.second]);
			// check_struct();
			insert_point(endpoints.first - dirs[endpoints.second]);
			// std::cout << "4 " << check_values() << "\n";
			// check_struct();
		}
		t++;
		ofs << t << " " << shift << "\n";
		ofs.flush();
	}
}



template <typename value_t>
bool MaxBiconcaveFunction<value_t>::in_array (Point p) const {
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
	shift = std::max(new_shift, value_t(0));
}

template <typename value_t>
void MaxBiconcaveFunction<value_t>::enable_point (Point p) {
	real_array->enable_point(p);
	real_array->value(p) += shift;
}

template <typename value_t>
void MaxBiconcaveFunction<value_t>::erase_single_point (Point p, MaxBiconcaveFunction::dir_id_t dir_id) {
	std::unordered_map<array_size_t, array_size_t>::iterator it
		= single_edge_ids.find(edge_hash(p, dir_id));
	assert(it != single_edge_ids.end());
	single_edges_heap.erase(it->second);
	single_edge_ids.erase(it);
}

template <typename value_t>
void MaxBiconcaveFunction<value_t>::erase_double_point (Point p, MaxBiconcaveFunction::dir_id_t dir_id) {
	std::unordered_map<array_size_t, array_size_t>::iterator it
		= double_edges_ids.find(edge_hash(p, dir_id));
	assert(it != double_edges_ids.end());
	double_edges_heap.erase(it->second);
	double_edges_ids.erase(it);
}

template <typename value_t>
void MaxBiconcaveFunction<value_t>::insert_single_edge (Point p, MaxBiconcaveFunction::dir_id_t dir_id) {
	assert(in_array(p) && in_array(p - dirs[dir_id]) && in_array(p + dirs[dir_id]));
	single_edges_heap.push(
		2 * real_array->value(p) - (real_array->value(p - dirs[dir_id]) + real_array->value(p + dirs[dir_id]))
	);
	single_edge_ids.emplace(edge_hash(p, dir_id), single_edge_endpoints.size());
	single_edge_endpoints.push_back(p + dirs[dir_id]);
}

template <typename value_t>
void MaxBiconcaveFunction<value_t>::insert_double_edge (Point p, MaxBiconcaveFunction::dir_id_t dir_id) {
	assert(in_array(p) && in_array(p - dirs[dir_id]) && in_array(p + dirs[dir_id]));
	double_edges_heap.push(
		real_array->value(p) - (real_array->value(p - dirs[dir_id]) + real_array->value(p + dirs[dir_id])) * 0.5
	);
	double_edges_ids.emplace(edge_hash(p, dir_id % 2), double_edge_endpoints.size());
	double_edge_endpoints.push_back({p, dir_id});
}

template <typename value_t>
void MaxBiconcaveFunction<value_t>::insert_point (Point p) {
	Point p1, p2;
	enable_point(p);
	for (dir_id_t dir_id = 0; dir_id < 4; dir_id++) {
		p1 = p - dirs[dir_id];
		p2 = p1 - dirs[dir_id];
		if (in_array(p1) && in_array(p2)) {
			if (real_array->has_point(p1)) {
				if (real_array->has_point(p2)) {
					erase_single_point(p1, dir_id);
				} else {
					insert_single_edge(p1, (dir_id + 2) % 4);
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
				if (! real_array->has_point(p2)) {
					insert_double_edge(p, dir_id);
				} else {
					insert_single_edge(p, dir_id + 2);
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
	
template <typename value_t>
double MaxBiconcaveFunction<value_t>::check_values() {
	array::Twodim<value_t> temp_array = * real_array;
	for (coord_t x = 0; x < real_array->x_size(); x++) {
		for (coord_t y = 0; y < real_array->y_size(); y++) {
			if (! temp_array.has_point(Point({x,y}))) {
				temp_array.enable_point(Point({x, y}));
				temp_array.value(Point({x,y})) += shift;
			}
		}
	}
	
	double a = std::numeric_limits<double>::min();
	
	for (coord_t x = 0; x < real_array->x_size(); x++) {
		for (coord_t y = 0; y < real_array->y_size(); y++) {
			if (in_array(Point({x, y})) && in_array(Point({coord_t(x + 1), y})) && in_array(Point({coord_t(x - 1), y}))) {
				a = std::max(a,
					- 2 * temp_array.value(Point({x,y}))
					+ temp_array.value(Point({coord_t(x + 1),y})) + temp_array.value(Point({coord_t(x - 1),y}))
				);
			}
			if (in_array(Point({x, y})) && in_array(Point({x, coord_t(y + 1)})) && in_array(Point({x, coord_t(y - 1)}))) {
				a = std::max(a,
					- 2 * temp_array.value(Point({x,y}))
					+ temp_array.value(Point({x, coord_t(y + 1)})) + temp_array.value(Point({x,coord_t(y - 1)}))
				);
			}
		}
	}
	return a;
}

template <typename value_t>
double MaxBiconcaveFunction<value_t>::check_struct() {
	for (auto [hash, id] : single_edge_ids) {
		array_size_t point_id = hash / 4;
		Point p = real_array->point_by_id(point_id);
		dir_id_t dir_id = hash % 4;
		Point q = single_edge_endpoints[id];
		assert(q == p + dirs[dir_id]);
		assert(in_array(p) && in_array(p + dirs[dir_id]) && in_array(p - dirs[dir_id]));
		assert(real_array->has_point(p) && real_array->has_point(p - dirs[dir_id]) && ! real_array->has_point(p + dirs[dir_id]));
		double real_diff = 2 * real_array->value(p) -
			(real_array->value(p + dirs[dir_id]) + real_array->value(p - dirs[dir_id]) + shift);
		double diff = single_edges_heap.item(id) - shift;
		assert (std::abs(real_diff - diff) < 1e-9);
	}
	for (auto [hash, id] : double_edges_ids) {
		array_size_t point_id = hash / 4;
		Point p = real_array->point_by_id(point_id);
		dir_id_t dir_id = hash % 4;
		assert(dir_id == double_edge_endpoints[id].second);
		assert(p == double_edge_endpoints[id].first);
		assert(in_array(p) && in_array(p - dirs[dir_id]) && in_array(p + dirs[dir_id]));
		assert(real_array->has_point(p) && ! real_array->has_point(p - dirs[dir_id]) && ! real_array->has_point(p + dirs[dir_id]));
		double real_diff = real_array->value(p) -
			0.5 * (real_array->value(p + dirs[dir_id]) + real_array->value(p - dirs[dir_id]) + 2 * shift);
		double diff = double_edges_heap.item(id) - shift;
		assert (std::abs(real_diff - diff) < 1e-9);
	}
	
	return 0;
}
	
} // namespace detail
	
} // namespace hull
