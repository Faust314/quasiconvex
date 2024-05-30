#pragma once

#include "onedim_basic.hpp"

namespace algo::convex {

template<bool is_convex, typename Arg, onedim_func<Arg> F>
void convex_hull (F & f, Arg a, Arg b) {
	std::vector<Arg> v;
	v.reserve(b - a);
	v.push_back(a);
	v.push_back(a + 1);
	for (Arg id = a + 2; id <= b; id++) {
		do {
			if constexpr (is_convex) {
				if (
					(id - v[v.size() - 2]) * f(v[v.size() - 1]) >
					(v[v.size() - 1] - v[v.size() - 2]) * f(id) +
					(id - v[v.size() - 1]) * f(v[v.size() - 2])
				) {
					v.pop_back();
				} else {
					break;
				}
			} else {
				if (
					(id - v[v.size() - 2]) * f(v[v.size() - 1]) <
					(v[v.size() - 1] - v[v.size() - 2]) * f(id) +
					(id - v[v.size() - 1]) * f(v[v.size() - 2])
				) {
					v.pop_back();
				} else {
					break;
				}
			}
		} while (v.size() >= 2);
		v.push_back(id);
	}
	for (Arg i = 0; i < v.size() - 1; i++) {
		for (Arg id = v[i] + 1; id < v[i + 1]; id++) {
			f(id) = ((v[i + 1] - id) * f(v[i]) + (id - v[i]) * f(v[i + 1])) / (v[i + 1] - v[i]);
		}
	}
}

} // namespace algo::convex