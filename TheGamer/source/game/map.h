#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

#include "difficulty.h"
#include "../engine/files.h"
#include "../engine/logger.h"

namespace game::osu
{
	class map
	{
	public:	//constructing a map is a very performance costly operation
		map(const std::string& directory, bool& valid)
		{
			std::vector<std::string> diffNames = engine::utilities::files::folderContents(directory, 2, ".osu");

			if (diffNames.empty())
			{
				logger::log("No difficultys inside map folder!", logger::LEVEL::WARN);
				valid = false;
				return;
			}

			bool isDiffValid = true;
			for (std::string& d : diffNames)
			{
				game::osu::difficulty diff = game::osu::difficulty(d, isDiffValid);

				if (isDiffValid)
					m_diffs.emplace_back(diff);

				isDiffValid = true;
			}

			if(m_diffs.empty())
			{
				logger::log("No valid difficultys inside the map folder!", logger::LEVEL::WARN);
				valid = false;
				return;
			}

			m_name = directory.substr(directory.find(' '));

			logger::log("Map loaded!", logger::LEVEL::OK);
			valid = true;
			return;
		}

	private:
		std::string m_name;

		std::vector<game::osu::difficulty> m_diffs;
	};
}