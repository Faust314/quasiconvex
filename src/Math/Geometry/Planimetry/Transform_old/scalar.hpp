#pragma once

#include "../../types.hpp"
#include "../point.hpp"

namespace math::geom::plan {

template <Coord_t>
class Rectangular;

template <Coord_t>
class Orthogonal;

template <Coord_t>
class Affine;

template <Coord_t coord_t>
class ScalarT {
public:
	using real_t = Real_t<coord_t>;
	constexpr static bool is_float = Float_t<coord_t>;

public:
	ScalarT () = default;
	ScalarT (coord_t s_, coord_t x0_, coord_t y0_);
	ScalarT (coord_t s_, PointT<coord_t> const & shift);
	ScalarT (coord_t x0_, coord_t y0_);
	explicit ScalarT (PointT<coord_t> const & shift);
	
	coord_t a () const;
	coord_t b () const;
	coord_t x0 () const;
	coord_t y0 () const;
	
	coord_t det () const;
	
	RectangularT operator* (RectangularT<coord_t> const & rect);
	
	RectangularT<real_t> get_inverse () const;
	void inverse () const requires is_float;
	
	void apply (PointT<coord_t> & point) const;
	PointT<coord_t> operator() (PointT<coord_t> const & point) const;

private:
	coord_t _s;
	coord_t _x0;
	coord_t _y0;
};

} // namespace math::geom::plan