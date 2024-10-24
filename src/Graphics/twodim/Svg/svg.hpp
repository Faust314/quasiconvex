#pragma once

#include "svg_config.hpp"
#include "Structs/file_structs.hpp"
#include "Structs/path.hpp"
#include "Structs/primitives.hpp"

namespace graphics::twodim::svg {

class Print {
public:
	Print ();
	void reset (std::ostream & os, Settings const & settings_);
	Print (std::ostream & os, Settings const & settings_);
	
	FileStructs const & file_structs () const;
	Path const & path () const;
	Primitives const & primitives () const;
	
private:
	Output output;
	
	FileStructs _file_structs;
	Path _path;
	Primitives _primitives;
};
	
} // namespace graphics::twodim::svg