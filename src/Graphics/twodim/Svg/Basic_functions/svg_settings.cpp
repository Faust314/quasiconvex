#include "svg_settings.hpp"

#include <cassert>

namespace graphics::twodim::svg {


void Settings::init (Settings::program const program_type_, ::aux::precision_t precision_) {
	_program_type = program_type_;
	_precision = precision_;
}

Settings::Settings (Settings::program const program_type_, ::aux::precision_t precision_) :
	_program_type(program_type_), _precision(precision_), _space("")
{}



void Settings::set_precision (::aux::precision_t const precision) {
	_precision = precision;
}



Settings::program const & Settings::program_type () const {
	return _program_type;
}

::aux::precision_t const & Settings::precision () const {
	return _precision;
}



void Settings::change_space (Settings::param_t const diff) {
	assert(_space.size() + diff >= 0);
	_space.resize(_space.size(), ' ');
}

std::string const & Settings::space () const {
	return _space;
}
	
} // namespace graphics::twodim::svg
