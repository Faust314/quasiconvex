#pragma once
#include "asymp.hpp"

#include "function.tpp"

namespace ornstein {

template <int dim>
std::vector<coord_t> compute_asymp (
	std::vector<coord_t> p_array, uint16_t bin_iterations,
	ornstein::array_coord_t n, uint16_t N, uint16_t M, coord_t T, double alpha
) {
	std::vector<coord_t> values;
	values.reserve(p_array.size());
	
	auto check = [&] (coord_t p, coord_t c) -> bool {
		ArrayPoint<dim> point;
		point.assign(0);
		Function<dim> orn(p, c, n, 1);
		orn.calculate_convex_hull(N, M, alpha);
		return orn.values()(point) > T;
	};
	
	for (size_t i = 0; i < p_array.size(); i++) {
		coord_t p = p_array[i];
		coord_t c0 = 0;
		coord_t c1 = 2;
		
		size_t it = 0;
		for (; it < bin_iterations; it++) {
			if (check(p, c1)) {
				c1 *= 2;
			} else {
				break;
			}
		}
		
		for (; it < bin_iterations; it++) {
			std::cout << i << "/" << p_array.size() << ", " << it << "/" << bin_iterations << "\n"; 
			coord_t c = (c0 + c1) / 2;
			if (check(p, c)) {
				c0 = c;
			} else {
				c1 = c;
			}
		}
		values.push_back((c0 + c1) / 2);
	}
	return values;
}
	
} // namespace ornstein#pragma once