
#pragma once

#include "game/globals.h"
#include "engine/audio.h"

#include "game/osu/osu!parser.h"

namespace game
{
	class session
	{
	public:
		void play(osuParser::OsuParser map)
		{
			renderobjects.clear();

			hitobjects = map.hitObjects;

			std::cout << map.version << std::endl;

			this->m_map = map;

			m_timeRemainder = sf::Time::Zero;
			m_time.restart();

			music.play(map.m_folder + "/" + map.audioFilename);
		}

		void restart()
		{
			play(this->m_map);
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
				if (getMapTime() + 1000 > hitobjects[0].time) {
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

				if (obj->time + 1000 < getMapTime())
					obj = renderobjects.erase(obj);
				else
					obj++;
			}
		}

		unsigned long long getMapTime() {
			return (m_timeRemainder + m_time.getElapsedTime()).asMilliseconds();
		}

	private:
		osuParser::OsuParser m_map;
		std::vector<osuParser::HitObject> hitobjects;

		std::vector<osuParser::HitObject> renderobjects;

		sf::Clock m_time;
		sf::Time m_timeRemainder;

		engine::MusicEngine music;
		engine::SoundEngine sounds;
	};
}