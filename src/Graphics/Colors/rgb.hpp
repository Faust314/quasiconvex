#pragma once

#include <unordered_map>
#include <string>
#include <fstream>

namespace graphics {

struct RGB {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	
	explicit RGB(uint8_t r_ = 0, uint8_t g = 0, uint8_t b = 0);
	
	RGB res(uint8_t step) const ;
	RGB res_3() const;
	RGB res_5() const;
	RGB res_15() const;
	RGB res_17() const;
	RGB res_51() const;
	RGB res_85() const;
	
	std::string to_string_16() const;
};

extern std::unordered_map<std::string, RGB> colors;

}

