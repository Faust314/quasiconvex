#include "twodim.hpp"

namespace array {

template <typename value_t>
void Twodim<value_t>::init (coord_t const & x_size_, coord_t const & y_size_, value_t init_value, bool enable) {
	_x_size = x_size_;
	_y_size = y_size_;
	values.resize(_x_size * _y_size, init_value);
	used.resize(_x_size * _y_size, enable);
	links.reserve(_x_size);
	for (coord_t x = 0; x < _x_size; x++) {
		links.push_back(x * _y_size);
	}
}

template <typename value_t>
Twodim<value_t>::Twodim (coord_t const & x_size_, coord_t const & y_size_, value_t init_value, bool enable) {
	init(x_size_, y_size_, init_value, enable);
}



template <typename value_t>
template <typename another_value_t>
void Twodim<value_t>::init (Twodim<another_value_t> const & array) {
	init (array.x_size(), array.y_size());
	for (value_id_t value_id = 0; value_id < values.size(); value_id++) {
		used[value_id] = array.has_point(value_id);
	}
}



template <typename value_t>
coord_t Twodim<value_t>::x_size () const {
	return _x_size;
}

template <typename value_t>
coord_t Twodim<value_t>::y_size () const {
	return _y_size;
}

template <typename value_t>
value_id_t Twodim<value_t>::size () const {
	return values.size();
}



template <typename value_t>
value_id_t Twodim<value_t>::value_id (Point const & p) const {
	assert(0 <= p.x && p.x < _x_size && 0 <= p.y && p.y < _y_size);
	return links[p.x] + p.y;
}



template <typename value_t>
bool Twodim<value_t>::has_point (Point const & p) const {
	assert(0 <= p.x && p.x < _x_size && 0 <= p.y && p.y < _y_size);
	return used[links[p.x] + p.y];
}

template <typename value_t>
bool Twodim<value_t>::has_point (value_id_t value_id) const {
	assert(0 <= value_id && value_id < values.size());
	return used[value_id];
}

template <typename value_t>
value_t Twodim<value_t>::value (Point const & p) const {
	assert(0 <= p.x && p.x < _x_size && 0 <= p.y && p.y < _y_size);
	return values[links[p.x] + p.y];
}

template <typename value_t>
value_t Twodim<value_t>::value (value_id_t value_id) const {
	assert(0 <= value_id && value_id < values.size());
	return values[value_id];
}

template <typename value_t>
value_t & Twodim<value_t>::value (Point const & p) {
	assert(0 <= p.x && p.x < _x_size && 0 <= p.y && p.y < _y_size);
	return values[links[p.x] + p.y];
}

template <typename value_t>
value_t & Twodim<value_t>::value (value_id_t value_id) {
	assert(0 <= value_id && value_id < values.size());
	return values[value_id];
}



template <typename value_t>
void Twodim<value_t>::disable_point (Point const & p) {
	assert(0 <= p.x && p.x < _x_size && 0 <= p.y && p.y < _y_size);
	used[links[p.x] + p.y] = false;
}

template <typename value_t>
void Twodim<value_t>::disable_point (value_id_t value_id) {
	assert(0 <= value_id && value_id < values.size());
	used[value_id];
}

template <typename value_t>
void Twodim<value_t>::enable_point (Point const & p) {
	assert(0 <= p.x && p.x < _x_size && 0 <= p.y && p.y < _y_size);
	used[links[p.x] + p.y] = true;
}

template <typename value_t>
void Twodim<value_t>::enable_point (value_id_t value_id) {
	assert(0 <= value_id && value_id < values.size());
	used[value_id];
}

} // namespace array
