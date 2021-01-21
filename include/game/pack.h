#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "engine/files.h"
#include "engine/logger.h"
#include "engine/manager.h"
#include "game/osu/osu!parser.h"
#include "engine/files.h"

namespace game::osu
{
	/*
	* Constructing a pack is a very costly operation
	* TODO: Lookahead for info, don't load the entire map, load only at playtime
	*/
	class pack
	{
	public:	
		pack(const std::string& directory, bool& valid)
		{
			m_directory = directory;
			m_name = directory.substr(directory.find(' '));

			std::vector<std::string> diffNames = engine::utilities::files::folderContents(directory, 0, ".osu");

			if (diffNames.empty())
				logger::log("No difficultys inside map folder!", logger::LEVEL::WARN);

			for (std::string& d : diffNames)
			{
				std::ifstream stream(d);
				osuParser::OsuParser p(&stream, directory);

				if(p.Parse())
					m_diffs.push_back(p);
				else
					throw "the fuck?";
			}

			logger::log("Pack processed!", logger::LEVEL::OK);
		}

		osuParser::OsuParser get() {
			return m_diffs[0];
		}

	private:
		std::string m_directory;
		std::string m_name;

		std::vector<osuParser::OsuParser> m_diffs;
	};
}