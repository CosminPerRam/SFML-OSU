
#pragma once

#include <string>

#include "engine/maths.h"

#include "game/config.h"

#include "game/osu/OsTypes.h"

static unsigned currentComboIndex = 1;

namespace osu::render
{
	class Object {
	public:
		virtual ~Object() = default;

		virtual void update(unsigned deltaTime) {}
		virtual void fixedUpdate(unsigned deltaTime) {}
		virtual void render(sf::RenderTarget& renderer) = 0;

		virtual unsigned getTime() = 0;
		virtual unsigned getType() {
			return 99;
		};
	};

	class TextObject : public Object {
	public:
		TextObject(unsigned time, sf::Vector2f pos, std::string text) {
			this->time = time;
			this->pos = pos;
			this->text = text;

			r_text = sf::Text(text, engine::resource::holder::get().fonts.get("default"), 8);
			r_text.setPosition(pos);
			r_text.setFillColor(sf::Color::White);
		}

		void render(sf::RenderTarget& renderer) {
			renderer.draw(r_text);
		}

		unsigned getTime() {
			return this->time;
		}

	private:
		sf::Text r_text;

		unsigned time;
		sf::Vector2f pos;
		std::string text;
	};

	class TimeRemained : public Object {
	public:
		TimeRemained(unsigned startTime, unsigned totalTime, sf::Vector2f pos) {
			this->startTime = startTime;
			this->totalTime = totalTime;
			this->pos = pos;

			r_rect.setPosition(pos);
			r_rect.setFillColor(sf::Color::Blue);
		}

		void update(unsigned deltaTime) {
			this->m_timeRemainedPrecentage = 1 - float(deltaTime - startTime) / totalTime;
			r_rect.setSize(sf::Vector2f(config::screen::width * m_timeRemainedPrecentage, 10));
		}

		void render(sf::RenderTarget& renderer) {
			renderer.draw(r_rect);
		}

		unsigned getTime() {
			return totalTime;
		}

	private:
		sf::RectangleShape r_rect;

		float m_timeRemainedPrecentage = 0;

		unsigned startTime, totalTime;
		sf::Vector2f pos;
	};

	class HitObject : public Object{
	public:
		HitObject(osu::parse::HitObject obj, unsigned mapCS, unsigned cCS, unsigned cAR) {
			this->obj = obj;

			this->mapCS = mapCS;
			this->cCS = cCS;
			this->cAR = cAR;

			if (obj.isNewCombo)
				currentComboIndex = 1;

			this->comboIndex = currentComboIndex++;

			sf::Vector2f position = osu::math::screenPosition({ float(obj.x), float(obj.y) });

			if (obj.type == 3) {
				radius = 200; //dinamically resize it by screen

				r_body.setRadius(radius);
				r_body.setOrigin(radius, radius);
				r_body.setPosition(position);
				r_body.setFillColor(sf::Color::Green);

				r_text = sf::Text("SPM", engine::resource::holder::get().fonts.get("default"), 8);
				r_text.setCharacterSize(20);
				r_text.setPosition(position);
				r_text.setFillColor(sf::Color::White);

				r_approach.setFillColor(sf::Color(0, 0, 0, 0));
				r_approach.setOrigin(radius, radius);
				r_approach.setOutlineThickness(4);
				r_approach.setOutlineColor(sf::Color::Red);
			}
			else {
				radius = cCS * mapCS;

				r_body.setRadius(radius);
				r_body.setOrigin(radius, radius);
				r_body.setPosition(position);

				r_text = sf::Text(std::to_string(comboIndex), engine::resource::holder::get().fonts.get("default"), 8);
				r_text.setCharacterSize(cCS);
				r_text.setPosition(position);
				r_text.setFillColor(sf::Color::White);

				r_approach.setFillColor(sf::Color(0, 0, 0, 0));
				r_approach.setOrigin(radius, radius);
				r_approach.setOutlineThickness(2);
			}
		}

		void update(unsigned deltaTime) {
			this->m_timeRemainedPrecentage = std::abs(float(obj.time - deltaTime) / cAR);
		}

		void render(sf::RenderTarget& renderer) {
			if (this->obj.type == 3) {
				renderer.draw(r_body);
				renderer.draw(r_text);

				unsigned outlineSize = radius - radius * m_completed;

				r_approach.setPosition(osu::math::screenPosition({ float(obj.x) - outlineSize, float(obj.y) - outlineSize }));
				r_approach.setRadius(radius + outlineSize);
				renderer.draw(r_approach);
			}
			else {
				r_body.setFillColor(sf::Color(0, 255, 0, (255 - 255 * m_timeRemainedPrecentage)));
				renderer.draw(r_body);

				renderer.draw(r_text);

				unsigned outlineSize = cCS * mapCS - cCS * mapCS * (1 - m_timeRemainedPrecentage);

				r_approach.setPosition(osu::math::screenPosition({ float(obj.x) - outlineSize, float(obj.y) - outlineSize }));
				r_approach.setRadius(cCS * mapCS + outlineSize);
				r_approach.setOutlineColor(sf::Color(255, 0, 0, (255 - 255 * m_timeRemainedPrecentage)));
				renderer.draw(r_approach);

				if (obj.slider.isSlider) {
					for (auto point : obj.slider.curvePoints) {
						//std::cout << point.x << " " << point.y << "\n";

						r_body.setPosition(osu::math::screenPosition({ float(point.x), float(point.y) }));
						renderer.draw(r_body);
					}
				}

				r_body.setPosition(osu::math::screenPosition({ float(obj.x), float(obj.y) }));
			}
		}

		/*
		This is slightly weird one:
		0 - not applicable YET || nothing happened;
		X - hitRemainedTime;
		*/
		unsigned handleEvent(sf::Event e, unsigned mapTime) {
			if (obj.type != 0)
				return 0;

			if (e.type == sf::Event::MouseButtonPressed) {
				if (e.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2f circleCoords = osu::math::screenPosition(sf::Vector2f(obj.x, obj.y));
					if (engine::math::sqroot((e.mouseButton.x - circleCoords.x) * (e.mouseButton.x - circleCoords.x) +
						(e.mouseButton.y - circleCoords.y) * (e.mouseButton.y - circleCoords.y)) < cCS * mapCS * 2) {

						this->m_completed = 1;

						return std::abs(obj.time - float(mapTime));
					}
				}
			}

			return 0;
		}

		unsigned getTime() {
			if (this->obj.type == 3)
				return this->obj.spinner.end;

			return this->obj.time;
		}

		bool isCompleted() {
			return m_completed == 1;
		}

		unsigned getType() {
			return this->obj.type;
		}

		sf::Vector2f getCoords() {
			return sf::Vector2f(obj.x, obj.y);
		}

	private:
		unsigned comboIndex;
		unsigned radius;
		
		osu::parse::HitObject obj;

		float m_timeRemainedPrecentage;
		float m_completed = 0.5; //for spinners only

		//Render objects
		sf::CircleShape r_body;
		sf::Text r_text;
		sf::CircleShape r_approach;
		//--------------

		unsigned mapCS;
		unsigned cCS, cAR;
	};
}