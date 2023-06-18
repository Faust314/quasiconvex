#pragma once

#include <string>

namespace aux::dir {

void create_directory (std::string const & path);
void remove_directory (std::string const & path);
void clear_directory (std::string const & path);

} // namespace aux::dir