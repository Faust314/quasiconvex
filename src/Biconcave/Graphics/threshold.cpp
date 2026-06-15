#include "threshold.hpp"

#include <algorithm>

namespace biconcave {

std::vector<uint8_t> calculate_transform (std::vector<value_id_t> const & counts, uint16_t colors_number) {
	std::vector<uint8_t> transform(256, 0);
	
	std::vector<uint8_t> colors;
	colors.reserve(256);
	for (uint16_t color = 0; color < 256; color++) {
		if (counts[color] > 0) {
			colors.push_back(color);
			transform[color] = color;
		}
	}
	if (colors.size() <= colors_number) {
		return transform;
	}
	
	
	std::vector<std::pair<uint8_t, uint8_t>> lengths;
	lengths.reserve(colors.size());
	for (uint16_t color = 0; color <= colors.size() - 2; color++) {
		lengths.emplace_back(colors[color + 1] - colors[color], color);
	}
	std::sort(lengths.begin(), lengths.end());
	std::vector<uint8_t> united_color_ids;
	united_color_ids.reserve(lengths.size());
	for (uint16_t color = 0; color < lengths.size() - colors_number + 1; color++) {
		united_color_ids.push_back(lengths[color].second);
	}
	std::sort(united_color_ids.begin(), united_color_ids.end());
	uint8_t id0 = united_color_ids[0];
	for (uint16_t i = 1; i <= united_color_ids.size(); i++) {
		if (united_color_ids[i - 1] + 1 < united_color_ids[i] || i == united_color_ids.size()) {
			uint8_t id1 = united_color_ids[i - 1] + 1;
			uint8_t max_id = id0;
			for (uint16_t id = id0; id <= id1; id++) {
				if (counts[colors[id]] > counts[colors[max_id]]) {
					max_id = id;
				}
			}
			for (uint16_t id = id0; id <= id1; id++) {
				transform[colors[id]] = colors[max_id];
			}
			id0 = united_color_ids[i];
		}
	}
	return transform;
}

} // namespace biconcave
