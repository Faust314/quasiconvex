#pragma once

#include <concepts>

namespace algo::convex {

typedef double value_t;

template <class F, typename Arg>
concept onedim_func = requires (Arg arg, F f) {
	std::is_same_v<decltype(f(arg)), value_t &>;
};

} // namespace alg::convex