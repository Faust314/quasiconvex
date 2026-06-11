#include "obj.hpp"

#include "../../../Utils/Basic/format_utils.tpp"

#include <cassert>

namespace graphics::threedim::obj {

void Str::init (std::ofstream & mtl_, std::ofstream & obj_) {
	mtl = & mtl_;
	obj = & obj_;
	aux::format::set_precision(* obj, precision);
}

Str::Str (std::ofstream & mtl_, std::ofstream & obj_) :
	mtl (& mtl_),
	obj (& obj_)
{
	aux::format::set_precision(* obj, precision);
}



void Str::change_direct_permutation (uint8_t x_to, uint8_t y_to, uint8_t z_to) {
	direct[0] = x_to;
	direct[1] = y_to;
	direct[2] = z_to;
	repair_permutation(direct, reverse);
}

void Str::change_reverse_permutation (uint8_t to_x, uint8_t to_y, uint8_t to_z) {
	reverse[0] = to_x;
	reverse[1] = to_y;
	reverse[2] = to_z;
	repair_permutation(reverse, direct);
}



void Str::set_precision (aux::precision_t precision_) {
	precision = precision_;
	if (obj != nullptr) {
		aux::format::set_precision(* obj, precision);
	}
}

void Str::new_mtl (color::RGB const & rgb, std::string mtl_name) {
	* mtl << "\n";
	* mtl << "newmtl " << mtl_name << "\n";
	* mtl << "Ka " << double(rgb.r) / 255 << " " << double(rgb.g) / 255 << " " << double(rgb.b) / 255 << "\n";
	* mtl << "Kd " << double(rgb.r) / 255 << " " << double(rgb.g) / 255 << " " << double(rgb.b) / 255 << "\n";
	* mtl << "Ks 0 0 0\n";
	* mtl << "Ns 0\n";
	* mtl << "d 1";
}

void Str::new_mtl (color::RGB const & rgb, object_id_t mtl_id) {
	* mtl << "\n";
	* mtl << "newmtl " << std::to_string(mtl_id) << "\n";
	* mtl << "Ka " << double(rgb.r) / 255 << " " << double(rgb.g) / 255 << " " << double(rgb.b) / 255 << "\n";
	* mtl << "Kd " << double(rgb.r) / 255 << " " << double(rgb.g) / 255 << " " << double(rgb.b) / 255 << "\n";
	* mtl << "Ks 0 0 0\n";
	* mtl << "Ns 0\n";
	* mtl << "d 1";
}



void Str::obj_begin (std::string mtl_file) {
	* obj << "mtllib " << mtl_file << ".mtl\n";
}

void Str::faces_begin () {
	* obj << "\n";
}



void Str::use_mtl (std::string mtl_name) {
	* obj << "\n";
	* obj << "usemtl " << mtl_name;
}

void Str::use_mtl (object_id_t mtl_id) {
	* obj << "\n";
	* obj << "usemtl " << std::to_string(mtl_id);
}



void Str::add_vertex (Point const & point) {
	coord_t xyz[3];
	xyz[direct[0]] = point.x;
	xyz[direct[1]] = point.y;
	xyz[direct[2]] = point.z;
	* obj << "\n";
	* obj << "v " << xyz[0] << " " << xyz[1] << " " << xyz[2];
}

void Str::add_face (std::vector<object_id_t> const & points) {
	assert(points.size() >= 3);
	* obj << "\n";
	* obj << "f ";
	* obj << points.front() + 1;
	for (object_id_t i = 1; i < points.size(); i++) {
		* obj << " " << points[i] + 1;
	}
}



void Str::repair_permutation (uint8_t * main, uint8_t * to_repair) {
	to_repair[main[0]] = 0;
	to_repair[main[1]] = 1;
	to_repair[main[2]] = 2;
}

bool Str::check_permutation (uint8_t * permutation) {
	bool b = false;
	for (uint8_t i = 0; i <= 2; i++) {
		for (uint8_t j = 0; j <= 2; j++) {
			if (permutation[j] == i) {
				b = true;
			}
		}
		if (!b) {
			return false;
		}
	}
	return true;
}
	
} // namespace graphics::threedim::obj