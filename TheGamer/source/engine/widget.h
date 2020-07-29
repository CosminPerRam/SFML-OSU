
#pragma once

#include <SFML/Graphics.hpp>

#include "holder.h"

namespace engine::gui
{
	class widget
	{
	public:
		widget(sf::Vector2f position = sf::Vector2f(0.0, 0.0), const std::string resource = "", float scale = 1)
			: m_scale(scale), m_position(position)
		{
			if(resource != "")
				m_body.setTexture(resourceHolder::get().textures.get(resource));

			m_body.setPosition(position);
			m_body.setScale(scale, scale);
		}

		virtual void handleEvent(sf::Event e, const sf::RenderWindow& window) = 0;
		virtual void render(sf::RenderTarget& renderer) = 0;

	private:
		sf::Sprite m_body;

		const sf::Vector2f m_position;

		const float m_scale;
	};
}