#pragma once

#include "types.hpp"
#include "../Math/Functions/func.hpp"
#include "../Utils/Basic/json.hpp"

#include <unordered_set>

namespace biconcave {

class Master {
public:
	Master () = default;
	
	void read (std::string const & path);
	
	void run ();
	
private:
	std::string output_path;
	
	value_t screen_width = 1920;
	value_t screen_height = 1080;
	value_t margin = 50;
	
	value_t slider0;
	value_t slider1;
	steps_count_t sliders_number;
	
	func::Func left_domain_pos;
	func::Func right_domain_pos;
	func::Func strip_width;
	func::Func grid_size;
	
	func::Func steps_count;
	
	size_t function_grid_size = 10;
	
	func::Func f;
	func::Func g;
	
	func::Func color_func;
	uint16_t colors_number;
	
	char prev;
	char next;
	char switch_profile;
	char switch_f;
	char switch_g;
	
	static std::vector<std::string> const options;
	
	void create_html ();
	void create_css ();
	void create_js ();
};

} // namespace biconcave