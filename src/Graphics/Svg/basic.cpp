#include "basic.hpp"

#include "../../Utils/Basic/time_utils.hpp"
#include "../../Utils/Basic/type_utils.hpp"

#include <cassert>
#include <utility>
#include <cmath>

namespace graphics::svg {

Object::Object (std::string  name_) :
	name(std::move(name_))
{ }

std::string & Object::operator() () {
	return lines.back();
}

std::string & Object::new_line (std::string const & line) {
	lines.emplace_back(line);
	return lines.back();
}

Object::Object (Object const & object) :
	name(object.name),
	lines(object.lines)
{ }

Object::Object (Object && object) noexcept :
	name(std::move(object.name)),
	lines(std::move(object.lines))
{ }

Object & Object::operator= (Object const & object) {
	name = object.name;
	lines = object.lines;
	return *this;
}

Object & Object::operator= (Object && object)  noexcept {
	name = std::move(object.name);
	lines = std::move(object.lines);
	return *this;
}

void Object::print (std::ofstream & ofs, const std::string& space) const {
	ofs << space << "<" << name;
	
	assert(!lines.empty());
	for (auto & line : lines) {
		ofs << "\n";
		ofs << space << "   " << line;
	}
	
	ofs << " />\n";
}





std::function<std::string (coord_t)> File::to_str = std::function<std::string (double)>(::aux::types::to_string);

void File::Layer::add_object (Object && obj) {
	objects.push_back(std::move(obj));
}

void File::Layer::print (std::ofstream & ofs, const std::string& space) const {
	ofs << space <<	"<g\n";
	ofs << space << "  inkscape:groupmode=\"layer\"\n";
	ofs << space << "  id=\"layer" << int(number) << "\"\n";
	ofs << space << "  inkscape:label=\"" << name <<"\">\n";
	
	for (auto & obj : objects) {
		obj.print(ofs, space + "  ");
	}
	ofs << space <<	"</g>\n";
}

File::File () :
	file_name("figure_" + aux::time::date(time(nullptr))),
	width(display_width),
	height(display_height),
	zoom_view(0.8),
	layers(1),
	layer_numbers()
{ layers[0].name = "main", layers[0].number = 0; layer = & layers[0]; }

File::File (std::string file_name_, double width_, double height_, double zoom_view_) :
	file_name(std::move(file_name_)),
	width(width_),
	height(height_),
	zoom_view(zoom_view_),
	layers(1),
	layer_numbers()
{ layers[0].name = "main", layers[0].number = 0; layer = & layers[0]; }



void File::set_name (std::string const & file_name_) {
	file_name = file_name_;
}

void File::set_width (double width_) {
	width = width_;
}

void File::set_height (double height_) {
	height = height_;
}

void File::set_zoom_view (double zoom_view_) {
	zoom_view = zoom_view_;
}



double File::get_width () const {
	return width;
}

double File::get_height () const {
	return height;
}





void File::choose_layer (std::string const & name) {
	layer = & layers[layer_numbers[name]];
}

void File::choose_layer (File::layer_number_t number) {
	layer = & layers[number];
}

void File::set_layer_count (layer_number_t count) {
	layer_number_t previos_count = layers.size();
	layers.resize(count);
	for (layer_number_t number = previos_count + 1; number < layers.size(); number++) {
		layers[number].number = number;
	}
}

File::layer_number_t File::get_layer_count () const {
	return layers.size();
}

void File::set_layer (std::string const & name, layer_number_t number) {
	layer_numbers[name] = number;
	layers[number].name = name;
}

File::Layer & File::get_layer (std::string const & name) {
	assert(layer_numbers.contains(name));
	return get_layer(layer_numbers.find(name)->second);
}

File::Layer const &  File::get_layer (std::string const & name) const {
	assert(layer_numbers.contains(name));
	return get_layer(layer_numbers.find(name)->second);
}

File::Layer & File::get_layer (File::layer_number_t number) {
	return layers[number];
}

File::Layer const &  File::get_layer (layer_number_t number) const {
	return layers[number];
}

bool File::check_layer_names_consistency () const {
	std::vector<bool> check(layers.size(), false);
	for (auto & layer : layer_numbers) {
		if (check[layer.second]) return false;
		check[layer.second] = true;
	}
	for (auto b : check) {
		if (!b) {
			return false;
		}
	}
	return true;
}



void File::add_object (Object && obj, std::string const & layer_name) {
	get_layer(layer_name).add_object(std::move(obj));
}

void File::add_object (Object && obj, layer_number_t layer_number) {
	get_layer(layer_number).add_object(std::move(obj));
}

void File::add_object (Object && obj) {
	layer->add_object(std::move(obj));
}


std::string & File::new_line (std::string const & line) {
	layer->objects.back().lines.emplace_back(line);
	return layer->objects.back().lines.back();
}

std::string & File::last_line () {
	return layer->objects.back().lines.back();
}

void File::print (std::string const & dir) const {
	std::ofstream ofs (dir + "/" + file_name + ".svg");
	print_prefix(ofs);
	for (layer_number_t number = layers.size(); number >= 1; number-- ) {
		layers[number - 1].print(ofs, "  ");
	}
	print_suffix(ofs);
}

void File::print_prefix (std::ofstream & ofs) const {
	ofs << R"(<?xml version="1.0" encoding="UTF-8" standalone="no"?>)" << "\n";
	ofs << "<svg\n";
	ofs << "   width=\"" << width << "\"\n";
	ofs << "   height=\"" << height << "\"\n";
	ofs << "   viewBox=\"0 0 " << width << " " << height << "\"\n";
	ofs << R"abc(   version="1.1"
   id="svg5"
   inkscape:version="1.2 (dc2aedaf03, 2022-05-15)"
   sodipodi:docname="picture1.svg"
   xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape"
   xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd"
   xmlns="http://www.w3.org/2000/svg"
   xmlns:svg="http://www.w3.org/2000/svg">
)abc";
	ofs << "  <sodipodi:namedview\n";
	ofs << R"(     id="namedview7"
     pagecolor="#ffffff"
     bordercolor="#000000"
     borderopacity="0.25"
     inkscape:showpageshadow="2"
     inkscape:pageopacity="0.0"
     inkscape:pagecheckerboard="0"
     inkscape:deskcolor="#d1d1d1"
     inkscape:document-units="px"
     showgrid="false"
)";
	
	ofs << "     inkscape:zoom=\"" << zoom_view * std::min(display_width / width, display_height / height) << "\"\n";
	ofs << "     inkscape:cx=\"" << width / 2 << "\"\n";
	ofs << "     inkscape:cy=\"" << height / 2 << "\"\n";
	ofs << "     inkscape:window-width=\"" << width << "\"\n";
	ofs << "     inkscape:window-height=\"" << height << "\"\n";
	
	ofs << R"(     inkscape:window-x="-11"
     inkscape:window-y="-11"
     inkscape:window-maximized="1"
     inkscape:current-layer="svg5" />
  <defs
     id="defs2" />
)";
	
}

void File::print_suffix (std::ofstream & ofs) {
	ofs << "</svg>\n";
}

} // namespace graphics::svg
