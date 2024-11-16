#pragma once

#include "../types.hpp"

#include <vector>

namespace biconcave {

std::vector<uint8_t> calculate_transform (std::vector<value_id_t> const & counts, uint16_t colors_number);

} // namespace biconcave