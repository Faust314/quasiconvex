#include "basic.hpp"

#include "../../Math/Geometry/Multidimensional/multi_point.tpp"

#include <cassert>

namespace array {

template <typename T, unsigned char d>
void Basic<T, d>::init (Basic::Point a_, Basic::Point b_) {
	_a = a_;
	_b = b_;
	_volume = 1;
	_shift = 0;
	
	_size = _b - _a;
	_size.modify([] (array_coord_t & id) {id++;});
	
	for (index_t index = 0; index < d; index++ ) {
		_volume *= _size[index];
		_shift = _shift * _size[index] - _a[index];
	}
	
	values.resize(_volume);
}

template <typename T, unsigned char d>
Basic<T, d>::Basic (Basic::Point a_, Basic::Point b_) :
	_a(a_), _b(b_), _volume(1), _shift(0)
{
	_size = _b - _a;
	_size.modify([] (array_coord_t & id) {id++;});
	
	for (index_t index = 0; index < d; index++ ) {
		_volume *= _size[index];
		_shift = _shift * _size[index] - _a[index];
	}
	
	values.resize(_volume);
}

template <typename T, unsigned char d>
typename Basic<T,d>::Point const & Basic<T, d>::a () const {
	return _a;
}

template <typename T, unsigned char d>
typename Basic<T,d>::Point const & Basic<T, d>::b () const {
	return _b;
}

template <typename T, unsigned char d>
typename Basic<T,d>::Point const & Basic<T, d>::size () const {
	return _size;
}

template <typename T, unsigned char d>
id_t const & Basic<T, d>::volume () const {
	return _volume;
}



template <typename T, unsigned char d>
index_t Basic<T, d>::get_dim () const {
	return d;
}

template <typename T, unsigned char d>
id_t Basic<T, d>::get_shift () const {
	return _shift;
}



template <typename T, unsigned char d>
id_t Basic<T, d>::get_hash (Basic::Point const & p) {
	id_t id = 0;
	for (index_t index = 0; index < d; index++) {
		id = id * _size[index] + p[index];
	}
	
	assert(0 <= id + _shift && id + _shift < values.size());
	return id + _shift;
}



template <typename T, unsigned char d>
T & Basic<T, d>::get_value (id_t hash) {
	return values[hash];
}

template <typename T, unsigned char d>
T const & Basic<T, d>::get_value (id_t hash) const {
	return values[hash];
}

template <typename T, unsigned char d>
T & Basic<T, d>::operator() (Basic::Point const & p) {
	id_t id = 0;
	for (index_t index = 0; index < d; index++) {
		id = id * _size[index] + p[index];
	}
	
	assert(0 <= id + _shift && id + _shift < values.size());
	return values[id + _shift];
}

template <typename T, unsigned char d>
T const & Basic<T, d>::operator() (Basic::Point const & p) const {
	// TODO проверить, как это работает
	
	id_t id = 0;
	for (index_t index = 0; index < d; index++) {
		id = id * _size[index] + p[index];
	}
	
	assert(0 <= id + _shift && id + _shift < values.size());
	return values[id + _shift];
}

template <typename T, unsigned char d>
T Basic<T, d>::approxim_value (math::geom::multi::Point<real_coord_t, d> p) requires requires (T t, double x) { x * t; x + t; } {
	id_t hypercube_index = 0;
	Point corner = p.template convert<array_coord_t>(ceil);
	p -= ::math::geom::multi::Point<double, d>(corner);
	T buffer(std::pow(2,d));
	Point hypercube_point;
	id_t aux_hypercube_index;
	
	// TODO можно сделать быстрее, если каждый раз добавлять 1 к corner и пересчитывать переходы 1 через разряды
	for (hypercube_index = 0; hypercube_index < buffer.size(); hypercube_index++) {
		aux_hypercube_index = hypercube_index;
		for (index_t index = 0; index < d; index++) {
			hypercube_point[index] = aux_hypercube_index % 2;
			aux_hypercube_index >> 1;
		}
		buffer[hypercube_index] = this->operator()(corner + hypercube_point);
	}
	hypercube_index >> 1;
	for (index_t index = 0; index < d; index++) {
		for (aux_hypercube_index = 0; aux_hypercube_index < hypercube_index; aux_hypercube_index++) {
			buffer[aux_hypercube_index] =
				buffer[aux_hypercube_index] * (1 - p[d - 1 - index]) +
				buffer[aux_hypercube_index + hypercube_index] * p[d - 1 - index];
		}
		hypercube_index >> 1;
	}
	return buffer[0];
}

} // namespace array