#include "hessian.hpp"

namespace biconcave {

void Hessian::init (RealArray const & real_array_, value_t step) {
	real_array = & real_array_;
	div = step * step;
}

Hessian::Hessian (RealArray const & real_array_, value_t step) {
	init (real_array_, step);
}



bool Hessian::has_derivative (bool dim, ArrayPoint const & p) const {
	assert(real_array->has_point(p));
	if (dim == 0) {
		return 1 <= p.x && p.x < real_array->x_size() - 1 && 1 <= p.y && p.y < real_array->y_size() - 1 &&
			real_array->has_point({coord_t(p.x - 1), coord_t(p.y + 1)}) &&
			real_array->has_point({coord_t(p.x + 1), coord_t(p.y - 1)});
	} else {
		return 1 <= p.y && p.y < real_array->y_size() - 1 &&
			real_array->has_point({p.x, coord_t(p.y - 1)}) &&
			real_array->has_point({p.x, coord_t(p.y + 1)});
	}
}

bool Hessian::has_derivative1 (bool dim, ArrayPoint const & p) const {
	assert(real_array->has_point(p));
	if (dim == 0) {
		return 1 <= p.x && p.x < real_array->x_size() - 1 &&
			   real_array->has_point({coord_t(p.x - 1), coord_t(p.y)}) &&
			   real_array->has_point({coord_t(p.x + 1), coord_t(p.y)});
	} else {
		return 1 <= p.y && p.y < real_array->y_size() - 1 &&
			   real_array->has_point({p.x, coord_t(p.y - 1)}) &&
			   real_array->has_point({p.x, coord_t(p.y + 1)});
	}
}

value_t Hessian::derivative (bool dim, ArrayPoint const & p) const {
	assert(has_derivative(dim, p));
	if (dim == 0) {
		return (
			real_array->value({coord_t(p.x - 1), coord_t(p.y + 1)}) +
			real_array->value({coord_t(p.x + 1), coord_t(p.y - 1)}) -
			2 * real_array->value(p)
		) / div;
	} else {
		return (
			real_array->value({p.x, coord_t(p.y - 1)}) + real_array->value({p.x, coord_t(p.y + 1)}) -
			2 * real_array->value(p)
		) / div;
	}
}

value_t Hessian::derivative1 (bool dim, ArrayPoint const & p) const {
	assert(has_derivative1(dim, p));
	if (dim == 0) {
		return (
			real_array->value({coord_t(p.x - 1), coord_t(p.y)}) +
			real_array->value({coord_t(p.x + 1), coord_t(p.y)}) -
			2 * real_array->value(p)
		) / div;
	} else {
		return (
			real_array->value({p.x, coord_t(p.y - 1)}) + real_array->value({p.x, coord_t(p.y + 1)}) -
			2 * real_array->value(p)
		) / div;
	}
}
	
} // namespace biconcave