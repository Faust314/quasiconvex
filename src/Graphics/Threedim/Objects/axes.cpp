#include "axes.hpp"

#include "cuboid.hpp"

#include "../../../Math/Geometry/Stereometry/threedim_point.tpp"

namespace graphics::threedim::objects {

void add_axes (Model & model, Point const & center, Point const & a, Point const & b, coord_t width) {
	width /= 2;
	
	model.add_color(color::RGB(255, 0, 0));
	add_cuboid(model,
		{a.x, center.y - width, center.z - width},
		{b.x, center.y + width, center.z + width}
	);
	
	model.add_color(color::RGB(0, 255, 0));
	add_cuboid(model,
		{center.x - width, a.y, center.z - width},
		{center.x + width, b.y, center.z + width}
	);
	
	model.add_color(color::RGB(0, 0, 255));
	add_cuboid(model,
		{center.x - width, center.y - width, a.z},
		{center.x + width, center.y + width, b.z}
	);
}
	
} // namespace graphics::threedim::objects