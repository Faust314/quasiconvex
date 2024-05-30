#pragma once

#include "../../types.hpp"
#include "../../../Utils/Basic/types.hpp"

#include <string>
#include <cstdint>
#include <iostream>

namespace graphics::twodim::svg {

class Settings {
public:
	enum class program {inkscape, browser};
	
	Settings () = default;
	
	program program_type = program::inkscape;
	::aux::precision_t precision = 6;
	coord_t zoom_view = 0.8;
	coord_t display_width = 1920;
	coord_t display_height = 1080;
	
	void init_pointers ();
};



class OutputParameters {
public:
	typedef int8_t param_t;
	
	OutputParameters () = default;
	void init (std::ofstream & ofs_);
	OutputParameters (std::ofstream & ofs_);
	
	std::ofstream & ofs ();
	std::string const & space () const;
	
	void set_ofs (std::ofstream & ofs_);
	void change_space (param_t const diff);
	
	void init_pointers ();
	
private:
	std::ofstream * _ofs = nullptr;
	std::string _space = 0;
};

} // namespace graphics::twodim::svg