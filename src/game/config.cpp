
#include "game/config.h"

void config::init()
{
	if (engine::utilities::files::exists("config.json"))
	{
		nlohmann::json config;
		try {
			config = nlohmann::json::parse(engine::utilities::files::getFileContent("config.json"));
		}
		catch (nlohmann::json::exception e) {
			std::cout << "Couldn't parse the config.json file, wrongly formatted." << std::endl;
			return;
		}

		//parse data from file to variables
	}
}

void config::dump()
{
	nlohmann::json config;
	config["width"] = screen::width;
	config["height"] = screen::height;
	config["fullscreen"] = screen::fullscreen;

	engine::utilities::files::setFileContent("config.json", config.dump(4));
}