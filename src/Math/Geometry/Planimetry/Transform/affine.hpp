#pragma once

#include "Linear/linear_abstract.hpp"

namespace math::geom::plan {

template <typename coord_t, template<typename coord_t_> class LinearTransform>
requires LinearT_c<coord_t, LinearTransform<coord_t>>
class Affine {
public:
	Affine () = default;
	void reset (PointT<coord_t> const & shift);
	template <typename... Args>
	void reset (Args... args);
	template <typename... Args>
	void reset (PointT<coord_t> const & shift, Args... args);
	explicit Affine (PointT<coord_t> const & shift);
	template <typename... Args>
	Affine (Args... args);
	template <typename... Args>
	explicit Affine (PointT<coord_t> const & shift_, Args... args);
	
	PointT<coord_t> const & shift () const;
	LinearTransform<coord_t> const & linear () const;
	
	
	
private:
	PointT<coord_t> _shift;
	LinearTransform<coord_t> _linear;
};

} // namespace math::geom::plan