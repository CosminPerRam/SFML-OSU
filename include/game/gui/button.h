
#pragma once

#include <functional>

#include "engine/widget.h"

#include "engine/holder.h"

namespace game::gui
{   //add function to constructor
    class button : public engine::gui::widget
    {
    public: 
        button(const std::string& str, sf::Vector2f position = sf::Vector2f(256, 64), sf::Vector2f size = sf::Vector2f(256, 64))
        {
            m_button.setOutlineThickness(2);
            m_button.setOutlineColor(sf::Color::Green);
            m_button.setFillColor(sf::Color::Black);
            m_button.setSize(size);

            m_text.setFont(engine::resource::holder::get().fonts.get("arial"));
            m_text.setFillColor(sf::Color::Red);
            m_text.setCharacterSize(12);
            m_text.setString(str);
            
            this->setPosition(position);
        }

        void setFunction(std::function<void(void)> func) {
            m_function = func;
        }

        void setText(const std::string& str) {
            m_text.setString(str);

            this->updateText();
        }

        void setTexture(const sf::Texture& tex) {
            m_button.setTexture(&tex);
        }

        void handleEvent(sf::Event e, const sf::RenderWindow& window)
        {
            if (e.type == sf::Event::MouseButtonPressed) {
                if (e.mouseButton.button == sf::Mouse::Left) {
                    auto pos = sf::Mouse::getPosition(window);
                    if (m_button.getGlobalBounds().contains((float)pos.x, (float)pos.y)) {
                        m_function();
                    }
                }
            }
        }

        void render(sf::RenderTarget& renderer) {
            renderer.draw(m_button);
            renderer.draw(m_text);
        }

        void setPosition(const sf::Vector2f& pos) {
            m_position = pos;

            m_button.setPosition(m_position);

            updateText();
        }

        sf::Vector2f getSize() const {
            return m_button.getSize();
        }

    private:
        void updateText()
        {
            m_text.setPosition(m_position.x + m_button.getGlobalBounds().width / 2 - m_text.getGlobalBounds().width / 2,
                m_position.y + m_button.getGlobalBounds().height / 2 - m_text.getGlobalBounds().height / 2);
        }

        sf::RectangleShape   m_button;
        sf::Text        m_text;
        std::function<void(void)> m_function = []() {};
    };
}