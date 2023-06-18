#include "dir_struct.hpp"

#include "../Utils/dir_utils.hpp"
#include "../Utils/time_utils.hpp"

#include <filesystem>
#include <ctime>

#include <iostream>

void DirStruct::basic_init () {
	catalog = std::filesystem::current_path().parent_path().string();
	std::replace(catalog.begin(), catalog.end(), '\\', '/');
	
	output = catalog + "/output";
	time_t timer = time(nullptr);
	working_catalog = output + "/" + aux::time::date(timer);
	
	aux::dir::create_directory(output);
	aux::dir::create_directory(working_catalog);
}

std::string DirStruct::get_working_catalog () const {
	return working_catalog;
}
