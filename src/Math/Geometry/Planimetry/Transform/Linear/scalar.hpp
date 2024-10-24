#pragma once
#include "linear_abstract.hpp"

namespace math::geom::plan::detail {

template <Coord_t coord_t>
class ScalarT_int : public LinearT<coord_t> {
public:
	ScalarT_int () = default;
	void reset ();
	void reset (ScalarT<coord_t> const & scalar);
	void reset (DiagonalT<coord_t> const & diagonal);
	void reset (HomothetyT<coord_t> const & homothety);
	void reset (LinearT<coord_t> const & linear);
	void reset (coord_t scale_);
	template <LinearT_c<coord_t> LinearTransform>
	explicit ScalarT_int (LinearTransform const & linear) : LinearAT<coord_t>(linear) {};
	explicit ScalarT_int (coord_t scale_);
	
	linear_t type () const;
	
	bool is_scalar () const;
	bool is_diagonal () const;
	bool is_homothety () const;
	
	coord_t scale () const;
	
	coord_t det () const;
	int8_t orientation () const;
	
	ScalarT_int operator* (ScalarT_int const & linear) const;
	 
	ScalarT_int<Real_t<coord_t>> get_inverse () const;
	
	void apply (PointT<coord_t> & point);
	PointT<coord_t> operator() (PointT<coord_t> const & point) const;
	
protected:
	coord_t _scale = 1;
};



template <Coord_t coord_t>
class ScalarT_float : public ScalarT_int<coord_t> {
public:
	ScalarT_float () = default;
	void reset (OrthogonalT<coord_t> const & orthogonal);
	template <LinearT_c<coord_t> LinearTransform>
	explicit ScalarT_float (LinearTransform const & linear) : ScalarT_int<coord_t>(linear) {};
	explicit ScalarT_float (coord_t scale_) : ScalarT_int<coord_t>(scale_) {};
	
	bool is_orthogonal () const;
	void inverse () const;
};
	
} // namespace math::geom::plan::detail


