#pragma once

#include <vector>

#include "object.hpp"

namespace graphics::twodim {

class Path : public Object {
public:
	enum class path_kind_t {common, polygon, polyline};
	enum class seg_kind_t {move, close, line, bezier, bezier_short, quadratic, quadratic_short, arc, circ_arc};
	
public:
	Path () = default;
	explicit Path (Point const & p);
	explicit Path (path_kind_t path_kind_);
	explicit Path (path_kind_t path_kind_, Point const & p);
	
	path_kind_t path_kind () const;
	std::vector<seg_kind_t> const & seg_kinds () const;
	std::vector<Point> const & key_points () const;
	std::vector<coord_t> const & extra_args () const;
	
	void read (aux::Json const & json) final;
	void write (aux::Json & json) const final;
	
	void print_svg (svg::Print const & print, Paint const & paint, object_id_t object_id) const final;
	
	void set_path_kind (path_kind_t path_kind_);
	
	void move (Point const & p);
	void close ();
	
	void line_fast (Point const & p);
	void line (Point const & p);
	
	void bezier (Point const & p1, Point const & p2, Point const & p);
	void bezier_short (Point const & p2, Point const & p);
	void quadratic (Point const & p1, Point const & p);
	void quadratic_short (Point const & p);
	
	void arc (
		coord_t rx, coord_t ry, coord_t rotation, bool is_large_arc, bool is_counterclockwise, Point const & p
	);
	void circ_arc (coord_t r, bool is_counterclockwise, Point const & p);
	
	void add_circ (coord_t r, Point const & p);
	
	Path operator+ (Path const & path);
	Path & operator+= (Path const & path);
	
	bool supports_react_transform () final {return true;};
	bool supports_affine_transform () final {return true;};
	bool supports_common_transform () final {return true;};
	
	void rect_transform (Rectangular const & rectangular) final;
	void affine_transform (Affine const & affine) final;
	void common_transform (std::function<Point (Point const &)> const & transform) final;
	
private:
	path_kind_t _path_kind = path_kind_t::common;
	std::vector<seg_kind_t> _seg_kinds;
	std::vector<Point> _key_points;
	std::vector<coord_t> _extra_args;
	
	template <class Transform>
	void apply_transform_to_point (Transform const & transform, object_id_t arg_id);
	template <Transform_t Transform>
	void apply_orthogonal_to_circ_arc (Transform const & transform, object_id_t arg_id);
	template <Transform_t Transform>
	void apply_affine_to_arc (Transform const & transform, object_id_t arg_id);
	template <class Transform, bool is_common>
	void _transform (Transform const & transform);
};

} // namespace graphics::twodim