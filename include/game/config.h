
#pragma once

#include "json.hpp"

#include "engine/files.h"

namespace config
{
	static unsigned width = 1280;
	static unsigned height = 720;
	static bool fullscreen = false;

	void init()
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

	void dump()
	{
		nlohmann::json config;
		config["width"] = width;
		config["height"] = height;
		config["fullscreen"] = fullscreen;
	
		engine::utilities::files::setFileContent("config.json", config.dump(4));
	}
}