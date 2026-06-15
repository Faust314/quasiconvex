#pragma once

#include "types.hpp"
#include "../Algo/convex_hull.tpp"
#include "../Algo/heap.hpp"

#include <unordered_map>
#include <array>

namespace hull {

template<typename value_t>
void calculate_max_biconcave_function(array::Twodim<value_t> & real_array, Point const & center);



namespace detail {

template <typename value_t>
class MaxBiconcaveFunction {
public:
	using Heap = algo::Heap<value_t, coord_t>;
	typedef uint8_t dir_id_t;
	
public:
	explicit MaxBiconcaveFunction (array::Twodim<value_t> & real_array_);
	
	void operator() (Point const & center);

private:
	array::Twodim<value_t> * real_array;
	Heap single_edges_heap;
	Heap double_edges_heap;
	value_t shift = 0;
	
	std::vector<Point> single_edge_endpoints;
	std::vector<std::pair<Point, dir_id_t>> double_edge_endpoints;
	std::unordered_map<array_size_t, array_size_t> single_edge_ids;
	std::unordered_map<array_size_t, array_size_t> double_edges_ids;
	
	bool in_array (Point p) const;
	array_size_t edge_hash (Point p, dir_id_t dir);
	void add_shift (value_t new_shift);
	void enable_point (Point p);
	void erase_single_point (Point p, dir_id_t dir_id);
	void erase_double_point (Point p, dir_id_t dir_id);
	void insert_single_edge (Point p, dir_id_t dir_id);
	void insert_double_edge (Point p, dir_id_t dir_id);
	void insert_point (Point p);
	
	inline static std::array<Point, 4> const dirs = {Point(1,0), Point(0,1), Point(-1,0), Point(0,-1)};
	
	bool check_center (Point const & center);
};
	
} // detail

} // namespace hull