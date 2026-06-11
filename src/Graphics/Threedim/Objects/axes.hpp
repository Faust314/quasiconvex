#pragma once

#include "../model.hpp"

namespace graphics::threedim::objects {

void add_axes (Model & model, Point const & center, Point const & a, Point const & b, coord_t width);

} // namespace graphics::threedim::objects