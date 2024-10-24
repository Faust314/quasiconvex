#pragma once
#include "linear_abstract.hpp"

namespace math::geom::plan::detail {

template <Coord_t coord_t>
class DiagonalT_int : public LinearT<coord_t> {
public:
	DiagonalT_int () = default;
	void reset ();
	void reset (ScalarT<coord_t> const & scalar);
	void reset (DiagonalT<coord_t> const & diagonal);
	void reset (HomothetyT<coord_t> const & homothety);
	void reset (LinearT<coord_t> const & linear);
	void reset (coord_t a_, coord_t b_);
	template <LinearT_c<coord_t> LinearTransform>
	explicit DiagonalT_int (LinearTransform const & linear) : LinearAT<coord_t>(linear) {};
	explicit DiagonalT_int (coord_t a_, coord_t b_);
	
	linear_t type () const;
	
	bool is_scalar () const;
	bool is_diagonal () const;
	bool is_homothety () const;
	
	coord_t a () const;
	coord_t b () const;
	
	coord_t det () const;
	int8_t orientation () const;
	
	DiagonalT_int operator* (DiagonalT_int const & linear) const;
	
	DiagonalT_int<Real_t<coord_t>> get_inverse () const;
	
	void apply (PointT<coord_t> & point);
	PointT<coord_t> operator() (PointT<coord_t> const & point) const;

protected:
	coord_t _a = 1;
	coord_t _b = 1;
};



template <Coord_t coord_t>
class DiagonalT_float : public DiagonalT_int<coord_t> {
public:
	DiagonalT_float () = default;
	void reset (OrthogonalT<coord_t> const & orthogonal);
	template <LinearT_c<coord_t> LinearTransform>
	explicit DiagonalT_float (LinearTransform const & linear) : DiagonalT_int<coord_t>(linear) {};
	explicit DiagonalT_float (coord_t a_, coord_t b_) : DiagonalT_float(a_, b_) {};
	
	bool is_orthogonal () const;
	void inverse () const;
};
	
} // namespace math::geom::plan::detail
