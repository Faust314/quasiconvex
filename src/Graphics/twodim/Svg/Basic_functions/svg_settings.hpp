#pragma once

#include "../../../types.hpp"
#include "../../../../Utils/Basic/types.hpp"

#include <string>
#include <cstdint>

namespace graphics::twodim::svg {

class Settings {
public:
	enum class program {inkscape, browser};
	typedef int8_t param_t;
	
	void init (program const program_type_ = program::inkscape, ::aux::precision_t precision_ = 6);
	Settings (program const program_type_ = program::inkscape, ::aux::precision_t precision_ = 6);
	
	void set_precision (::aux::precision_t const precision);
	
protected:
	program const & program_type() const;
	::aux::precision_t const & precision () const;
	
	void change_space (param_t const diff);
	std::string const & space () const;
	
private:
	program _program_type;
	::aux::precision_t _precision;
	std::string _space;
};

} // namespace graphics::twodim::svg