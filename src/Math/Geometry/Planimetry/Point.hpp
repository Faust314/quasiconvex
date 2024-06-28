#pragma once

#include "../parameters.hpp"

namespace math::geom::plan {

template <Coord_t coord_t>
class PointT {
public:
	using real_t = Real_t<coord_t>;
	constexpr static bool is_float = Float_t<coord_t>;
	
public:
	PointT () = default;
	PointT (coord_t a);
	PointT (coord_t x_, coord_t y_);
	template <Coord_t coord_t1>
	PointT (coord_t1 x_, coord_t1 y_);
	
	PointT (PointT const & point) = default;
	template<Coord_t coord_t1>
	PointT (PointT<coord_t1> const & p);
	
	coord_t x;
	coord_t y;
	
	real_t abs () const;
	coord_t abs_sqr () const;
	real_t angle () const;
	bool f_less (PointT p) requires is_float;
	bool f_grt (PointT p) requires is_float;
	bool f_less (coord_t a) requires is_float;
	bool f_grt (coord_t a) requires is_float;
	
	bool operator== (PointT const & p) const;
	bool operator!= (PointT const & p) const;
	bool operator<= (PointT const & p) const;
	bool operator>= (PointT const & p) const;
	bool operator< (PointT const & p) const;
	bool operator> (PointT const & p) const;
	
	PointT operator- () const;
	PointT operator+ (PointT const & p) const;
	PointT operator- (PointT const & p) const;
	PointT operator* (PointT const & p) const;
	PointT<real_t> operator/ (PointT const & p) const requires is_float;
	
	PointT & operator+= (PointT const & p);
	PointT & operator-= (PointT const & p);
	PointT & operator*= (PointT const & p);
	PointT & operator/= (PointT const & p) requires is_float;
	PointT & operator*= (coord_t a);
	PointT & operator/= (coord_t a);
	
	void set_coords (coord_t x_, coord_t y_);
	void set_polar_coords (coord_t radius, coord_t angle) requires is_float;
	void set_polar_coords (coord_t angle) requires is_float;
	void norm () requires is_float;
	void reflect ();
	void rotate (coord_t angle) requires is_float;
	
private:
	coord_t _x;
	coord_t _y;
};



template <Float_t coord_t>
PointT<coord_t> exp (coord_t radius, coord_t angle);
template <Float_t coord_t>
PointT<coord_t> exp (coord_t angle);

template <Float_t coord_t>
bool are_equal (PointT<coord_t> const & p1, PointT<coord_t> const & p2, coord_t eps);

template <Float_t coord_t>
bool are_equal (PointT<coord_t> const & p1, PointT<coord_t> const & p2, coord_t eps);

template <Coord_t coord_t>
coord_t dot_prod (PointT<coord_t> const & p1, PointT<coord_t> const & p2);
template <Coord_t coord_t>
coord_t vec_prod (PointT<coord_t> const & p1, PointT<coord_t> const & p2);

template <Coord_t coord_t>
bool operator== (PointT<coord_t> const & p, coord_t a);
template <Coord_t coord_t>
bool operator!= (PointT<coord_t> const & p, coord_t a);
template <Coord_t coord_t>
bool operator<= (PointT<coord_t> const & p, coord_t a);
template <Coord_t coord_t>
bool operator>= (PointT<coord_t> const & p, coord_t a);
template <Coord_t coord_t>
bool operator< (PointT<coord_t> const & p, coord_t a);
template <Coord_t coord_t>
bool operator> (PointT<coord_t> const & p, coord_t a);

template <typename coord_t>
bool operator== (coord_t a, PointT<coord_t> const & p);
template <typename coord_t>
bool operator!= (coord_t a, PointT<coord_t> const & p);
template <typename coord_t>
bool operator<= (coord_t a, PointT<coord_t> const & p);
template <typename coord_t>
bool operator>= (coord_t a, PointT<coord_t> const & p);
template <typename coord_t>
bool operator< (coord_t a, PointT<coord_t> const & p);
template <typename coord_t>
bool operator> (coord_t a, PointT<coord_t> const & p);

template <typename coord_t>
PointT<coord_t> operator* (PointT<coord_t> const & point, coord_t a);
template <typename coord_t>
PointT<coord_t> operator* (coord_t a, PointT<coord_t> const & point);
template <typename coord_t>
PointT<coord_t> operator/ (PointT<coord_t> const & point, coord_t a);

} // namespace math::geom::plan