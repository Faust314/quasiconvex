#pragma once

#include "../model.hpp"

namespace graphics::threedim::objects {

void add_cuboid (Model & model, Point const & a, Point const & b, object_id_t color_id);
void add_cuboid (Model & model, Point const & a, Point const & b);

} // namespace graphics::threedim::objects