#pragma once

#include "../Painting/types.hpp"

#include <vector>
#include <string>

namespace graphics::twodim::svg {

std::vector<std::string> linecap_to_str {"butt", "round", "square"};
std::vector<std::string> linejoin_to_str {"bevel", "round", "square"};

} // namespace graphics::twodim::svg