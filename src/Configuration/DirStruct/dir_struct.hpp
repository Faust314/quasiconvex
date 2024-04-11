#pragma once

#include <string>

class DirStruct {
public:
	DirStruct() = default;
	
	std::string get_working_catalog() const;
	
	void basic_init();
	
private:
	std::string catalog;
	std::string output;
	std::string working_catalog;
};