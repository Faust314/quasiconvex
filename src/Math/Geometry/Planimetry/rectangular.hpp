#pragma once

#include "../parameters.hpp"
#include "point.hpp"

#include <cstdint>

namespace math::geom::plan {

template <Coord_t coord_t>
class RectangularT {
public:
	using real_t = Real_t<coord_t>;
	constexpr static bool is_float = Float_t<coord_t>;
	
public:
	RectangularT () = default;
	RectangularT (coord_t a_, coord_t b_, coord_t x0_, coord_t y0_);
	RectangularT (coord_t a_, coord_t b_, PointT<coord_t> const & shift);
	RectangularT (coord_t x0_, coord_t y0_);
	RectangularT (PointT<coord_t> const & shift);
	
	coord_t a () const;
	coord_t b () const;
	coord_t x0 () const;
	coord_t y0 () const;
	
	RectangularT operator* (RectangularT<coord_t> const & rect);
	
	RectangularT<real_t> get_inverse () const;
	void inverse () const requires is_float;
	
	PointT<coord_t> operator() (PointT<coord_t> const & point);
	
private:
	coord_t _a;
	coord_t _b;
	coord_t _x0;
	coord_t _y0;
};

template <Float_t coord_t>
RectangularT<coord_t> rectangular_translate (
	PointT<coord_t> const & p1, PointT<coord_t> const & p2,
	PointT<coord_t> const & q1, PointT<coord_t> const & q2
);

template <Float_t coord_t>
RectangularT<coord_t> proportional_translate (
	PointT<coord_t> const & p1, PointT<coord_t> const & p2,
	PointT<coord_t> const & q1, PointT<coord_t> const & q2,
	int8_t pos_x = 0, int8_t pos_y = 0
);

template <Coord_t coord_t>
RectangularT<coord_t> rectangular_scale (coord_t scale);
template <Coord_t coord_t>
RectangularT<coord_t> rectangular_scale (coord_t scale_x, coord_t scale_y);
template <Coord_t coord_t>
RectangularT<coord_t> rectangular_scale (coord_t scale, PointT<coord_t> center);
template <Coord_t coord_t>
RectangularT<coord_t> rectangular_scale (coord_t scale_x, coord_t scale_y, PointT<coord_t> center);

} // namespace math::geom::plan