#include "chart.hpp"

#include <cmath>

namespace graphics::svg::object::str {

void Chart::update_file () {
	if (file_parameters_complete()) {
		_file->set_width(
			(_left_cells.value() + _right_cells.value()) * _svg_cell.value() +
			2 * (_border_width + _extra_border_width.value())
		);
		_file->set_height(
			(_lower_cells.value() + _upper_cells.value()) * _svg_cell.value() +
			2 * (_border_width + _extra_border_width.value())
		);
	}
}



File const * Chart::get_file () const {
	assert(with_file);
	return _file;
}



bool Chart::file_parameters_complete () const {
	return
		with_file && (_file == nullptr) &&
		_svg_cell.has_value() && _extra_border_width.has_value() &&
		_left_cells.has_value() && _right_cells.has_value() &&
		_lower_cells.has_value() && _upper_cells.has_value();
}

bool Chart::chart_complete () const {
	if (with_file != (_file != nullptr)) {
		return false;
	}
	if (_chart_cell <= 0 || (_delta.has_value() == _scale.has_value())) {
		return false;
	}
	
	if (with_file) {
		return file_parameters_complete();
	} else {
		return
			_begin_externel.has_value() &&
			_end_externel.has_value() &&
			_svg_origin.has_value() &&
			(_svg_origin_relative.has_value() != _svg_origin_relative.has_value()) &&
			(_svg_cell.has_value() != (_cell_count.value() > 0)) &&
			(_end_externel->x - _begin_externel->x) > 2 * border_width() &&
			(_begin_externel->y - _end_externel->y) > 2 * border_width();
	}
}



double Chart::axis_width () const {
	return _axis_width;
}

double Chart::border_width () const {
	return _border_width;
}

double Chart::extra_border_width () const {
	assert(_extra_border_width.has_value());
	return _extra_border_width.value();
}



Chart::Point Chart::begin_internal () const {
	assert(chart_complete());
	if (with_file) {
		return Point(
			border_width(),
			extra_border_width() + border_width() + (_lower_cells.value() + _upper_cells.value()) * _svg_cell.value()
		);
	} else {
		return _begin_externel.value() + Point(border_width(), -border_width());
	}
}

Chart::Point Chart::end_internal () const {
	assert(chart_complete());
	if (with_file) {
		return Point(
			(_left_cells.value() + _right_cells.value()) * _svg_cell.value() + border_width() + extra_border_width(),
			border_width()
		);
	} else {
		return _end_externel.value() + Point(-border_width(), border_width());
	}
}

Chart::Point Chart::begin_external () const {
	assert(chart_complete());
	if (with_file) {
		return Point(
			extra_border_width()
			, (_lower_cells.value() + _upper_cells.value()) * _svg_cell.value() +
			2 * (border_width() + extra_border_width())
		);
	} else {
		return _begin_externel.value() + Point(border_width(), -border_width());
	}
}

Chart::Point Chart::end_external () const {
	assert(chart_complete());
	if (with_file) {
		return Point(
			(_left_cells.value() + _right_cells.value()) * _svg_cell.value() +
			2 * (border_width() + extra_border_width()),
			extra_border_width()
		);
	} else {
		return _end_externel.value() + Point(-border_width(), border_width());
	}
}



double Chart::internal_chart_width () const {
	assert(chart_complete());
	if (with_file) {
		return (_left_cells.value() + _right_cells.value()) * _svg_cell.value();
	} else {
		return _end_externel->x - _begin_externel->x - 2 * border_width();
	}
}

double Chart::external_chart_width () const {
	assert(chart_complete());
	if (with_file) {
		return (_left_cells.value() + _right_cells.value()) * _svg_cell.value() + 2 * border_width();
	} else {
		return _end_externel->x - _begin_externel->x;
	}
}

double Chart::internal_chart_height () const {
	assert(chart_complete());
	if (with_file) {
		return (_lower_cells.value() + _upper_cells.value()) * _svg_cell.value();
	} else {
		return _begin_externel->y - _end_externel->y - 2 * border_width();
	}
}

double Chart::external_chart_height () const {
	assert(chart_complete());
	if (with_file) {
		return (_lower_cells.value() + _upper_cells.value()) * _svg_cell.value() + 2 * border_width();
	} else {
		return _begin_externel->y - _end_externel->y;
	}
}



Chart::Point Chart::svg_origin () const {
	assert(chart_complete());
	if (with_file) {
		return Point(
			extra_border_width() + border_width() + _left_cells.value() * _svg_cell.value(),
			extra_border_width() + border_width() + _upper_cells.value() * _svg_cell.value()
		);
	} else {
		if (_svg_origin.has_value()) {
			return _svg_origin.value();
		} else {
			return Point(
				begin_internal().x * (1 - _svg_origin_relative->x) +
				end_internal().x * _svg_origin_relative->x,
				begin_internal().y * (1 - _svg_origin_relative->x) +
				end_internal().y * _svg_origin_relative->x
			);
		}
	}
}

double Chart::svg_cell () const {
	assert(chart_complete());
	if (_svg_cell.has_value()) {
		return _svg_cell.value();
	} else {
		return std::trunc(std::min(internal_chart_width(), internal_chart_height()) / _cell_count.value());
	}
}



Chart::Point const & Chart::chart_origin () const {
	return _chart_origin;
}

double Chart::chart_cell () const {
	return _chart_cell;
}



std::optional<double> Chart::delta_opt () const {
	return _delta;
}

std::optional<uint16_t> Chart::scale_opt () const {
	return _scale;
}

double Chart::delta () const {
	assert(chart_complete());
	if (_delta.has_value()) {
		return _delta.value();
	} else {
		return _svg_cell.value() / double(_scale.value());
	}
}





Chart::Chart (Chart::Point chart_origin_, double chart_cell_, uint16_t scale_) :
	_chart_origin(chart_origin_),
	_chart_cell(chart_cell_),
	_scale(scale_)
{ }





void Chart::set_axis_width (double width) {
	_axis_width = width;
}

void Chart::set_border_width (double width) {
	_border_width = width;
}



void Chart::set_with_file () {
	with_file = true;
	_begin_externel = std::nullopt;
	_end_externel = std::nullopt;
	
	_svg_origin = std::nullopt;
	_svg_origin_relative = std::nullopt;
	
	_cell_count = std::nullopt;
}

void Chart::set_without_file () {
	with_file = false;
	_extra_border_width = std::nullopt;
	
	_left_cells = std::nullopt;
	_right_cells = std::nullopt;
	_lower_cells = std::nullopt;
	_upper_cells = std::nullopt;
}



void Chart::set_file (File & file) {
	_file = &file;
	update_file();
}

void Chart::erase_file () {
	_file = nullptr;
}

void Chart::set_chart_size (double left, double right, double lower, double upper) {
	_left_cells = left;
	_right_cells = right;
	_lower_cells = lower;
	_upper_cells = upper;
	update_file();
}

void Chart::set_cell (double cell) {
	_svg_cell = cell;
	update_file();
}

void Chart::set_extra_border_width (double extra_border_width) {
	_extra_border_width = extra_border_width;
	update_file();
}

void Chart::set_chart_with_file (File & file, double left, double right, double lower, double upper, double cell) {
	_file = &file;
	_left_cells = left;
	_right_cells = right;
	_lower_cells = lower;
	_upper_cells = upper;
	_svg_cell = cell;
	_extra_border_width = border_width();
	update_file();
}







void Chart::set_external_border (Chart::Point begin, Chart::Point end) {

}

void Chart::set_external_border (File const & file) {

}



void Chart::set_svg_origin (Chart::Point const & origin) {

}

void Chart::set_svg_origin_relative (Chart::Point const & origin) {

}



void Chart::set_svg_cell (double cell) {

}

void Chart::set_svg_cell_count (uint16_t count) {

}





void Chart::set_chart_origin (Chart::Point const & chart_origin) {

}



void Chart::set_chart_cell (double cell) {

}



void Chart::set_delta (double delta_) {

}

void Chart::set_scale (uint16_t count) {

}





void Chart::print_borders (File::Layer & layer) {

}

void Chart::print_fine_grid (File::Layer & layer, uint16_t count) {

}

void Chart::print_grid (File::Layer & layer, double width) {

}

void Chart::print_arrows (File::Layer & layer, double width) {

}

} // namespace graphics::svg::object::str