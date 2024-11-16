#pragma once

#include "types.hpp"
#include "../Algo/convex_hull.tpp"

#include <array>

namespace hull {

template <typename value_t>
class HullHandler {
public:
	using RealArray = array::Twodim<value_t>;
	
public:
	struct Line {
	public:
		array_size_t begin;
		array_size_t step;
		coord_t last;
	};
	
	struct PointAccess {
		value_t & operator() (coord_t coord);
		
		RealArray * array;
		array_size_t begin;
		array_size_t step;
	};
	
public:
	HullHandler () = default;
	void init (RealArray & array_);
	explicit HullHandler (RealArray & array_);
	
	void add_line (bool dim, Point const & first, Point const & step, coord_t segments);
	
	template <bool is_convex>
	void build_convex_hull (iter_id_t count);
	
private:
	RealArray * array;
	std::array<std::vector<Line>, 2> lines;
};
	
} // namespace hull