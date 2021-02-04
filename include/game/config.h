
#pragma once

#include <iostream>

#include <SFML/Window/Keyboard.hpp>

#include "json.hpp"

#include "engine/files.h"

namespace config
{
	namespace screen {
		static unsigned width = 1280;
		static unsigned height = 720;
		static bool fullscreen = false;
	}
	
	namespace keybinds {

	}

	void init();

	void dump();
}