
#include "engine/maths.h"

#include "game/session.h"

void game::session::play(osuParser::OsuParser map, std::vector<unsigned> mods)
{
	renderHitObjects.clear();
	dynamicObjects.clear();

	s_combo = 0;
	s_score = 0;
	s_accuracy = 0;

	s_maxCombo = 0;

	s_nPerfects = 0;
	s_nHundreds = 0;
	s_nFifties = 0;
	s_nMisses = 0;

	hitObjects = map.hitObjects;

	this->m_map = map;
	this->m_mods = mods;

	this->calculate();

	m_timeRemainder = sf::Time::Zero;
	m_time.restart();

	music.play(map.m_folder + "/" + map.audioFilename);
}

void game::session::restart() {
	play(this->m_map, this->m_mods);
}

void game::session::pause()
{
	music.pause();
	m_timeRemainder = m_timeRemainder + m_time.getElapsedTime();
}

void game::session::resume()
{
	m_time.restart();
	music.resume();
}

void game::session::handleInput()
{

}

void game::session::handleEvent(sf::Event e)
{
	if (e.type == sf::Event::MouseButtonPressed) {
		if (e.mouseButton.button == sf::Mouse::Left) {
			for (auto obj = renderHitObjects.begin(); obj != renderHitObjects.end(); ) {
				sf::Vector2f circleCoords = osu::math::screenPosition({ float(obj->x), float(obj->y) });
				if (engine::math::sqroot((e.mouseButton.x - circleCoords.x) * (e.mouseButton.x - circleCoords.x) +
					(e.mouseButton.y - circleCoords.y) * (e.mouseButton.y - circleCoords.y)) < c_CS * m_map.CS * 2) {
					float hitRemainedTime = std::abs(obj->time - float(getMapTime()));
					float timeRemainedPrecentage = hitRemainedTime / c_AR;

					s_combo++;

					if (hitRemainedTime < c_perfectsWindow) {
						s_nPerfects++;
						s_score += s_combo * 300;
						dynamicObjects.push_back(osu::render::TextObject(getMapTime() + 500, circleCoords, "300"));
					}
					else if (hitRemainedTime < c_hundredsWindow) {
						s_nHundreds++;
						s_score += s_combo * 300;
						dynamicObjects.push_back(osu::render::TextObject(getMapTime() + 500, circleCoords, "100"));
					}
					else if (hitRemainedTime < c_fiftiesWindow) {
						s_nFifties++;
						s_score += s_combo * 300;
						dynamicObjects.push_back(osu::render::TextObject(getMapTime() + 500, circleCoords, "50"));
					}
					else {
						s_resetCombo();
						s_nMisses++;
						dynamicObjects.push_back(osu::render::TextObject(getMapTime() + 500, circleCoords, "X"));
					}

					s_updateAccuracy();

					obj = renderHitObjects.erase(obj);
					return;
				}
				else
					obj++;
			}
		}
	}
}

void game::session::update(sf::Time deltaTime)
{
	if (hitObjects.size() > 0) {
		if (getMapTime() + c_AR > hitObjects[0].time) {
			renderHitObjects.push_back(hitObjects[0]);
			hitObjects.erase(hitObjects.begin());
		}
	}
}

void game::session::fixedUpdate(sf::Time deltaTime)
{

}

void game::session::render(sf::RenderTarget& renderer)
{
	for (auto obj = renderHitObjects.begin(); obj != renderHitObjects.end(); ) {
		sf::Vector2f position = osu::math::screenPosition({ float(obj->x), float(obj->y) });
		float timeRemainedPrecentage = std::abs((float(obj->time) - getMapTime()) / c_AR);

		sf::CircleShape circle(c_CS * m_map.CS);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(position);
		circle.setFillColor(sf::Color(0, 255, 0, (255 - 255 * timeRemainedPrecentage)));
		renderer.draw(circle);

		unsigned outlineSize = c_CS * m_map.CS - c_CS * m_map.CS * (1 - timeRemainedPrecentage);
		sf::CircleShape outed(c_CS * m_map.CS + outlineSize);
		outed.setFillColor(sf::Color(0, 0, 0, 0));
		outed.setOrigin(circle.getRadius(), circle.getRadius());
		outed.setPosition(osu::math::screenPosition({ float(obj->x) - outlineSize, float(obj->y) - outlineSize }));
		outed.setOutlineThickness(2);
		outed.setOutlineColor(sf::Color(255, 0, 0, (255 - 255 * timeRemainedPrecentage)));
		renderer.draw(outed);

		if (obj->time < getMapTime())
		{
			s_resetCombo();
			s_nMisses++;
			s_updateAccuracy();
			dynamicObjects.push_back(osu::render::TextObject(getMapTime() + 500, osu::math::screenPosition({ float(obj->x), float(obj->y) }), "X"));

			obj = renderHitObjects.erase(obj);
		}
		else
			obj++;
	}

	for (auto obj = dynamicObjects.begin(); obj != dynamicObjects.end(); ) {
		sf::Text text(obj->text, engine::resource::holder::get().fonts.get("default"), 8);
		text.setPosition(obj->pos);
		text.setFillColor(sf::Color::White);

		renderer.draw(text);

		if (obj->time < getMapTime())
			obj = dynamicObjects.erase(obj);
		else
			obj++;
	}
}

void game::session::calculate()
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

	c_AR = osu::math::approachRateTime(m_map.AR);
	c_fadeIn = osu::math::fadeInTime(m_map.AR);

	c_perfectsWindow = 79 - (m_map.OD * 6) + 0.5;
	c_hundredsWindow = 139 - (m_map.OD * 8) + 0.5;
	c_fiftiesWindow = 199 - (m_map.OD * 10) + 0.5;

	c_CS = 12;
}