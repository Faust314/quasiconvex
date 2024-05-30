#include "dir_struct.hpp"

#include "../../Utils/Basic/dir_utils.hpp"
#include "../../Utils/Basic/time_utils.hpp"

#include <filesystem>
#include <ctime>
#include <algorithm>

#include <iostream>

void DirStruct::basic_init (std::string working_dir_name) {
	catalog = std::filesystem::current_path().string();
	std::replace(catalog.begin(), catalog.end(), '\\', '/');
	
	output = catalog + "/output";
	time_t timer = time(nullptr);
	working_catalog = output + "/" + working_dir_name;
	
	aux::dir::create_directory(output);
	aux::dir::clear_directory(working_catalog);
}

std::string DirStruct::get_working_catalog () const {
	return working_catalog;
}
