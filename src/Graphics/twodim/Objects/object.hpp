#pragma once

#include "../../types.hpp"
#include "../Painting/_painting.hpp"
#include "../../../Utils/Basic/json.hpp"
#include "../Svg/svg.hpp"

namespace graphics::twodim {

class Path;

class Object {
public:
	Object() = default;
	
	virtual void read (aux::Json const & json) {};
	virtual void write (aux::Json & json) const {};
	
	virtual void print_svg (svg::Print const & print, Paint const & paint, object_id_t object_id) const {};
	
	virtual bool supports_react_transform () {return false;};
	virtual bool supports_affine_transform () {return false;};
	virtual bool supports_common_transform () {return false;};
	virtual void rect_transform (
		[[maybe_unused]] Rectangular const & rectangular
	) {assert(false);};
	virtual void affine_transform (
		[[maybe_unused]] Affine const & affine
	) {assert(false);};
	virtual void common_transform (
		[[maybe_unused]] std::function<Point (Point const &)> const & transform
	) {assert(false);};
	
	virtual Path get_path ();
	virtual Path * get_path_pointer ();
	
private:
	virtual void convert_to_path (Path & path) {};
};

} // namespace graphics::twodim