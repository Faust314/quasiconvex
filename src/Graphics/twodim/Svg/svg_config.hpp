#pragma once

#include "../../types.hpp"
#include "../../../Utils/Basic/types.hpp"

#include <string>
#include <cstdint>
#include <iostream>
#include <fstream>

namespace graphics::twodim::svg {

class Settings {
public:
	enum class program_type_t {inkscape, browser};
	
	Settings () = default;
	
	program_type_t program_type = program_type_t::inkscape;
	::aux::precision_t precision = 6;
	coord_t zoom_view = 0.8;
	coord_t display_width = 1920;
	coord_t display_height = 1080;
};



class Output {
public:
	typedef int8_t param_t;
	
public:
	Output () = default;
	void init (std::ostream & os_);
	explicit Output (std::ostream & os_);
	
	std::ostream & os ();
	std::ostream & get_os ();
	std::string const & space () const;
	
	void set_os (std::ostream & os_);
	void change_space (param_t const diff);
	
private:
	std::ostream * _os = nullptr;
	std::string _space = "\n";
};

} // namespace graphics::twodim::svg