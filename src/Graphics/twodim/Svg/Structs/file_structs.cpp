#include "file_structs.hpp"

#include "../../../Color/rgb_o.tpp"
#include "../types.hpp"

#include <cassert>

namespace graphics::twodim::svg {

void FileStructs::init (Settings const & settings, Output & output) {
	_settings = & settings;
	_output = & output;
}

FileStructs::FileStructs (Settings const & settings, Output & output) :
	_settings(& settings),
	_output(& output)
{}



void FileStructs::file_begin (coord_t width, coord_t height, std::string const & file_name) const {
	if (_settings->program_type == Settings::program_type_t::inkscape) {
		_output->get_os() << R"a(<?xml version="1.0" encoding="UTF-8" standalone="no"?>)a";
		_output->os() <<    "<svg";
		_output->os() <<    "   width=\"" << width << "\"";
		_output->os() <<    "   height=\"" << height << "\"";
		_output->os() <<    "   viewBox=\"0 0 " << width << " " << height << "\"";
		_output->os() << R"a(   version="1.1")a";
		_output->os() << R"a(   id="svg1")a";
		_output->os() << R"a(   inkscape:version="1.3.2 (091e20e, 2023-11-25, custom)")a";
		_output->os() <<    "   sodipodi:docname=\"" << file_name << ".svg\"";
		_output->os() << R"a(   xmlns:inkscape="http://www.inkscape.org/namespaces/inkscape")a";
		_output->os() << R"a(   xmlns:sodipodi="http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd")a";
		_output->os() << R"a(   xmlns="http://www.w3.org/2000/svg")a";
		_output->os() << R"a(   xmlns:svg="http://www.w3.org/2000/svg">)a";
		_output->os() << R"a(  <sodipodi:namedview)a";
		_output->os() << R"a(     id="namedview1")a";
		_output->os() << R"a(     pagecolor="#ffffff")a";
		_output->os() << R"a(     bordercolor="#000000")a";
		_output->os() << R"a(     borderopacity="0.25")a";
		_output->os() << R"a(     inkscape:showpageshadow="2")a";
		_output->os() << R"a(     inkscape:pageopacity="0.0")a";
		_output->os() << R"a(     inkscape:pagecheckerboard="0")a";
		_output->os() << R"a(     inkscape:deskcolor="#d1d1d1")a";
		_output->os() << R"a(     inkscape:document-units="px")a";
		_output->os() <<    "     inkscape:zoom=\"" << _settings->zoom_view * std::min(
			_settings->display_width / width, _settings->display_height / height
		) << "\"";
		_output->os() << R"a(     inkscape:deskcolor="#d1d1d1")a";
		_output->os() <<    "     inkscape:cx=\"" << width / 2 << "\"";
		_output->os() <<    "     inkscape:cy=\"" << height / 2 << "\"";
		_output->os() <<    "     inkscape:window-width=\"" << width << "\"";
		_output->os() <<    "     inkscape:window-height=\"" << height << "\"";
		_output->os() << R"a(     inkscape:window-x="-11")a";
		_output->os() << R"a(     inkscape:window-y="-11")a";
		_output->os() << R"a(     inkscape:window-maximized="1")a";
		_output->os() << R"a(     inkscape:current-layer="svg1" />)a";
		_output->os() << R"a(  <defs/>)a";
		_output->os() << R"a(     id="defs1" />)a";
	} else if (_settings->program_type == Settings::program_type_t::browser) {
		_output->get_os() <<    "<svg";
		_output->os() <<    "   width=\"" << width << "\"";
		_output->os() <<    "   height=\"" << height << "\"";
		_output->os() <<    "   viewBox=\"0 0 " <<
			_settings->display_width << " " << _settings->display_height << "\"";
		_output->os() << R"a(   version="1.1")a";
		_output->os() << R"a(xmlns="http://www.w3.org/2000/svg">)a";
	}
	_output->change_space(2);
}

void FileStructs::file_end () const {
	_output->change_space(-2);
	_output->os() << "</svg>";
}



void FileStructs::layer_begin (group_id_t layer_id, std::string const & layer_label) const {
	assert(_settings->program_type == Settings::program_type_t::inkscape);
	_output->os() <<   "<g" << "\n";
	_output->os() << R"(   inkscape:groupmode="layer")";
	_output->os() <<   "   inkscape:label=\"" << layer_label << "\"";
	_output->os() <<   "   id=\"layer" << layer_id << "\">";
	_output->change_space(2);
}

void FileStructs::layer_begin (group_id_t layer_id) const {
	assert(_settings->program_type == Settings::program_type_t::inkscape);
	_output->os() <<   "<g";
	_output->os() << R"(   inkscape:groupmode="layer")";
	_output->os() <<   "   inkscape:label=\"" << layer_id << "\"";
	_output->os() <<   "   id=\"layer" << layer_id << "\">";
	_output->change_space(2);
}

void FileStructs::group_begin (group_id_t group_id) const {
	_output->os() <<   "<g";
	_output->os() <<   "   id=\"g" << group_id << "\">";
	_output->change_space(2);
}

void FileStructs::group_end () const {
	_output->change_space(-2);
	_output->os() << "</g>";
}



void FileStructs::painting (painting::Fill const & fill) const {
	_output->os() << "style=\"";
	if (! fill.is_empty()) {
		_output->get_os() << "fill:#" << fill.color().col.to_string_16();
		if (fill.color().has_op()) {
			_output->get_os() << ";fill-opacity:" << fill.color().op_norm();
		}
	}
	_output->get_os() << "\"";
}

void FileStructs::painting (painting::Stroke const & stroke) const {
	_output->os() << "style=\"";
	if (! stroke.is_empty()) {
		_output->get_os() << "stroke:#" << stroke.color().col.to_string_16();
		if (stroke.color().has_op()) {
			_output->get_os() << ";stroke-opacity:" << stroke.color().op_norm();
		}
		_output->get_os() << ";stroke-width:" << stroke.width();
		_output->get_os() << ";stroke-linecap:" << linecap_to_str[int(stroke.linecap())];
		_output->get_os() << ";stroke-linejoin:" << linejoin_to_str[int(stroke.linejoin())];
	}
	_output->get_os() << "\"";
}

void FileStructs::painting (painting::Fill const & fill, painting::Stroke const & stroke) const {
	_output->os() << "style=\"";
	if (! fill.is_empty()) {
		_output->get_os() << "fill:#" << fill.color().col.to_string_16();
		if (fill.color().has_op()) {
			_output->get_os() << ";fill-opacity:" << fill.color().op_norm();
		}
	}
	if (! stroke.is_empty()) {
		_output->get_os() << "stroke:#" << stroke.color().col.to_string_16();
		if (stroke.color().has_op()) {
			_output->get_os() << ";stroke-opacity:" << stroke.color().op_norm();
		}
		_output->get_os() << ";stroke-width:" << stroke.width();
		_output->get_os() << ";stroke-linecap:" << linecap_to_str[int(stroke.linecap())];
		_output->get_os() << ";stroke-linejoin:" << linejoin_to_str[int(stroke.linejoin())];
	}
	_output->get_os() << "\"";
}

void FileStructs::painting (Paint const & paint) const {
	_output->os() << "style=\"";
	if (! paint.fill().is_empty()) {
		_output->get_os() << "fill:#" << paint.fill().color().col.to_string_16();
		if (paint.fill().color().has_op()) {
			_output->get_os() << ";fill-opacity:" << paint.fill().color().op_norm();
		}
	} else {
		_output->get_os() << "fill:none";
	}
	if (! paint.stroke().is_empty()) {
		_output->get_os() << ";stroke:#" << paint.stroke().color().col.to_string_16();
		if (paint.stroke().color().has_op()) {
			_output->get_os() << ";stroke-opacity:" << paint.stroke().color().op_norm();
		}
		_output->get_os() << ";stroke-width:" << paint.stroke().width();
		_output->get_os() << ";stroke-linecap:" << linecap_to_str[int(paint.stroke().linecap())];
		_output->get_os() << ";stroke-linejoin:" << linejoin_to_str[int(paint.stroke().linejoin())];
	}
	_output->get_os() << "\"";
}



void FileStructs::object_end () const {
	_output->get_os() << " />";
	_output->change_space(-3);
}

} // namespace graphics::two_dim::svg
