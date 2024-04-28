#include "svg_config.hpp"

#include "Basic/file_struct.hpp"
#include "Objects/paths.hpp"
#include "Objects/primitives.hpp"

#include <cassert>

namespace graphics::twodim::svg {


void OutputParameters::init (std::ofstream & ofs_) {
	_ofs = & ofs_;
}

OutputParameters::OutputParameters (std::ofstream & ofs_) :
	_ofs(& ofs_)
{ }



void OutputParameters::set_ofs (std::ofstream & ofs_) {
	assert(_ofs != nullptr);
	_ofs = & ofs_;
}

std::ofstream & OutputParameters::ofs () {
	return * _ofs;
}



void OutputParameters::change_space (OutputParameters::param_t const diff) {
	assert(_space.size() + diff >= 0);
	_space.resize(_space.size() + diff, ' ');
}

std::string const & OutputParameters::space () const {
	return _space;
}



void set_settings (Settings const & settings) {
	
}

void set_output_parameters (OutputParameters & parameters) {
	
}

} // namespace graphics::twodim::svg
