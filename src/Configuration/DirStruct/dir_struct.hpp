#pragma once

#include <string>

class DirStruct {
public:
	DirStruct () = default;
	
	std::string get_working_catalog () const;
	
	void basic_init (std::string working_dir_name);
	
private:
	std::string catalog;
	std::string output;
	std::string working_catalog;
};