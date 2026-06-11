#pragma once

#include "types.hpp"

#include <vector>
#include <valarray>

namespace array {

template <typename value_t>
class Twodim {
public:
	Twodim () = default;
	void init (coord_t const & x_size_, coord_t const & y_size_, value_t init_value = value_t(), bool enable = true);
	Twodim (coord_t const & x_size_, coord_t const & y_size_, value_t init_value = value_t(), bool enable = true);
	
	template <typename another_value_t>
	void init (Twodim<another_value_t> const & array);
	
	inline coord_t x_size () const;
	inline coord_t y_size () const;
	inline value_id_t size () const;
	
	inline value_id_t value_id (Point const & p) const;
	
	inline bool has_point (Point const & p) const;
	inline bool has_point (value_id_t value_id) const;
	inline value_t value (Point const & p) const;
	inline value_t value (value_id_t value_id) const;
	inline value_t & value (Point const & p);
	inline value_t & value (value_id_t value_id);
	
	inline void disable_point (Point const & p);
	inline void disable_point (value_id_t value_id);
	inline void enable_point (Point const & p);
	inline void enable_point (value_id_t value_id);
	
	inline void set_values (value_t const & value);
	
private:
	coord_t _x_size = 0;
	coord_t _y_size = 0;
	std::vector<value_id_t> links;
	std::vector<value_t> values;
	std::valarray<bool> used;
};
	
} // namespace array