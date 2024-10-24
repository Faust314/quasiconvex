#include "object.hpp"

#include "path.hpp"

namespace graphics::twodim {

Path Object::get_path () {
	Path path;
	convert_to_path(path);
	return path;
}

Path * Object::get_path_pointer () {
	Path * path = new Path ();
	convert_to_path(* path);
	return path;
}

} // namespace graphics::twodim
