namespace array {

template <typename T, unsigned char d>
Basic<T, d>::Basic (Basic::Point a_, Basic::Point b_) :
	_dim(d), _a(a_), _b(b_), _volume(0), _shift(0)
{
	_size = _b - _a;
	
	for (index = 0; index < d; index++ ) {
		_volume *= _size[index];
		_shift = _shift * _size[index] - _a[index];
	}
	
	values.resize(_volume, 0);
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
uint8_t Basic<T, d>::get_dim () const {
	return _dim;
}

template <typename T, unsigned char d>
array_size_t Basic<T, d>::get_shift () const {
	return _shift;
}

template <typename T, unsigned char d>
T & Basic<T, d>::get_value (array_size_t hash) {
	return values[hash];
}

template <typename T, unsigned char d>
T const & Basic<T, d>::get_value (array_size_t hash) const {
	return values[hash];
}

template <typename T, unsigned char d>
T & Basic<T, d>::operator() (Basic::Point const & p) {
	id = 0;
	for (index = 0; index < d; index++) {
		id = id * _size[index] + p[index];
	}
	
	return values[id + _shift];
}

template <typename T, unsigned char d>
T const & Basic<T, d>::operator() (Basic::Point const & p) const {
	id = 0;
	for (index = 0; index < d; index++) {
		id = id * _size[index] + p[index];
	}
	
	return values[id + _shift];
}

template <typename T, unsigned char d>
T Basic<T, d>::aproxim_value (math::type::Point<double,d> p) requires requires (T t, double x) { x * t; x + t; } {
	hypercube_index = 0;
	corner = p.template convert<decltype(ceil)>(ceil);
	p -= ::math::type::Point<double, d>(corner);
	for (hypercube_index = 0; hypercube_index < buffer.size(); hypercube_index++) {
		support_hypercube_index = hypercube_index;
		for (index = 0; index < d; index++) {
			hypercube_point[index] = support_hypercube_index % 2;
			support_hypercube_index >> 1;
		}
		buffer[hypercube_index] = this->operator()(corner + hypercube_point);
	}
	hypercube_index >> 1;
	for (auto index = 0; index < d; index++) {
		for (support_hypercube_index = 0; support_hypercube_index < hypercube_index; support_hypercube_index++) {
			buffer[support_hypercube_index] =
			buffer[support_hypercube_index] * p[d-1-index] +
			buffer[support_hypercube_index + hypercube_index] * (1 - p[d-1-index]);
		}
		hypercube_index >> 1;
	}
	return buffer[0];
}

} // namespace array