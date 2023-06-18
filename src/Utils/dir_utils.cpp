#include "dir_utils.hpp"

#include <filesystem>

namespace aux::dir {

void create_directory (std::string const & path) {
	if (!std::filesystem::exists(path)) {
		std::filesystem::create_directory(path);
	}
}

void remove_directory (std::string const & path) {
	if (std::filesystem::exists(path)) {
		std::filesystem::remove_all(path);
	}
}

void clear_directory (std::string const & path) {
	remove_directory(path);
	std::filesystem::create_directory(path);
}

} // namespace aux::dir
