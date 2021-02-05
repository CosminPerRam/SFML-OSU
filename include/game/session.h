
#pragma once

#include <algorithm>

#include "engine/audio.h"

#include "game/osu/OsuParser.h"
#include "game/osu/osuMaths.h"

#include "game/osu/OsuRender.h"

namespace game
{
	enum mods { EZ, HR, HD, DT, HT };

	class session
	{
	public:
		void play(osu::parse::OsuParser map, std::vector<unsigned> mods = {});
		void restart();
		void pause();
		void resume();

		bool ended() {
			return music.ended();
		}

		osu::parse::OsuParser getMap() {
			return this->m_map;
		}

		void handleInput();
		void handleEvent(sf::Event e);

		void update(sf::Time deltaTime);
		void fixedUpdate(sf::Time deltaTime);

		void render(sf::RenderTarget& renderer);

		unsigned long long getMapTime() {
			return (m_timeRemainder + m_time.getElapsedTime()).asMilliseconds();
		}

		unsigned getCombo() {
			return s_combo;
		}

		unsigned getScore() {
			return s_score;
		}

		float getAccuracy() {
			return s_accuracy;
		}

		unsigned getMaxCombo() {
			return s_maxCombo;
		}

		unsigned getPerfects() {
			return s_nPerfects;
		}

		unsigned getHundreds() {
			return s_nHundreds;
		}

		unsigned getFifties() {
			return s_nFifties;
		}

		unsigned getMisses() {
			return s_nMisses;
		}

	private:
		void calculate();

		osu::parse::OsuParser m_map;
		std::vector<unsigned> m_mods;

		//Osu related calculations
		unsigned c_AR;
		unsigned c_fadeIn;

		float c_perfectsWindow;
		float c_hundredsWindow;
		float c_fiftiesWindow;

		unsigned c_CS;
		//------------------------
		//Stats
		unsigned s_combo;
		unsigned s_score;
		float s_accuracy;

		unsigned s_maxCombo;
		
		unsigned s_nPerfects;
		unsigned s_nHundreds;
		unsigned s_nFifties;
		unsigned s_nMisses;

		void s_resetCombo() {
			if (s_combo > s_maxCombo)
				s_maxCombo = s_combo;

			s_combo = 0;
		}

		void s_updateAccuracy() {
			s_accuracy = float(50 * s_nFifties + 100 * s_nHundreds + 300 * s_nPerfects)
				/ (300 * (s_nMisses + s_nFifties + s_nHundreds + s_nPerfects));
		}
		//------------------------

		std::vector<osu::parse::HitObject> hitObjects;

		std::vector<osu::render::HitObject> renderHitObjects;
		std::vector<osu::render::TextObject> dynamicObjects;

		sf::Clock m_time;
		sf::Time m_timeRemainder;

		engine::MusicEngine music;
		engine::SoundEngine sounds;
	};
}