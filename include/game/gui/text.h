
#pragma once

#include <functional>

#include "engine/widget.h"
#include "engine/holder.h"

namespace game::gui
{   
    class text : public engine::gui::widget
    {
    public:
        text(const std::string& str, sf::Vector2f position = sf::Vector2f(256, 64), sf::Vector2f size = sf::Vector2f(256, 64))
        {
            m_text.setFont(engine::resource::holder::get().fonts.get("default"));
            m_text.setFillColor(sf::Color::Red);
            m_text.setCharacterSize(12);
            m_text.setPosition(position);
            this->setText(str);

            m_position = position;
        }

        void setText(const std::string& str) {
            m_text.setString(str);

            this->updateText();
        }

        void handleEvent(sf::Event e, const sf::RenderWindow& window) { };

        void render(sf::RenderTarget& renderer) {
            renderer.draw(m_text);
        }

        void setPosition(const sf::Vector2f& pos) {
            m_position = pos;

            m_text.setPosition(m_position);

            updateText();
        }

    private:
        void updateText()
        {
            m_text.setOrigin(m_text.getGlobalBounds().width / 2,
                m_text.getGlobalBounds().height / 2);
        }

        sf::Text        m_text;
    };
}