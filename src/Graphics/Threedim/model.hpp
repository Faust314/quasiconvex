#pragma once

#include "types.hpp"
#include "../Color/color.hpp"

#include <vector>

namespace graphics::threedim {

class Model {
public:
	Model () = default;
	
	std::vector<color::RGB> & colors ();
	std::vector<Point> & points ();
	std::vector<std::vector<object_id_t>> & faces ();
	std::vector<object_id_t> & face_colors ();
	
	void add_color (color::RGB const & rgb);
	void add_point (Point const & point);
	
	void add_face (std::vector<object_id_t> const & point_ids, object_id_t color_id);
	void add_face (std::vector<object_id_t> const & point_ids);
	void add_face (std::vector<Point> const & points, object_id_t color_id);
	void add_face (std::vector<Point> const & points);
	void add_face (object_id_t color_id);
	void add_face ();
	
	void add_face_point (object_id_t point_id, object_id_t face_id);
	void add_face_point (object_id_t point_id);
	void add_face_points (std::vector<object_id_t> const & point_ids, object_id_t face_id);
	void add_face_points (std::vector<object_id_t> const & point_ids);
	void set_face_color (object_id_t color_id, object_id_t face_id);
	void set_face_color (object_id_t color_id);
	
	void arrange_colors (graphics::color::arg_t step = 1);
	
	void output_to_obj (std::string const & dir, std::string const & name);
	
private:
	std::vector<color::RGB> _colors;
	std::vector<Point> _points;
	std::vector<std::vector<object_id_t>> _faces;
	std::vector<object_id_t> _face_colors;
};

} // namespace graphics::threedim::obj