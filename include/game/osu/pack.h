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
		pack(const std::string& directory)
		{
			m_directory = directory;
			m_name = directory.substr(directory.find(' '));

			std::vector<std::string> diffNames = engine::utilities::files::folderContents(directory, 0, ".osu");

			if (diffNames.empty())
				logger::log("No difficultys inside map folder!", logger::LEVEL::WARN);

			for (std::string& d : diffNames)
			{
				osuParser::OsuParser p(d, directory);

				if(p.Parse())
					m_diffs.push_back(p);
				else
					throw "the fuck?";
			}

			logger::log("Pack processed!", logger::LEVEL::OK);
		}

		osuParser::OsuParser get(unsigned index, bool preview = false) {
			if (index > m_diffs.size() - 1)
				throw "exceeded difficulty pack index";

			std::cout << "res/maps/" + m_directory + m_diffs[index].m_fileName << std::endl;
			if(preview)
				return osuParser::OsuParser("res/maps/" + m_directory + m_diffs[index].m_fileName, m_directory);

			return m_diffs[index];
		}

		unsigned size() {
			return this->m_diffs.size();
		}

		std::string getFolderName() {
			return this->m_directory;
		}

	private:
		std::string m_directory;
		std::string m_name;

		std::vector<osuParser::OsuParser> m_diffs;
	};
}