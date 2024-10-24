#include "path.hpp"

namespace graphics::twodim {

Path::Path (Point const & p) {
	_seg_kinds.push_back(seg_kind_t::move);
	_key_points.push_back(p);
}

Path::Path (Path::path_kind_t path_kind_) {
	_path_kind = path_kind_;
}

Path::Path (Path::path_kind_t path_kind_, Point const & p) {
	_path_kind = path_kind_;
	if (_path_kind == path_kind_t::common) {
		_seg_kinds.push_back(seg_kind_t::move);
		_key_points.push_back(p);
	} else {
		_key_points.push_back(p);
	}
}



Path::path_kind_t Path::path_kind () const {
	return _path_kind;
}

std::vector<Path::seg_kind_t> const & Path::seg_kinds () const {
	return _seg_kinds;
}

std::vector<Point> const & Path::key_points () const {
	return _key_points;
}

std::vector<coord_t> const & Path::extra_args () const {
	return _extra_args;
}



void Path::read (aux::Json const & json) {
	Object::read(json);
}

void Path::write (aux::Json & json) const {
	Object::write(json);
}



void Path::print_svg (svg::Print const & print, Paint const & paint, object_id_t object_id) const {
	assert(! _seg_kinds.empty());
	object_id_t point_id = 1;
	object_id_t arg_id = 0;
	
	switch (_path_kind) {
		case path_kind_t::common:
			print.path().begin();
			print.path().path_id(object_id);
			print.file_structs().painting(paint);
			print.path().start(_key_points.front());
			for (object_id_t seg_id = 1; seg_id < _seg_kinds.size(); seg_id++) {
				switch (_seg_kinds[seg_id]) {
					case seg_kind_t::move:
						print.path().Move(_key_points[point_id]);
						point_id++;
						break;
					case seg_kind_t::close:
						print.path().close_path();
						break;
					case seg_kind_t::line:
						print.path().Line(_key_points[point_id]);
						point_id++;
						break;
					case seg_kind_t::bezier:
						print.path().Bezier_curve(
							{_extra_args[arg_id], _extra_args[arg_id + 1]},
							{_extra_args[arg_id + 2], _extra_args[arg_id + 3]},
							_key_points[point_id]
						);
						point_id++;
						arg_id += 2;
						break;
					case seg_kind_t::bezier_short:
						print.path().Bezier_curve_short(
							{_extra_args[arg_id], _extra_args[arg_id + 1]},
							_key_points[point_id]
						);
						point_id++;
						arg_id += 2;
						break;
					case seg_kind_t::quadratic:
						print.path().Quadratic_curve(
							{_extra_args[arg_id], _extra_args[arg_id + 1]},
							_key_points[point_id]
						);
						point_id++;
						arg_id += 2;
						break;
					case seg_kind_t::quadratic_short:
						print.path().Quadratic_curve(
							{_extra_args[arg_id], _extra_args[arg_id + 1]},
							_key_points[point_id]
						);
						point_id++;
						break;
					case seg_kind_t::arc:
						print.path().Arc(
							std::abs(_extra_args[arg_id]), std::abs(_extra_args[arg_id + 1]),
							_extra_args[arg_id + 2], _extra_args[arg_id] > 0, _extra_args[arg_id + 1] > 0,
							_key_points[point_id]
						);
						point_id++;
						arg_id += 3;
						break;
					case seg_kind_t::circ_arc:
						print.path().Arc(
							std::abs(_extra_args[arg_id]), std::abs(_extra_args[arg_id]),
							0, false, _extra_args[arg_id] > 0,
							_key_points[point_id]
						);
						point_id++;
						arg_id++;
						break;
				}
			}
			print.path().stop();
			break;
		case path_kind_t::polygon:
			print.primitives().polygon_begin();
			print.primitives().polygon_id(object_id);
			print.file_structs().painting(paint);
			print.primitives().polygon_start(_key_points.front());
			for (; point_id < _seg_kinds.size(); point_id++) {
				print.primitives().polygon_point(_key_points[point_id]);
			}
			print.primitives().polygon_stop();
			break;
		case path_kind_t::polyline:
			print.primitives().polyline_begin();
			print.primitives().polyline_id(object_id);
			print.file_structs().painting(paint);
			print.primitives().polyline_start(_key_points.front());
			for (; point_id < _seg_kinds.size(); point_id++) {
				print.primitives().polyline_point(_key_points[point_id]);
			}
			print.primitives().polyline_stop();
			break;
	}
	
	print.file_structs().object_end();
}



void Path::set_path_kind (Path::path_kind_t path_kind_) {
	assert(_path_kind != path_kind_t::common || path_kind_ == path_kind_t::common || _key_points.empty());
	if (_key_points.empty()) {
		_path_kind = path_kind_;
	} else if (path_kind_ == path_kind_t::common) {
		if (_path_kind == path_kind_t::common) {
			return;
		}
		_seg_kinds.resize(_key_points.size(), seg_kind_t::line);
		_seg_kinds[0] = seg_kind_t::move;
		if (_path_kind == path_kind_t::polygon) {
			_seg_kinds.push_back(seg_kind_t::close);
		}
		_path_kind = path_kind_;
	} else {
		_path_kind = path_kind_;
	}
}



void Path::move (Point const & p) {
	assert(_path_kind == path_kind_t::common);
	_seg_kinds.push_back(seg_kind_t::move);
	_key_points.push_back(p);
}

void Path::close () {
	assert(_path_kind == path_kind_t::common);
	_seg_kinds.push_back(seg_kind_t::close);
}



void Path::line (Point const & p) {
	assert(_path_kind == path_kind_t::common);
	_seg_kinds.push_back(seg_kind_t::line);
	_key_points.push_back(p);
}

void Path::line_fast (Point const & p) {
	assert(_path_kind != path_kind_t::common);
	_key_points.push_back(p);
}




void Path::bezier (Point const & p1, Point const & p2, Point const & p) {
	assert(_path_kind == path_kind_t::common);
	_seg_kinds.push_back(seg_kind_t::bezier);
	_key_points.push_back(p);
	_extra_args.push_back(p1.x);
	_extra_args.push_back(p1.y);
	_extra_args.push_back(p2.x);
	_extra_args.push_back(p2.y);
}

void Path::bezier_short (Point const & p2, Point const & p) {
	assert(
		! _seg_kinds.empty() &&
		_seg_kinds.back() == seg_kind_t::bezier ||
		_seg_kinds.back() == seg_kind_t::bezier_short
	);
	_seg_kinds.push_back(seg_kind_t::bezier_short);
	_key_points.push_back(p);
	_extra_args.push_back(p2.x);
	_extra_args.push_back(p2.y);
}

void Path::quadratic (Point const & p1, Point const & p) {
	assert(_path_kind == path_kind_t::common);
	_seg_kinds.push_back(seg_kind_t::quadratic);
	_key_points.push_back(p);
	_extra_args.push_back(p1.x);
	_extra_args.push_back(p1.y);
}

void Path::quadratic_short (Point const & p) {
	assert(
		! _seg_kinds.empty() &&
		_seg_kinds.back() == seg_kind_t::quadratic ||
		_seg_kinds.back() == seg_kind_t::quadratic_short
	);
	_seg_kinds.push_back(seg_kind_t::quadratic_short);
	_key_points.push_back(p);
}



void Path::arc (
	coord_t rx, coord_t ry, coord_t rotation, bool is_large_arc, bool is_counterclockwise, Point const & p
) {
	assert(_path_kind == path_kind_t::common);
	_seg_kinds.push_back(seg_kind_t::arc);
	_key_points.push_back(p);
	_extra_args.push_back(is_large_arc ? rx : -rx);
	_extra_args.push_back(is_counterclockwise ? ry : -ry);
	_extra_args.push_back(rotation);
	
}

void Path::circ_arc (coord_t r, bool is_counterclockwise, Point const & p) {
	assert(_path_kind == path_kind_t::common);
	_seg_kinds.push_back(seg_kind_t::circ_arc);
	_key_points.push_back(p);
	_extra_args.push_back(is_counterclockwise ? r : -r );
}



void Path::add_circ (coord_t r, Point const & p) {
	assert(_path_kind == path_kind_t::common);
	_seg_kinds.push_back(seg_kind_t::move);
	_key_points.push_back(p + Point(r, 0));
	
	_seg_kinds.push_back(seg_kind_t::circ_arc);
	_key_points.push_back(p + Point(-r, 0));
	_extra_args.push_back(r);
	
	_seg_kinds.push_back(seg_kind_t::circ_arc);
	_key_points.push_back(p + Point(r, 0));
	_extra_args.push_back(r);
	
	_seg_kinds.push_back(seg_kind_t::close);
}



Path Path::operator+ (Path const & path2) {
	assert(_path_kind == path_kind_t::common && path._path_kind == path_kind_t::common);
	Path path = * this;
	path._seg_kinds.insert(path._seg_kinds.end(), path2._seg_kinds.begin(), path2._seg_kinds.end());
	path._key_points.insert(path._key_points.end(), path2._key_points.begin(), path2._key_points.end());
	path._extra_args.insert(path._extra_args.end(), path2._extra_args.begin(), path2._extra_args.end());
}

Path & Path::operator+= (Path const & path2) {
	assert(_path_kind == path_kind_t::common && path._path_kind == path_kind_t::common);
	_seg_kinds.insert(_seg_kinds.end(), path2._seg_kinds.begin(), path2._seg_kinds.end());
	_key_points.insert(_key_points.end(), path2._key_points.begin(), path2._key_points.end());
	_extra_args.insert(_extra_args.end(), path2._extra_args.begin(), path2._extra_args.end());
	
	return * this;
}



void Path::rect_transform (Rectangular const & rectangular) {
	_transform<Rectangular, false>(rectangular);
}

void Path::affine_transform (Affine const & affine) {
	_transform<Affine, false>(affine);
}

void Path::common_transform (std::function<Point (Point const &)> const & transform) {
	_transform<std::function<Point (Point const &)>, true>(transform);
}
	
} // namespace graphics::twodim
