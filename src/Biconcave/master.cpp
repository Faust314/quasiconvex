#include "master.hpp"

#include "biconcave.hpp"
#include "../Utils/Basic/dir_utils.hpp"

#include <fstream>

namespace biconcave {

std::vector<std::string> const Master::options = {
	"prev:", "next:",
	"switch_profile:", "switch_f:", "switch_g:",
	"screen_width:", "screen_height:", "margin:",
	"output_path:",
	"color:", "colors_number:",
	"slider0:", "slider1:", "sliders_number:",
	"grid_size:", "steps_count:",
	"left_domain_pos:", "right_domain_pos:", "strip_width:",
	"f:", "g:"
};

void Master::read (std::string const & path) {
	std::ifstream ifs (path);
	std::ostringstream os;
	os << ifs.rdbuf();
	
	std::vector<std::string> option_values(options.size());
	for (size_t i = 0; i < os.str().size(); i++) {
		for (size_t j = 0; j < options.size(); j++) {
			if (i + options[j].size() <= os.str().size() && os.str().substr(i, options[j].size()) == options[j]) {
				assert(option_values[j].empty());
				i += options[j].size();
				while (i < os.str().size() && (os.str()[i] == ' ' || os.str()[i] == '\n')) {
					i++;
				}
				while (i < os.str().size() && os.str()[i] != ';') {
					option_values[j].push_back(os.str()[i]);
					i++;
				}
				while (
					! option_values[j].empty() &&
					option_values[j].back() == ' ' ||
					option_values[j].back() == '\n'
				) {
					option_values[j].pop_back();
				}
				i++;
				continue;
			}
		}
	}
#ifndef NDEBUG
	for (auto const & s : option_values) {
		assert(! s.empty());
	}
#endif
	assert(option_values[0].size() == 1);
	prev = option_values[0].front();
	assert(option_values[1].size() == 1);
	next = option_values[1].front();
	assert(option_values[2].size() == 1);
	switch_profile = option_values[2].front();
	assert(option_values[3].size() == 1);
	switch_f = option_values[3].front();
	assert(option_values[4].size() == 1);
	switch_g = option_values[4].front();
	screen_width = std::stod(option_values[5]);
	screen_height = std::stod(option_values[6]);
	margin = std::stod(option_values[7]);
	output_path = option_values[8];
	color_func.init(option_values[9], {"t", "s"});
	colors_number = std::stoi(option_values[10]);
	slider0 = std::stod(option_values[11]);
	slider1 = std::stod(option_values[12]);
	sliders_number = std::stoi(option_values[13]);
	grid_size.init(option_values[14], {"s"});
	steps_count.init(option_values[15], {"s"});
	left_domain_pos.init(option_values[16], {"s"});
	right_domain_pos.init(option_values[17], {"s"});
	strip_width.init(option_values[18], {"s"});
	f.init(option_values[19], {"t", "s"});
	g.init(option_values[20], {"t", "s"});
}

void Master::run () {
	assert(sliders_number >= 1);
	value_t slider_delta = sliders_number == 1 ? 0 : (slider1 - slider0) / (sliders_number - 1);
	value_t slider;
	
	aux::dir::clear_directory(output_path);
	
	graphics::twodim::svg::Settings settings;
	settings.program_type = graphics::twodim::svg::Settings::program_type_t::browser;
	
	for (steps_count_t step = 0; step < sliders_number; step++) {
		std::cout << "slider " << step << "\n";
		slider = slider0 + step * slider_delta;
		Biconcave B(settings, screen_width, screen_height, margin, slider);
		size_t cell_grid = std::lround(grid_size({slider}));
		cell_grid = function_grid_size / cell_grid + (function_grid_size % cell_grid == 0 ? 0 : 1);
		B.init_array(
			strip_width({slider}),
			left_domain_pos({slider}),
			right_domain_pos({slider}),
			coord_t(std::lround(grid_size({slider})))
		);
		B.print_function(
			output_path + "/f/" + std::to_string(step) + ".svg", "f" + std::to_string(step), f, cell_grid
		);
		B.print_function(
			output_path + "/g/" + std::to_string(step) + ".svg", "g" + std::to_string(step), g, cell_grid
		);
		B.init_array_border_values(f, g);
		B.calculate_hull(steps_count_t(steps_count({slider})));
		B.calculate_hessian();
		B.calculate_graphics(color_func, colors_number);
		B.print_profile(output_path + "/p/" + std::to_string(step) + ".svg", std::to_string(step));
		
		create_html();
		create_css();
		create_js();
	}
}

void Master::create_html () {
	std::ofstream ofs (output_path + "/index.html");
	ofs <<
R"123(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Image Flipper</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
<div class="image-container">
    <img id="image" src="p/0.svg" alt="Image Flipper">
</div>

<script src="script.js"></script>
</body>
</html>)123";
}

void Master::create_css () {
	std::ofstream ofs (output_path + "/styles.css");
	ofs <<
R"123(body {
    display: flex;
    align-items: center;
    justify-content: center;
    height: 100vh;
    margin: 0;
    background-color: #ffffff;
})123";
	
	ofs << "\n";
	ofs << "\n.image-container {";
	ofs << "\n    width: " << screen_width << "px;";
	ofs << "\n    height: " << screen_height << "px;";
	ofs << "\n    display: flex;";
	ofs << "\n    align-items: center;";
	ofs << "\n    justify-content: center;";
	ofs << "\n    ";
	ofs << "}";
	
	ofs << "\n";
	ofs <<
R"123(img {
    max-width: 100%;
    max-height: 100%;
})123";
}

void Master::create_js () {
	std::ofstream ofs (output_path + "/script.js");
	ofs << "const images = [";
	for (std::string s : {"p", "f", "g"}) {
		ofs << "\n    [\"" << s << "/0.svg\"";
		for (steps_count_t slider = 1; slider < sliders_number; slider++) {
			ofs << ", \"" << s << "/" << slider << ".svg\"";
		}
		ofs << "]";
		if (s != "g") {
			ofs << ",";
		}
	}
	ofs << "];";
	
	ofs << "\nlet size = " << sliders_number << ";";
	ofs << "\nprev = " << "\"" << prev << "\";";
	ofs << "\nnext = " << "\"" << next << "\";";
	ofs << "\nswitch_profile = " << "\"" << switch_profile << "\";";
	ofs << "\nswitch_f = " << "\"" << switch_f << "\";";
	ofs << "\nswitch_g = " << "\"" << switch_g << "\";";
	
	ofs << "\n";
	ofs <<
		R"123(let type = 0;
let id = 0;
const imgElement = document.getElementById("image");
document.addEventListener("keydown", (event) => {
    if (event.key === prev) {
        id = id - 1;
    } else if (event.key === next) {
        id = id + 1;
    } else if (event.key === switch_profile) {
        type = 0;
    } else if (event.key === switch_f) {
        type = 1;
    } else if (event.key === switch_g) {
        type = 2;
    }
    if (id < 0) {
        id = 0;
    } else if (id >= size) {
        id = size - 1;
    }
    imgElement.src = images[type][id];
});)123";
}
	
} // namespace biconcave
