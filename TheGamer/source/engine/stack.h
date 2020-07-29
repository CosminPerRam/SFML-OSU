
#pragma once

#include <functional>

#include <SFML/Graphics.hpp>

#include "widget.h"
#include "nonRules.h"

//add scaling support

namespace engine::gui
{
	class stack : public NonCopyable
	{
	public:
		~stack() = default;

		void add(std::unique_ptr<gui::widget> w)
		{
			m_widgets.push_back(std::move(w));
		}

		void handleEvent(sf::Event e, const sf::RenderWindow& window) //could made this virtual = 0
		{
			for (auto& widget : m_widgets) {
				widget->handleEvent(e, window);
			}
		}

		void render(sf::RenderTarget& renderer)
		{
			for (auto& widget : m_widgets) {
				widget->render(renderer);
			}

			m_imgui();
		}

		void setIMGUI(std::function<void(void)> func)
		{
			m_imgui = func;
		}

	private:
		const sf::RenderWindow& getWindow() const
		{
			return *m_window;
		}

		const sf::RenderWindow* m_window;

		std::vector<std::unique_ptr<gui::widget>> m_widgets;

		std::function<void(void)> m_imgui = [](){};
	};
}