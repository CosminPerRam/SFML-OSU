
#pragma once

#include "engine/game.h"
#include "engine/stack.h"

#include "game/globals.h"

#include "game/gui/button.h"
#include <SFML/Graphics.hpp>

namespace game::states
{
	class paused : public state
	{
	public:
		paused(engine::Game& game) : state(game)
		{
			globals::gamesession.pause();

			auto b_retry = std::make_unique<game::gui::button>("retry");

			b_retry->setActivateFunction([&game]() {
				std::cout << "retry" << std::endl;

				globals::gamesession.restart();

				game.popState();
			});

			auto b_mainmenu = std::make_unique<game::gui::button>("main menu", sf::Vector2f(400, 200));

			b_mainmenu->setActivateFunction([&game]() {
				std::cout << "main menu" << std::endl;

				game.popNStates(2);
			});

			auto b_resume = std::make_unique<game::gui::button>("resume", sf::Vector2f(300, 400));

			b_resume->setActivateFunction([&game]() {
				std::cout << "resume" << std::endl;

				globals::gamesession.resume();

				game.popState();
			});

			m_stack.add(std::move(b_retry));
			m_stack.add(std::move(b_mainmenu));
			m_stack.add(std::move(b_resume));
		}

		void handleEvent(sf::Event e)
		{


			m_stack.handleEvent(e, m_game->getWindow());
		}

		void update(sf::Time deltaTime)
		{

		}

		void fixedUpdate(sf::Time deltaTime)
		{

		}

		void render(sf::RenderTarget& renderer)
		{
			m_stack.render(renderer);
		}

	private:
		engine::gui::stack m_stack;
	};
}