#include "graphics.hpp"

namespace biconcave {

void Graphics::init (RealArray const & real_array) {
	colors.init(real_array);
}

Graphics::Graphics (RealArray const & real_array) {
	init(real_array);
}



std::vector<value_id_t> Graphics::set_colors (
	Hessian const & hessian, func::Func const & colors_func, value_t slide_value
) {
	std::vector<value_id_t> colors_count(256, 0);
	ArrayPoint p;
	std::array<uint8_t, 2> c;
	for (coord_t x = 0; x < colors.x_size(); x++) {
		for (coord_t y = 0; y < colors.y_size(); y++) {
			p = {x, y};
			for (uint8_t dim = 0; dim < 2; dim++) {
				if (colors.has_point(p) && hessian.has_derivative(dim, p)) {
					c[dim] = uint8_t(std::round(255 * colors_func({
						std::abs(hessian.derivative(dim, p)), slide_value
					})));
					colors_count[c[dim]]++;
				} else {
					c[dim] = 0;
				}
			}
			colors.value(p) = graphics::color::RGB(c[0], c[1], 0);
		}
	}
	return colors_count;
}

void Graphics::apply_transform (std::vector<uint8_t> const & transform, Hessian const & hessian) {
	for (coord_t x = 0; x < colors.x_size(); x++) {
		for (coord_t y = 0; y < colors.y_size(); y++) {
			if (colors.has_point({x, y})) {
				if (hessian.has_derivative(0, {x, y})) {
					colors.value({x, y}).r = transform[colors.value({x, y}).r];
				}
				if (hessian.has_derivative(1, {x, y})) {
					colors.value({x, y}).g = transform[colors.value({x, y}).g];
				}
			}
		}
	}
}



graphics::color::RGB Graphics::color (Point const & p) {
	return colors.value(p);
}

} // namespace biconcave
