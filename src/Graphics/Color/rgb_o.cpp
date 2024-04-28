#include "rgb_o.hpp"

#include "opacity.tpp"

namespace graphics::color {

RGB_O::RGB_O (arg_t r_, arg_t g_, arg_t b_, double op_) :
	Opacity<RGB>(op_, RGB(r_, g_, b_))
{ }

} // namespace graphics::color
