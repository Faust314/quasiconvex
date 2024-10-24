#include "svg.hpp"

namespace graphics::twodim::svg {

Print::Print () :
	_path(output),
	_primitives(output)
{}

void Print::reset (std::ostream & os, Settings const & settings_) {
	output.init(os);
	_file_structs.init(settings_, output);
}

Print::Print (std::ostream & os, Settings const & settings_) :
	output(os),
	_file_structs(settings_, output),
	_path(output),
	_primitives(output)
{}



FileStructs const & Print::file_structs () const{
	return _file_structs;
}

Path const & Print::path () const {
	return _path;
}

Primitives const & Print::primitives () const {
	return _primitives;
}

} // namespace graphics::twodim::svg