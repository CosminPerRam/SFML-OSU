
#pragma once

#include <functional>

#include "../engine/widget.h"

namespace game::gui
{
    class button : public engine::gui::widget
    {
    public:
        button(const std::string& str, sf::Vector2f position = sf::Vector2f(256, 64), sf::Vector2f size = sf::Vector2f(256, 64))
        {
            m_button.setOutlineThickness(2);
            m_button.setOutlineColor(sf::Color::Green);
            m_button.setFillColor(sf::Color::Black);
            m_button.setSize(size);
            m_button.setPosition(position);

            m_position = position;
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
            auto pos = sf::Mouse::getPosition(window);

            switch (e.type) {
            case sf::Event::MouseButtonPressed:
                switch (e.mouseButton.button) {
                case sf::Mouse::Left:
                    if (m_button.getGlobalBounds().contains((float)pos.x, (float)pos.y)) {
                        m_function();
                    }

                default:
                    break;
                }

            default:
                break;
            }
        }

        void render(sf::RenderTarget& renderer) {
            renderer.draw(m_button);
            renderer.draw(m_text);
        }

        void setPosition(const sf::Vector2f& pos) {
            m_position = pos;

            m_button.setPosition(m_position);
            m_text.setPosition(m_position);

            updateText();
        }

        sf::Vector2f getSize() const {
            return m_button.getSize();
        }

    private:
        void updateText()
        {
            m_text.setOrigin(m_text.getGlobalBounds().width / 2,
                m_text.getGlobalBounds().height / 2);

            m_text.move(m_button.getGlobalBounds().width / 2.0f,
                m_button.getGlobalBounds().height / 2.5f);
        }

        sf::Vector2f    m_position;

        sf::RectangleShape   m_button;
        sf::Text        m_text;
        std::function<void(void)> m_function = []() {};
    };
}