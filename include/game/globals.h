
#pragma once

#include "engine/audio.h"

#include "game/session.h"

#include "game/osu/pack.h"

namespace globals {
	static engine::MusicEngine music;
	static engine::SoundEngine sounds;

	static game::session gamesession;

	static std::vector<osu::pack> previews;
	static int previews_at = 0;
	static int previews_diff_at = 0;

	void loadPreviews(){
		std::vector<std::string> maps = engine::utilities::files::folderContents("res/maps/", 1);

		previews.reserve(maps.size());

		for (std::string& map : maps)
		{
			std::cout << map << std::endl;
			previews.push_back(map);
		}
	}
}
