#pragma once

#include "../types.hpp"

#include <unordered_map>
#include <string>
#include <fstream>
#include <cstdint>

namespace graphics::color {

struct RGB {
	arg_t r;
	arg_t g;
	arg_t b;
	
	explicit RGB (arg_t r_ = 0, arg_t g = 0, arg_t b = 0);
	
	void compress (arg_t step);
	
	uint32_t hash ();
	
	std::string to_string_16 () const;
};

} // namespace graphics::color

