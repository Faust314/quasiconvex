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
void Function<d>::calculate_convex_hull (uint16_t number, uint16_t hom_number, coord_t ratio) {
//	std::cout << "Calculate convex hull\n";
	uint16_t k = 0;
	for (uint16_t i = 0; i < number; i++) {
		k++;
//		std::cout << i << " \\ " << number << "\n"; 
		for (index_t dir = 0; dir < d; dir++) {
			convex_hull(dir);
		}
		if (k == hom_number) {
			k = 0;
			calculate_homogeneous(ratio);
		}
	}
}

template <int d>
void Function<d>::calculate_harmonic_hull (uint16_t number, uint16_t hom_number, coord_t ratio) {
	std::cout << "Calculate harmonic hull\n";
	uint16_t k = 0;
	for (uint16_t i = 0; i < number; i++) {
		k++;
		std::cout << i << " \\ " << number << "\n";
		for (index_t dir = 0; dir < d / 2; dir++) {
			harmonic_hull(dir * 2, dir * 2 + 1);
		}
		if (k == hom_number) {
			k = 0;
			calculate_homogeneous(ratio);
		}
	}
//	calculate_homogeneous(ratio);
}



template <int d>
void Function<d>::calculate_linearity () {
	std::cout << "Calculate linearity\n";
	
	ArrayPoint<d> point;
	index_t index = d - 1;
	point[d - 1] = -_n + 1;
	
	value_t v0, v1, v2;
	
	for (;;) {
//		std::cout << point[0] << " " << point[1] << " " << point[2] << " " << point[3] << "\n";
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
	
	{
		ArrayPoint<d> p0;
		p0.modify([&] (array_coord_t & id) {id = 0;});
		ArrayPoint<d> p1 = p0;
		for (int i = 0; i < d; i++) {
			p1[i] = 1;
			shifts[i] = _values.get_hash(p1) - _values.get_hash(p0);
			p1[i] = 0;
		}
	}
	
	for (array::id_t id = 0; id < _values.volume(); id++) {
//		_values.get_value(id) = std::numeric_limits<value_t>::max();
		_values.get_value(id) = 1;
	}
	
	index_t index = d - 1;
	point[d - 1] = -_n;
	
	array_coord_t max_coord;
	
	for (;;) {
		if (point[index] > _n) {
			index++;
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
		max_coord = std::numeric_limits<array_coord_t>::min();
		for (index_t i = 0; i < d; i++) {
			max_coord = std::max(max_coord, std::abs(point[i]));
		}
		_values(point) = std::pow(_delta * max_coord, _p);
		point[index]++;
	}
	
	point.modify([](array_coord_t & id) {id = 1;});
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
void Function<d>::harmonic_hull (index_t dir1, index_t dir2) {
	ArrayPoint<d> point;
	index_t index = d - 1;
	point[d - 1] = -_n + 1;
	
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
		point_harmonic_hull(point, dir1, dir2);
		point[index]++;
	}
}

template <int d>
void Function<d>::point_harmonic_hull (ArrayPoint<d> point, index_t dir1, index_t dir2) {
#ifndef NDEBUG
	for (int i = 0; i < d; i++) {
		if (point[i] == -_n || point[i] == _n) {
			assert(false);
		}
	}
	assert(dir1 != dir2);
#endif
	array::id_t hash = _values.get_hash(point);
	_values(point) = std::min(_values(point), (
		_values.get_value(hash + shifts[dir1]) +
		_values.get_value(hash - shifts[dir1]) +
		_values.get_value(hash + shifts[dir2]) +
		_values.get_value(hash - shifts[dir2])
	) / 4);
}



template <int d>
void Function<d>::calculate_homogeneous (coord_t ratio) {
	for (index_t dir = 0; dir < d; dir++) {
		for (coord_t x : {-_n, _n}) {
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
				point[dir] = x;
				calculate_homogeneous_point(point, ratio);
				if (index == dir) {
					point[index] = _n + 1;
					continue;
				}
				point[index]++;
			}
		}
	}
}

template <int d>
void Function<d>::calculate_homogeneous_point (ArrayPoint<d> point, coord_t ratio) {
	Point<d> p = Point<d>(point) * ratio;
	_values(point) = std::min(_values(point), _values.approxim_value(p) * std::pow(ratio, -_p));
}



template <int d>
bool Function<d>::onedim_linearity (value_t derivative) {
	return derivative < 0.000000001;
}

} // namespace ornstein

