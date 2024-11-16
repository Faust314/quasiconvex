#pragma once

#include "../hessian.hpp"
#include "../types.hpp"
#include "../../Graphics/Twodim/Svg/svg.hpp"
#include "../../Graphics/types.hpp"

#include <string>

namespace biconcave {

class Graphics {
public:
	Graphics () = default;
	void init (RealArray const & real_array);
	explicit Graphics (RealArray const & real_array);
	
	std::vector<value_id_t> set_colors (
		Hessian const & hessian, func::Func const & colors_func, value_t slide_value
	);
	void apply_transform (std::vector<uint8_t> const & transform, Hessian const & hessian);
	
	graphics::color::RGB color (Point const & p);
	
private:
	array::Twodim<graphics::color::RGB> colors;
};

} // namespace biconcave