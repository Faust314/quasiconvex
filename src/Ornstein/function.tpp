#pragma once

#include "function.hpp"
#include "../Algo/Convex/Onedim/onedim_basic.tpp"

#include <iostream>

// TODO добавить инициализацию точки одним значением

namespace ornstein {

template <int d>
void Function<d>::init (value_t p_, value_t c_, array_coord_t n_, coord_t l_) {
	_p = p_;
	_c = c_;
	
	_n = n_;
	_l = l_;
	_delta = l_ / n_;
	sqr_delta = 1 / _delta / _delta;
	
	f.values = & _values;
	
	init_array();
}

template <int d>
Function<d>::Function (value_t p_, value_t c_, array_coord_t n_, coord_t l_) :
	_p(p_),
	_c(c_),
	_n(n_),
	_l(l_),
	_delta(l_ / n_),
	sqr_delta(1 / _delta / _delta),
	f(_values)
{
	init_array();
}

template <int d>
array::Basic<value_t, d> const & Function<d>::values () const {
	return _values;
}

template <int d>
array_coord_t const & Function<d>::n () const {
	return _n;
}

template <int d>
coord_t const & Function<d>::l () const {
	return _l;
}

template <int d>
value_t const & Function<d>::delta () const {
	return _delta;
}

template <int d>
value_t const & Function<d>::p () const {
	return _p;
}

template <int d>
value_t const & Function<d>::c () const {
	return _c;
}



template <int d>
void Function<d>::calculate_convex_hull (uint16_t number) {
	std::cout << "Calculate convex hull\n";
	for (uint16_t i = 0; i < number; i++) {
		std::cout << i << " \\ " << number << "\n"; 
		for (index_t dir = 0; dir < d; dir++) {
			convex_hull(dir);
		}
	}
}



template <int d>
void Function<d>::calculate_linearity () {
	std::cout << "Calculate linearity\n";
	
	ArrayPoint<d> point;
	index_t index = d - 1;
	point[d - 1] = -_n + 1;
	
	value_t v0, v1, v2;
	
	for (;;) {
		if (point[index] > _n - 1) {
			index++;
			if (index >= d) {
				break;
			}
			point[index]++;
			continue;
		}
		if (index > 0) {
			index--;
			point[index] = -_n + 1;
			continue;
		}
		for (index_t i = 0; i < d; i++) {
			v1 = _values(point);
			point[i]--;
			v0 = _values(point);
			point[i] += 2;
			v2 = _values(point);
			point[i]--;
			_linearity_values(point)[i] = onedim_linearity((v0 + v2 - 2 * v1) * sqr_delta);
		}
		point[index]++;
	}
}

template <int d>
array::Basic<typename Function<d>::linearity, d> const & Function<d>::linearity_values () const {
	return _linearity_values;
}




template <int d>
Function<d>::F::F (array::Basic<value_t, d> & values_) :
	values(& values_)
{}

template <int d>
value_t & Function<d>::F::operator() (array_coord_t id) {
	return values->get_value(a * id + b);
}



template <int d>
void Function<d>::init_array () {
	ArrayPoint<d> point;
	point.modify([&] (array_coord_t & id) {id = _n;});
	_values.init(-point, point);
	_linearity_values.init(-point, point);
	
	for (array::id_t id = 0; id < _values.volume(); id++) {
//		_values.get_value(id) = std::numeric_limits<value_t>::max();
		_values.get_value(id) = 1000;
	}
	
	index_t index = d - 1;
	point[d - 1] = -1;
	
	for (;;) {
		if (point[index] > 1) {
			index++;
			if (index >= d) {
				break;
			}
			point[index] += 2;
			continue;
		}
		if (index > 0) {
			index--;
			point[index] = -1;
			continue;
		}
		for (array_coord_t x = 1; x <= _n; x++) {
			_values(point * x) = std::pow(_delta * x, _p);
		}
		point[index] += 2;
	}
	point.modify([this](array_coord_t & id) {id = 1;});
	for (array_coord_t x = 1; x <= _n; x++) {
		_values(point * x) = -_c * std::pow(_delta * x, _p);
		_values(point * (-x)) = -_c * std::pow(_delta * x, _p);
	}
	point.modify([this](array_coord_t & id) {id = 0;});
	_values(point) = 0;
}



template <int d>
void Function<d>::convex_hull (index_t dir) {
	ArrayPoint<d> point;
	index_t index = d - 1;
	point[d - 1] = -_n;
	
	for (;;) {
		if (point[index] > _n) {
			index++;
			if (index == dir) {
				index++;
			}
			if (index >= d) {
				break;
			}
			point[index]++;
			continue;
		}
		if (index > 0) {
			index--;
			point[index] = -_n;
			continue;
		}
		f.b = _values.get_hash(point);
		point[dir]++;
		f.a = _values.get_hash(point) - f.b;
		f.b += _n * f.a;
		algo::convex::convex_hull<true>(f, -_n, _n);
		point[dir]--;
		if (index == dir) {
			point[index] = _n + 1;
			continue;
		}
		point[index]++;
	}
}



template <int d>
bool Function<d>::onedim_linearity (value_t derivative) {
	return derivative < 0.000000001;
}

} // namespace ornstein

