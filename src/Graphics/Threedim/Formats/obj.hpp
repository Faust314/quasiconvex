#pragma once

#include "../../Color/color.hpp"
#include "../types.hpp"
#include "../../../Utils/Basic/types.hpp"

#include <fstream>
#include <vector>

namespace graphics::threedim::obj {

class Str {
public:
	Str () = default;
	void init (std::ofstream & mtl_, std::ofstream & obj_);
	Str (std::ofstream & mtl_, std::ofstream & obj_);
	
	void change_direct_permutation (uint8_t x_to, uint8_t y_to, uint8_t z_to);
	void change_reverse_permutation (uint8_t to_x, uint8_t to_y, uint8_t to_z);
	
	void set_precision (aux::precision_t precision_);
	
	void new_mtl (color::RGB const & rgb, std::string mtl_name);
	void new_mtl (color::RGB const & rgb, object_id_t mtl_id);
	
	void obj_begin (std::string mtl_file);
	void faces_begin ();
	
	void use_mtl (std::string mtl_name);
	void use_mtl (object_id_t mtl_id);
	
	void add_vertex (Point const & point);
	void add_face (std::vector<object_id_t> const & points);
	
private:
	uint8_t direct[3] = {0, 1, 2};
	uint8_t reverse[3] = {0, 1, 2};
	
	void repair_permutation (uint8_t * main, uint8_t * to_repair);
	bool check_permutation (uint8_t * permutation);
	
	aux::precision_t precision = 6;
	
	std::ofstream * mtl;
	std::ofstream * obj;
};

} // namespace graphics::threedim::obj