#include "model.hpp"

#include "Formats/obj.hpp"

#include <cassert>
#include <unordered_map>

namespace graphics::threedim {

std::vector<color::RGB> & Model::colors () {
	return _colors;
}

std::vector<Point> & Model::points () {
	return _points;
}

std::vector<std::vector<object_id_t>> & Model::faces () {
	return _faces;
}

std::vector<object_id_t> & Model::face_colors () {
	return _face_colors;
}



void Model::add_color (color::RGB const & rgb) {
	_colors.push_back(rgb);
}

void Model::add_point (Point const & point) {
	_points.push_back(point);
}



void Model::add_face (std::vector<object_id_t> const & point_ids, object_id_t color_id) {
	_faces.push_back(point_ids);
	_face_colors.push_back(color_id);
}

void Model::add_face (std::vector<object_id_t> const & point_ids) {
	_faces.push_back(point_ids);
	_face_colors.push_back(_colors.size() - 1);
}

void Model::add_face (std::vector<Point> const & points, object_id_t color_id) {
	_faces.emplace_back();
	for (Point const & point : points) {
		_faces.back().push_back(_points.size());
		_points.push_back(point);
	}
	_face_colors.push_back(color_id);
}

void Model::add_face (std::vector<Point> const & points) {
	_faces.emplace_back();
	for (Point const & point : points) {
		_faces.back().push_back(_points.size());
		_points.push_back(point);
	}
	_face_colors.push_back(_colors.size() - 1);
}

void Model::add_face (object_id_t color_id) {
	_faces.emplace_back();
	_face_colors.push_back(color_id);
}

void Model::add_face () {
	_faces.emplace_back();
	_face_colors.push_back(_colors.size() - 1);
}

void Model::add_face_point (object_id_t point_id, object_id_t face_id) {
	_faces[face_id].push_back(point_id);
}

void Model::add_face_point (object_id_t point_id) {
	_faces.back().push_back(point_id);
}

void Model::add_face_points (std::vector<object_id_t> const & point_ids, object_id_t face_id) {
	for (object_id_t point_id : point_ids) {
		_faces[face_id].push_back(point_id);	
	}
}

void Model::add_face_points (std::vector<object_id_t> const & point_ids) {
	for (object_id_t point_id : point_ids) {
		_faces.back().push_back(point_id);
	}
}

void Model::set_face_color (object_id_t color_id, object_id_t face_id) {
	_face_colors[face_id] = color_id;
}

void Model::set_face_color (object_id_t color_id) {
	_face_colors.back() = color_id;
}



void Model::arrange_colors (graphics::color::arg_t step) {
	assert (1 <= step && step <= 255);
	if (step > 1);
	for (auto & color : _colors) {
		color.compress(step);
	}
	std::unordered_map<uint32_t, object_id_t> colors_map;
	object_id_t colors_size = 0;
	std::vector<object_id_t> color_ids_map(_colors.size());
	
	std::unordered_map<uint32_t, object_id_t>::iterator it;
	for (object_id_t color_id = 0; color_id < _colors.size(); color_id++) {
		it = colors_map.find(_colors[color_id].hash());
		if (it == colors_map.end()) {
			colors_map[_colors[color_id].hash()] = colors_size;
			if (color_id > colors_size) {
				_colors[colors_size] = _colors[color_id];
			}
			color_ids_map[color_id] = colors_size;
			colors_size++;
		} else {
			color_ids_map[color_id] = it->second;
		}
	}
	_colors.resize(colors_size);
	for (object_id_t & color_id : _face_colors) {
		color_id = color_ids_map[color_id];
	}
}



void Model::output_to_obj (std::string const & dir, std::string const & name) {
	std::ofstream mtl (dir + "/" + name + ".mtl");
	std::ofstream obj (dir + "/" + name + ".obj");
	
	obj::Str output(mtl, obj);
	for (object_id_t id = 0; id < _colors.size(); id++) {
		output.new_mtl(_colors[id], id);
	}
	
	output.obj_begin(name);
	for (object_id_t id = 0; id < _points.size(); id++) {
		output.add_vertex(_points[id]);
	}
	
	std::vector<std::vector<object_id_t>> perm_objects (_colors.size());
	for (object_id_t face_id = 0; face_id < _faces.size(); face_id++) {
		perm_objects[_face_colors[face_id]].push_back(face_id);
	}
	
	output.faces_begin();
	for (object_id_t color_id = 0; color_id < perm_objects.size(); color_id++) {
		if (perm_objects[color_id].empty()) {
			continue;
		}
		output.use_mtl(color_id);
		for (object_id_t face_number = 0; face_number < perm_objects[color_id].size(); face_number++) {
			output.add_face(_faces[perm_objects[color_id][face_number]]);
		}
	}
}
	
} // namespace graphics::threedim
