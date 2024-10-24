#pragma once
#include "linear_abstract.hpp"

#include <utility>

namespace math::geom::plan::detail {

template <Coord_t coord_t>
class HomothetyT_int : public LinearT<coord_t> {
public:
	HomothetyT_int () = default;
	void reset ();
	void reset (ScalarT<coord_t> const & scalar);
	void reset (DiagonalT<coord_t> const & diagonal);
	void reset (HomothetyT<coord_t> const & homothety);
	void reset (LinearT<coord_t> const & linear);
	void reset (coord_t a_, coord_t b_, bool reflected_ = false);
	template <LinearT_c<coord_t> LinearTransform>
	explicit HomothetyT_int (LinearTransform const & linear) : LinearAT<coord_t>(linear) {};
	HomothetyT_int (coord_t a_, coord_t b_, bool is_reflected_ = false);
	
	linear_t type () const;
	
	bool is_scalar () const;
	bool is_diagonal () const;
	bool is_homothety () const;
	
	coord_t a () const;
	coord_t b () const;
	bool is_reflected () const;
	
	coord_t det () const;
	int8_t orientation () const;
	
	HomothetyT_int operator* (HomothetyT_int const & homothety) const;
	
	HomothetyT_int<Real_t<coord_t>> get_inverse () const;
	
	void apply (PointT<coord_t> & point);
	PointT<coord_t> operator() (PointT<coord_t> const & point) const;
	
	std::pair<ScalarT<Real_t<coord_t>>, OrthogonalT<Real_t<coord_t>>> get_decomposition () const;

protected:
	coord_t _a = 1;
	coord_t _b = 0;
	bool _is_reflected = false;
};



template <Coord_t coord_t>
class HomothetyT_float : public HomothetyT_int<coord_t> {
public:
	HomothetyT_float () = default;
	void reset (OrthogonalT<coord_t> const & orthogonal);
	template <LinearT_c<coord_t> LinearTransform>
	explicit HomothetyT_float (LinearTransform const & linear) : HomothetyT_int<coord_t>(linear) {};
	HomothetyT_float (coord_t a_, coord_t b_, bool is_reflected_ = false) : HomothetyT_float(
		a_, b_, is_reflected_
	) {};
	
	bool is_orthogonal () const;
	void inverse () const;
};
	
} // namespace math::geom::plan::detail
