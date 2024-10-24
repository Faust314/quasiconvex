#pragma once
#include "linear_abstract.hpp"

#include <tuple>

namespace math::geom::plan::detail {

template <Coord_t coord_t>
class LinearT_int : public LinearT<coord_t> {
public:
	LinearT_int () = default;
	void reset ();
	void reset (ScalarT<coord_t> const & scalar);
	void reset (DiagonalT<coord_t> const & diagonal);
	void reset (HomothetyT<coord_t> const & homothety);
	void reset (LinearT<coord_t> const & linear);
	void reset (coord_t a_, coord_t b_, coord_t c_, coord_t d_);
	template <LinearT_c<coord_t> LinearTransform>
	explicit LinearT_int (LinearTransform const & linear) : LinearAT<coord_t>(linear) {};
	LinearT_int (coord_t a_, coord_t b_, coord_t c_, coord_t d_);
	
	linear_t type () const;
	
	bool is_scalar () const;
	bool is_diagonal () const;
	bool is_homothety () const;
	
	coord_t det () const;
	int8_t orientation () const;
	
	LinearT_int operator* (LinearT_int const & linear) const;
	
	LinearT_int<Real_t<coord_t>> get_inverse () const;
	
	void apply (PointT<coord_t> & point);
	PointT<coord_t> operator() (PointT<coord_t> const & point) const;
	
	std::tuple<OrthogonalT<coord_t>, DiagonalT<coord_t>, OrthogonalT<coord_t>> get_svd () const;
	
protected:
	coord_t _a;
	coord_t _b;
	coord_t _c;
	coord_t _d;
};



template <Coord_t coord_t>
class LinearT_float : public LinearT_int<coord_t> {
public:
	LinearT_float () = default;
	void reset (OrthogonalT<coord_t> const & orthogonal);
	template <LinearT_c<coord_t> LinearTransform>
	explicit LinearT_float (LinearTransform const & linear) : LinearT_int<coord_t>(linear) {};
	LinearT_float (coord_t a_, coord_t b_, coord_t c_, coord_t d_) : LinearT_int<coord_t>(
		a_, b_, c_, d_
	) {};
	
	bool is_orthogonal () const;
	void inverse () const;
};
	
} // namespace math::geom::plan::detail
