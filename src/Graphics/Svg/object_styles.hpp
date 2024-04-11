#pragma once

#include "../Colors/rgb.hpp"

#include <string>
#include <vector>
#include <array>

namespace graphics::svg::object {

struct RGB_O {
	RGB rgb;
	double t; // opacity
	
	explicit RGB_O (uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, double t_ = 1);
	explicit RGB_O (RGB const & rgb, double t_ = 1);
};





struct Stroke;

struct Fill {
	friend std::string style(Fill const & fill);
	friend std::string style(Fill const & fill, Stroke const & stroke);
	
	bool empty;
	RGB_O color;
	
	explicit Fill ();
	explicit Fill (RGB_O color_);
	
private:
	std::string operator() () const;
};



struct Stroke {
	friend std::string style(Stroke const & stroke);
	friend std::string style(Fill const & fill, Stroke const & stroke);
	
//private:
	constexpr static std::array<std::string, 3> linecaps{"butt", "round", "square"};
	constexpr static std::array<std::string, 3> linejoins{"bevel", "round", "miter"};
	
public:
	enum class Linecap {butt, round, square};
	enum class Linejoin {bevel, round, miter};
	
	bool empty;
	RGB_O color;
	double width;
	Linecap linecap;
	Linejoin linejoin;
	
	Stroke ();
	explicit Stroke (
		RGB_O color_,
		double width_ = 5,
		Linecap linecap_ = Linecap::round,
		Linejoin linejoin = Linejoin::round
	);
	
private:
	std::string operator() () const;
};

} // namespace graphics::svg::object