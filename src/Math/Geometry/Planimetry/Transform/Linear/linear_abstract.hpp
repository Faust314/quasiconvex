#pragma once

#include "../../../types.hpp"
#include "../../point.hpp"

#include <cstdint>

namespace math::geom::plan {

enum class linear_t {scalar, diagonal, orthogonal, homothety, linear};

namespace detail {

template <Coord_t coord_t>
class ScalarT_int;
template <Coord_t coord_t>
class ScalarT_float;

template <Coord_t coord_t>
class DiagonalT_int;
template <Coord_t coord_t>
class DiagonalT_float;

template <Coord_t coord_t>
class HomothetyT_int;
template <Coord_t coord_t>
class HomothetyT_float;

template <Coord_t coord_t>
class LinearT_int;
template <Coord_t coord_t>
class LinearT_float;

} // namespace detail

template <Coord_t coord_t>
using ScalarT = std::conditional<
	Int_t<coord_t>, detail::ScalarT_int<coord_t>, detail::ScalarT_float<coord_t>
>;

template <Coord_t coord_t>
using DiagonalT = std::conditional<
	Int_t<coord_t>, detail::DiagonalT_int<coord_t>, detail::DiagonalT_float<coord_t>
>;

template <Coord_t coord_t>
class OrthogonalT;

template <Coord_t coord_t>
using HomothetyT = std::conditional<
	Int_t<coord_t>, detail::HomothetyT_int<coord_t>, detail::HomothetyT_float<coord_t>
>;

template <Coord_t coord_t>
using LinearT = std::conditional<
	Int_t<coord_t>, detail::LinearT_int<coord_t>, detail::LinearT_float<coord_t>
>;

template <typename coord_t, class LinearTransform>
concept LinearT_c =
	std::is_same_v<LinearTransform, ScalarT<coord_t>> ||
	std::is_same_v<LinearTransform, DiagonalT<coord_t>> ||
	std::is_same_v<LinearTransform, OrthogonalT<coord_t>> ||
	std::is_same_v<LinearTransform, HomothetyT<coord_t>> ||
	std::is_same_v<LinearTransform, LinearT<coord_t>>;



namespace detail {

template <Coord_t coord_t>
class LinearAT_int {
public:
	LinearAT_int () = default;
	virtual void reset () = 0;
	virtual void reset (ScalarT<coord_t> const & scalar) = 0;
	virtual void reset (DiagonalT<coord_t> const & diagonal) = 0;
	virtual void reset (HomothetyT<coord_t> const & homothety) = 0;
	virtual void reset (LinearT<coord_t> const & linear) = 0;
	template <LinearT_c<coord_t> LinearTransform>
	requires Int_t<coord_t>
	explicit LinearAT_int(LinearTransform const & linear);
	
	virtual linear_t type () const = 0;
	
	virtual bool is_scalar () const = 0;
	virtual bool is_diagonal () const = 0;
	virtual bool is_homothety () const = 0;
	
	ScalarT<coord_t> get_scalar ();
	DiagonalT<coord_t> get_diagonal ();
	OrthogonalT<coord_t> get_orthogonal ();
	HomothetyT<coord_t> get_homothety ();
	LinearT<coord_t> get_linear ();
	
	virtual coord_t det () const = 0;
	virtual int8_t orientation () const = 0;
	bool is_degenerate () const;
	bool is_positive_oriented () const;
	bool is_negative_oriented () const;
	
	virtual LinearAT_int operator* (LinearAT_int const & linear) const = 0;
	
	virtual LinearAT_int<Real_t<coord_t>> get_inverse () const = 0;
	
	virtual void apply (PointT<coord_t> & point) = 0;
	virtual PointT<coord_t> operator() (PointT<coord_t> const & point) const = 0;
};



template <Coord_t coord_t>
class LinearAT_float : public LinearAT_int<coord_t> {
	virtual void reset (OrthogonalT<coord_t> const & orthogonal) = 0;
	LinearAT_float () = default;
	template <LinearT_c<coord_t> LinearTransform>
	explicit LinearAT_float(LinearTransform const & linear);
	virtual bool is_orthogonal () const = 0;
	virtual void inverse () const = 0;
};

} // namespace detail



template <Coord_t coord_t>
using LinearAT = std::conditional<
    Int_t<coord_t>, detail::LinearAT_int<coord_t>, detail::LinearAT_float<coord_t>
>;
	
} // namespace math::geom::plan