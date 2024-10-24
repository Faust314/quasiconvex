#pragma once
#include "path.hpp"

namespace graphics::twodim {

template <class Transform>
void Path::apply_transform_to_point (Transform const & transform, object_id_t arg_id) {
	Point p = transform({_extra_args[arg_id], _extra_args[arg_id]});
	_extra_args[arg_id] = p.x;
	_extra_args[arg_id + 1] = p.y;
}

template <Transform_t Transform>
void Path::apply_orthogonal_to_circ_arc (Transform const & transform, object_id_t arg_id) {
	static_assert(requires (Transform t) {std::is_same_v<decltype(t.det()), coord_t>;});
	static_assert(requires (Transform const & t) {std::is_same_v<decltype(t.is_orthogonal), bool>;});
	assert(transform.is_orthogonal());
	coord_t det = transform.det();
	_extra_args[arg_id] = arg_id * std::sqrt(std::abs(det)) * (det > 0 ? 1 : -1);
}

template <Transform_t Transform>
void Path::apply_affine_to_arc (Transform const & transform, object_id_t arg_id) {
	static_assert(requires (Transform t) {std::is_same_v<decltype(t.det()), coord_t>;});
	static_assert(requires (Transform const & t) {std::is_same_v<decltype(t.is_orthogonal), bool>;});
	
	bool is_large_flag = _extra_args[arg_id] > 0;
	bool is_counterclockwise = _extra_args[arg_id + 1] > 0;
	auto [a1, a3] = transform(
		std::abs(_extra_args[arg_id]) * Point(
			std::cos(_extra_args[arg_id + 2]), std::sin(_extra_args[arg_id + 2])
		)
	);
	auto [a2, a4] = transform(
		std::abs(_extra_args[arg_id + 1]) * Point(
			- std::sin(_extra_args[arg_id + 2]), std::cos(_extra_args[arg_id + 2])
		)
	);
	
	if (transform.is_orthogonal()) {
		_extra_args[arg_id] = std::sqrt(a1 * a1 + a2 * a2);
		_extra_args[arg_id + 1] = _extra_args[arg_id];
	} else {
		coord_t A1 = a1 * a1;
		coord_t A2 = a2 * a2;
		coord_t A3 = a3 * a3;
		coord_t A4 = a4 * a4;
		coord_t b2 = a1 * a3 + a2 * a4;
		
		coord_t d = std::sqrt(
			std::pow (A1 - A4, 2) + std::pow(A2 - A3, 2) +
			2 * std::pow(b2, 2) + 2 * std::pow(a1 * a2 + a3 * a4, 2)
		);
		assert(d > math::geom::error);
		coord_t l = (d + A1 + A2 + A3 + A4) / 2;
		_extra_args[arg_id] = std::sqrt(l);
		_extra_args[arg_id + 1] = std::sqrt(l - d);
		coord_t b1 = A1 + A2 - l;
		coord_t b4 = A3 + A4 - l;
		
		if (std::abs(b1) > math::geom::error || std::abs(b2) > math::geom::error) {
			_extra_args[arg_id + 2] = std::atan2(b1, - b2);
		} else {
			assert(std::abs(b3) > math::geom::error || std::abs(b4) > math::geom::error);
			_extra_args[arg_id + 2] = std::atan2(b2, - b4);
		}
	}
	_extra_args[arg_id] *= (is_large_flag ? 1 : -1);
	_extra_args[arg_id + 1] *= (transform.det() > 0 ? 1 : -1) * (is_counterclockwise ? 1 : -1);
}

template <class Transform, bool is_common>
void Path::_transform (Transform const & transform) {
	object_id_t point_id = 0;
	object_id_t arg_id = 0;
	for (seg_kind_t seg_kind : _seg_kinds) {
		if (seg_kind == seg_kind_t::close) {
			continue;
		}
		if constexpr (is_common) {
			_key_points[point_id] = transform(_key_points[point_id]);
		} else {
			transform.apply(_key_points[point_id]);
		}
		point_id++;
		switch (seg_kind) {
			case seg_kind_t::bezier:
				apply_transform_to_point(transform, arg_id);
				apply_transform_to_point(transform, arg_id + 2);
				arg_id += 4;
				break;
			case seg_kind_t::bezier_short:
				apply_transform_to_point(transform, arg_id);
				arg_id += 2;
				break;
			case seg_kind_t::quadratic:
				apply_transform_to_point(transform, arg_id);
				arg_id += 2;
				break;
			case seg_kind_t::arc:
				if constexpr (is_common) {
					assert(false);
				} else {
					apply_affine_to_arc(transform, arg_id);
				}
				break;
			case seg_kind_t::circ_arc:
				if constexpr (is_common) {
					assert(false);
				} else {
					apply_affine_to_arc(transform, arg_id);
					arg_id += 3;
				}
				break;
			default:
				break;
		}
	}
}

} // namespace graphics::twodim