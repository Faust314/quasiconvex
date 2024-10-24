#include "svg_config.hpp"

#include <cassert>

namespace graphics::twodim::svg {

void Output::init (std::ostream & os_) {
	_os = & os_;
}

Output::Output (std::ostream & os_) :
	_os(& os_)
{ }



std::ostream & Output::os () {
	(* _os) << _space;
	return * _os;
}

std::ostream & Output::get_os () {
	return * _os;
}

void Output::change_space (Output::param_t const diff) {
	assert(_space.size() + diff >= 0);
	_space.resize(_space.size() + diff, ' ');
}



void Output::set_os (std::ostream & os_) {
	assert(_os != nullptr);
	_os = & os_;
}

std::string const & Output::space () const {
	return _space;
}
	
} // namespace graphics::twodim::svg
