#pragma once

#include "function.hpp"

namespace ornstein {

template <int dim>
std::vector<coord_t> compute_asymp (
	std::vector<coord_t> p_array, uint16_t bin_iterations,
	ornstein::array_coord_t n, uint16_t N, uint16_t M, coord_t T, double alpha
);

} // namespace ornstein