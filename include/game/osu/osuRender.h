
#pragma once

#include <string>

namespace osu::render
{
	struct TextObject {
		TextObject(unsigned time, sf::Vector2f pos, std::string text) {
			this->time = time;
			this->pos = pos;
			this->text = text;
		}

		unsigned time;
		sf::Vector2f pos;
		std::string text;
	};
}