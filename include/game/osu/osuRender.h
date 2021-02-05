
#pragma once

#include <string>

#include "game/osu/OsTypes.h"

static unsigned currentComboIndex = 1;

namespace osu::render
{
	class TextObject {
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

		unsigned& getTime() {
			return this->time;
		}

	private:
		sf::Text r_text;

		unsigned time;
		sf::Vector2f pos;
		std::string text;
	};

	class HitObject {
	public:
		//this is for circles only, todo an implementation for sliders, spinners
		HitObject(osu::parse::HitObject obj, unsigned mapCS, unsigned cCS, unsigned cAR) {
			this->obj = obj;

			this->mapCS = mapCS;
			this->cCS = cCS;
			this->cAR = cAR;

			if (obj.isNewCombo)
				currentComboIndex = 1;

			this->comboIndex = currentComboIndex++;

			sf::Vector2f position = osu::math::screenPosition({ float(obj.x), float(obj.y) });
			unsigned radius = cCS * mapCS;

			r_body.setRadius(radius);
			r_body.setOrigin(radius, radius);
			r_body.setPosition(position);

			r_combo = sf::Text(std::to_string(comboIndex), engine::resource::holder::get().fonts.get("default"), 8);
			r_combo.setCharacterSize(cCS);
			r_combo.setPosition(position);
			r_combo.setFillColor(sf::Color::White);

			r_approach.setFillColor(sf::Color(0, 0, 0, 0));
			r_approach.setOrigin(radius, radius);
			r_approach.setOutlineThickness(2);
		}

		void render(sf::RenderTarget& renderer, unsigned long long mapTime) {
			float timeRemainedPrecentage = std::abs(float(obj.time - mapTime) / cAR);

			r_body.setFillColor(sf::Color(0, 255, 0, (255 - 255 * timeRemainedPrecentage)));
			renderer.draw(r_body);

			renderer.draw(r_combo);

			unsigned outlineSize = cCS * mapCS - cCS * mapCS * (1 - timeRemainedPrecentage);

			r_approach.setPosition(osu::math::screenPosition({ float(obj.x) - outlineSize, float(obj.y) - outlineSize }));
			r_approach.setRadius(cCS * mapCS + outlineSize);
			r_approach.setOutlineColor(sf::Color(255, 0, 0, (255 - 255 * timeRemainedPrecentage)));
			renderer.draw(r_approach);
		}

		unsigned getTime() {
			return this->obj.time;
		}

		sf::Vector2f getCoords() {
			return sf::Vector2f(this->obj.x, this->obj.y);
		}

	private:
		unsigned comboIndex;
		
		osu::parse::HitObject obj;

		//Render objects
		sf::CircleShape r_body;
		sf::Text r_combo;
		sf::CircleShape r_approach;
		//--------------

		unsigned mapCS;
		unsigned cCS, cAR;
	};
}