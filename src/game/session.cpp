
#include "engine/maths.h"

#include "game/session.h"

void game::session::play(osu::parse::OsuParser map, std::vector<unsigned> mods)
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

	dynamicObjects.push_back(std::make_unique<osu::render::TimeRemained>(getMapTime(), music.getDuration(), sf::Vector2f(0, 700)));
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
	for (auto obj = renderHitObjects.begin(); obj != renderHitObjects.end(); ) {
		unsigned hitRemainedTime = obj->handleEvent(e, getMapTime());

		if (hitRemainedTime == 0) {
			obj++;
			continue;
		}

		s_combo++;

		sf::Vector2f circleCoords = osu::math::screenPosition(obj->getCoords());

		if (hitRemainedTime < c_perfectsWindow) {
			s_nPerfects++;
			s_score += s_combo * 300;
			dynamicObjects.push_back(std::make_unique<osu::render::TextObject>(getMapTime() + 500, circleCoords, "300"));
		}
		else if (hitRemainedTime < c_hundredsWindow) {
			s_nHundreds++;
			s_score += s_combo * 300;
			dynamicObjects.push_back(std::make_unique<osu::render::TextObject>(getMapTime() + 500, circleCoords, "100"));
		}
		else if (hitRemainedTime < c_fiftiesWindow) {
			s_nFifties++;
			s_score += s_combo * 300;
			dynamicObjects.push_back(std::make_unique<osu::render::TextObject>(getMapTime() + 500, circleCoords, "50"));
		}
		else {
			s_resetCombo();
			s_nMisses++;
			dynamicObjects.push_back(std::make_unique<osu::render::TextObject>(getMapTime() + 500, circleCoords, "X"));
		}

		s_updateAccuracy();

		obj = renderHitObjects.erase(obj);
	}
}

void game::session::update(sf::Time deltaTime)
{
	unsigned mapTime = getMapTime();

	if (hitObjects.size() > 0) {
		if (mapTime + c_AR > hitObjects[0].time) {
			renderHitObjects.push_back(osu::render::HitObject(hitObjects[0], m_map.CS, c_CS, c_AR));

			hitObjects.erase(hitObjects.begin());
		}
	}

	for (auto& obj : renderHitObjects) {
		obj.update(mapTime);
	}

	for (auto& obj : dynamicObjects) {
		obj->update(mapTime);
	}
}

void game::session::fixedUpdate(sf::Time deltaTime)
{

}

void game::session::render(sf::RenderTarget& renderer)
{
	for (auto obj = renderHitObjects.begin(); obj != renderHitObjects.end(); ) {
		obj->render(renderer);

		if (obj->getTime() < getMapTime())
		{
			if (obj->isCompleted())
			{
				obj = renderHitObjects.erase(obj);
				continue;
			}

			s_resetCombo();
			s_nMisses++;
			s_updateAccuracy();
			dynamicObjects.push_back(std::make_unique<osu::render::TextObject>(getMapTime() + 500, osu::math::screenPosition(obj->getCoords()), "X"));

			obj = renderHitObjects.erase(obj);
		}
		else
			obj++;
	}
	
	for (auto obj = dynamicObjects.begin(); obj != dynamicObjects.end(); ) {
		obj->get()->render(renderer);

		if (obj->get()->getTime() < getMapTime())
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