#pragma once
#include "linear_abstract.hpp"

namespace math::geom::plan {

template <Coord_t coord_t>
class OrthogonalT : public LinearT<coord_t> {
public:
	OrthogonalT () = default;
	void reset ();
	void reset (ScalarT<coord_t> const & scalar);
	void reset (DiagonalT<coord_t> const & diagonal);
	void reset (OrthogonalT<coord_t> const & orthogonal);
	void reset (HomothetyT<coord_t> const & homothety);
	void reset (LinearT<coord_t> const & linear);
	void reset (coord_t angle_, bool is_reflected_ = false);
	template <LinearT_c<coord_t> LinearTransform>
	explicit OrthogonalT (LinearTransform const & linear) : LinearAT<coord_t>(linear) {};
	explicit OrthogonalT (coord_t angle_, bool is_reflected_ = false);
	
	linear_t type () const;
	
	bool is_scalar () const;
	bool is_diagonal () const;
	bool is_orthogonal () const;
	bool is_homothety () const;
	
	coord_t angle () const;
	coord_t is_reflected () const;
	
	coord_t det () const;
	int8_t orientation () const;
	
	OrthogonalT operator* (OrthogonalT const & orthogonal) const;
	
	OrthogonalT<Real_t<coord_t>> get_inverse () const;
	void inverse () const;
	
	void apply (PointT<coord_t> & point);
	PointT<coord_t> operator() (PointT<coord_t> const & point) const;
	
	static coord_t get_positive_angle (coord_t angle_);
	static coord_t get_signed_angle (coord_t angle_);

protected:
	coord_t _angle = 0;
	bool _is_reflected = false;
};

} // namespace math::geom::plan
