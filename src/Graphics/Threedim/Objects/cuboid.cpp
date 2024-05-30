#include "cuboid.hpp"

#include "../../../Math/Geometry/Stereometry/threedim_point.tpp"

namespace graphics::threedim::objects {

void add_cuboid (Model & model, Point const & a, Point const & b, object_id_t color_id) {
	object_id_t point_id = model.points().size();
	model.add_point({a.x, a.y, a.z});
	model.add_point({b.x, a.y, a.z});
	model.add_point({a.x, b.y, a.z});
	model.add_point({b.x, b.y, a.z});
	model.add_point({a.x, a.y, b.z});
	model.add_point({b.x, a.y, b.z});
	model.add_point({a.x, b.y, b.z});
	model.add_point({b.x, b.y, b.z});
	
	model.add_face({point_id + 0, point_id + 2, point_id + 3, point_id + 1}, color_id);
	model.add_face({point_id + 4, point_id + 5, point_id + 7, point_id + 6}, color_id);
	model.add_face({point_id + 0, point_id + 1, point_id + 5, point_id + 4}, color_id);
	model.add_face({point_id + 2, point_id + 6, point_id + 7, point_id + 3}, color_id);
	model.add_face({point_id + 0, point_id + 4, point_id + 6, point_id + 2}, color_id);
	model.add_face({point_id + 1, point_id + 3, point_id + 7, point_id + 5}, color_id);
}

void add_cuboid (Model & model, Point const & a, Point const & b) {
	add_cuboid(model, a, b, model.colors().size() - 1);
}
	
} // namespace graphics::threedim::objects
