
#pragma once

#include <algorithm>

#include "game/globals.h"
#include "engine/audio.h"

#include "game/osu/osu!parser.h"

namespace game
{
	enum mods { EZ, HR, HD, DT, HT };

	class session
	{
	public:
		void play(osuParser::OsuParser map, std::vector<unsigned> mods = {})
		{
			renderobjects.clear();

			hitobjects = map.hitObjects;

			this->m_map = map;
			this->m_mods = mods;

			this->calculate();

			m_timeRemainder = sf::Time::Zero;
			m_time.restart();

			music.play(map.m_folder + "/" + map.audioFilename);
		}

		void restart() {
			play(this->m_map, this->m_mods);
		}

		void pause()
		{
			music.pause();
			m_timeRemainder = m_timeRemainder + m_time.getElapsedTime();
		}

		void resume()
		{
			m_time.restart();
			music.resume();
		}

		bool ended() {
			return music.ended();
		}

		osuParser::OsuParser getMap() {
			return this->m_map;
		}

		void handleInput()
		{

		}

		void handleEvent(sf::Event e) 
		{
			if (e.type == sf::Event::MouseButtonPressed) {
				if (e.mouseButton.button == sf::Mouse::Left) {
					std::cout << e.mouseButton.x << " " << e.mouseButton.y << std::endl;
					for (auto obj = renderobjects.begin(); obj != renderobjects.end(); obj++) {
						if (e.mouseButton.x > obj->x - 80 && e.mouseButton.x < obj->x + 80 &&
							e.mouseButton.y > obj->y - 80 && e.mouseButton.y < obj->y + 80)
						{
							std::cout << "HIT" << std::endl;
						}
					}
				}
			}
		}

		void update(sf::Time deltaTime) 
		{
			if (hitobjects.size() > 0) {
				if (getMapTime() + c_AR > hitobjects[0].time) {
					renderobjects.push_back(hitobjects[0]);
					hitobjects.erase(hitobjects.begin());
				}
			}
		}

		void fixedUpdate(sf::Time deltaTime) 
		{
		
		}

		void render(sf::RenderTarget& renderer)
		{
			for (auto obj = renderobjects.begin(); obj != renderobjects.end(); ) {
				sf::CircleShape circle(20);
				circle.setOutlineColor(sf::Color::Red);
				circle.setOutlineThickness(1);
				circle.setPosition(obj->x, obj->y);
				renderer.draw(circle);

				if (obj->time + c_AR < getMapTime())
					obj = renderobjects.erase(obj);
				else
					obj++;
			}
		}

		unsigned long long getMapTime() {
			return (m_timeRemainder + m_time.getElapsedTime()).asMilliseconds();
		}

	private:
		void calculate()
		{
			for (unsigned mod : m_mods) {
				switch (mod) {
				case game::EZ:

					break;
				case game::HR:

					break;
				case game::DT:

					break;
				case game::HT:

					break;
				case game::HD:

					break;
				default:
					break;
				}
			}

			if (m_map.AR < 5)
			{
				c_AR = 1200 + 600 * (5 - m_map.AR) / 5;
				c_fadeIn = 800 + 400 * (5 - m_map.AR) / 5;
			}
			else if (m_map.AR > 5)
			{
				c_AR = 1200 - 750 * (m_map.AR - 5) / 5;
				c_fadeIn = 800 - 500 * (m_map.AR - 5) / 5;
			}
			else // == 5
			{
				c_AR = 1200;
				c_fadeIn = 800;
			}
		}

		osuParser::OsuParser m_map;
		std::vector<unsigned> m_mods;

		//Osu related calculations
		unsigned c_AR;
		unsigned c_fadeIn;
		//------------------------

		std::vector<osuParser::HitObject> hitobjects;

		std::vector<osuParser::HitObject> renderobjects;

		sf::Clock m_time;
		sf::Time m_timeRemainder;

		engine::MusicEngine music;
		engine::SoundEngine sounds;
	};
}