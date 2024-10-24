#pragma once

#include "../../types.hpp"
#include "../Point.hpp"

#include <cstdint>
#include <cmath>

namespace math::geom::plan {

template <Coord_t coord_t>
class AffineT {
public:
	using real_t = Real_t<coord_t>;
	constexpr static bool is_float = Float_t<coord_t>;
	
public:
	AffineT () = default;
	AffineT (coord_t a_, coord_t b_, coord_t c_, coord_t d_, coord_t x0_, coord_t y0_);
	AffineT (coord_t a_, coord_t b_, coord_t c_, coord_t d_, PointT<coord_t> const & shift);
	AffineT (coord_t x0_, coord_t y0_);
	explicit AffineT (PointT<coord_t> const & shift);
	
	coord_t a () const;
	coord_t b () const;
	coord_t c () const;
	coord_t d () const;
	coord_t x0 () const;
	coord_t y0 () const;
	
	coord_t det () const;
	bool is_orthogonal () const;
	
	AffineT operator* (AffineT<coord_t> const & affine);
	
	AffineT<real_t> get_inverse () const;
	void inverse () const requires is_float;
	
	void apply (PointT<coord_t> & point) const;
	PointT<coord_t> operator() (PointT<coord_t> const & point) const;
	
private:
	coord_t _a;
	coord_t _b;
	coord_t _c;
	coord_t _d;
	coord_t _x0;
	coord_t _y0;
};


template <Coord_t coord_t>
AffineT<coord_t> affine_scale (coord_t scale);
template <Coord_t coord_t>
AffineT<coord_t> affine_scale (coord_t scale, PointT<coord_t> center);

template <Coord_t coord_t>
AffineT<coord_t> affine_rotate (coord_t rotation)
requires Float_t<coord_t>;
template <Coord_t coord_t>
AffineT<coord_t> affine_symmetry (coord_t rotation)
requires Float_t<coord_t>;
	
} // namespace math::geom::plan