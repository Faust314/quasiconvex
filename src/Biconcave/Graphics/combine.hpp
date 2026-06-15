#pragma once

#include "../types.hpp"

namespace biconcave {

class Combine {
private:
	using Edges = array::Twodim<std::array<bool, 4>>;
	
public:
	Combine () = default;
	void init (coord_t const & x_size, coord_t const & y_size);
	Combine (coord_t const & x_size, coord_t const & y_size);
	
	void add_point (ArrayPoint const & p);
	
	void add_point1 (ArrayPoint const & p);
	
	void erase_extra_edges ();
	
	void erase_extra_edges1 ();
	
	std::vector<std::vector<Point>> calculate_contours ();
	std::vector<std::vector<Point>> calculate_contours1 ();
	
private:
	Edges edges;
	std::vector<ArrayPoint> using_nodes;
	
	void include_point (ArrayPoint const & p);
	static ArrayPoint next_point (ArrayPoint const & p, uint8_t dir);
	static ArrayPoint next_point1 (ArrayPoint const & p, uint8_t dir);
	static uint8_t opposite_dir (uint8_t dir);
	uint8_t next_dir (ArrayPoint const & p, uint8_t dir) const;
	uint8_t next_dir (ArrayPoint const & p) const;
	bool is_using (ArrayPoint  const & p) const;
};

} // namespace biconcave