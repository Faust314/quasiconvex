#include "modes.hpp"
#include "includes.hpp"

namespace modes {

void biconcave_mode () {
	biconcave::Master master;
	
	std::ifstream ifs ("main.txt");
	std::string settings_file;
	
	while (! ifs.eof()) {
		ifs >> settings_file;
		std::cout << settings_file << "\n";
		master.read(settings_file + ".txt");
		master.run();
		std::cout << "\n\n";
	}
}

} // namespace modes
