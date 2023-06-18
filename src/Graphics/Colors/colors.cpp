#include "rgb.hpp"

namespace graphics {

std::unordered_map<std::string, RGB> colors = {
	{"black", RGB(0, 0, 0)},
	{"white", RGB(255, 255, 255)},
	{"red", RGB(255, 0, 0)},
	{"green", RGB(0, 255, 0)},
	{"blue", RGB(0, 0, 255)}
};

} // namespace graphics