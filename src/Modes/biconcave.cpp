#include "modes.hpp"
#include "includes.hpp"

namespace modes {

void biconcave_mode () {
	biconcave::Master master;
	
	std::ifstream ifs ("main.txt");
	std::string settings_file;
	
	while (! ifs.eof()) {
		ifs >> settings_file;
		std::cout << "\n\n" << settings_file << "\n";
		master.read(settings_file + ".txt");
		master.run();
	}
}

} // namespace modes
