#include "svg_config.hpp"

#include <cassert>

namespace graphics::twodim::svg {

void Output::init (std::ofstream & ofs_) {
	_ofs = & ofs_;
}

Output::Output (std::ofstream & ofs_) :
	_ofs(& ofs_)
{ }



std::ofstream & Output::ofs () {
	(* _ofs) << _space;
	return * _ofs;
}

std::ofstream & Output::get_ofs () {
	return * _ofs;
}

void Output::change_space (Output::param_t const diff) {
	assert(_space.size() + diff >= 0);
	_space.resize(_space.size() + diff, ' ');
}



void Output::set_ofs (std::ofstream & ofs_) {
	assert(_ofs != nullptr);
	_ofs = & ofs_;
}

std::string const & Output::space () const {
	return _space;
}
	
} // namespace graphics::twodim::svg
