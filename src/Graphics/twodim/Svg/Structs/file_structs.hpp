#pragma once

#include "../../../types.hpp"
#include "../svg_config.hpp"
#include "../../Painting/painting.hpp"

namespace graphics::twodim::svg {

struct FileStructs {
	FileStructs () = default;
	void init (Settings const & settings, Output & output);
	FileStructs (Settings const & settings, Output & output);
	
	void file_begin (coord_t width, coord_t height, std::string const & file_name) const;
	void file_end () const;
	
	void layer_begin (group_id_t layer_id, std::string const & layer_label) const;
	void layer_begin (group_id_t layer_id) const;
	void group_begin (group_id_t group_id) const;
	void group_end () const;
	
	void painting (paint::Fill const & fill) const;
	void painting (paint::Stroke const & stroke) const;
	void painting (paint::Fill const & fill, paint::Stroke const & stroke) const;
	void painting (Paint const & paint) const;
	
	void object_end () const;
	
private:
	Settings const * _settings = nullptr;
	Output * _output = nullptr;
};

} // namespace graphics::twodim::svg