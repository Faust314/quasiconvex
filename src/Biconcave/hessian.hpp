#pragma once

#include "../Array/twodim.hpp"
#include "../Math/Functions/func.hpp"
#include "types.hpp"

namespace biconcave {

class Hessian {
public:
	Hessian () = default;
	void init (RealArray const & real_array_, value_t step);
	Hessian (RealArray const & real_array_, value_t step);
	
	bool has_derivative (bool dim, ArrayPoint const & p) const;
	value_t derivative (bool dim, ArrayPoint const & p) const;
	
private:
	value_t div = 1;
	RealArray const * real_array = nullptr;
};
	
} // namespace biconvex