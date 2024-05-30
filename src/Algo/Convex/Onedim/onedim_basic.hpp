#pragma once

#include "../types.hpp"

namespace algo::convex {

template<bool is_convex, typename Arg, onedim_func<Arg> F>
void convex_hull (F & f, Arg a, Arg b);
	
} // namespace algo::convex