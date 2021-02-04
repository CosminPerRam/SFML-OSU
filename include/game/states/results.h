
#pragma once

#include "engine/game.h"
#include "engine/stack.h"
#include "engine/files.h"

#include "game/globals.h"

#include "game/gui/button.h"
#include "game/gui/text.h"
#include "game/osu/pack.h"

#include "game/states/paused.h"
#include "game/states/playing.h"

#include "game/osu/osu!parser.h"

namespace game::states
{
	class results : public state
	{
	public:
		results(engine::Game& game) : state(game)
		{
			auto b_retry = std::make_unique<game::gui::button>("retry");

			b_retry->setActivateFunction([&game]() {
				std::cout << "retry" << std::endl;

				globals::gamesession.restart();

				game.popState();
			});

			auto b_mainmenu = std::make_unique<game::gui::button>("main menu", sf::Vector2f(400.0, 200.0));

			b_mainmenu->setActivateFunction([&game]() {
				std::cout << "main menu" << std::endl;

				game.popNStates(2);
			});

			std::string results = "Results: \nScore: " + std::to_string(globals::gamesession.getScore())
				+ "\nAccuracy: " + std::to_string(globals::gamesession.getAccuracy() * 100) + '%'
				+ "\nMax combo: " + std::to_string(globals::gamesession.getMaxCombo());
			auto b_results = std::make_unique<game::gui::text>(results, sf::Vector2f(100, 20));

			m_stack.add(std::move(b_results));
			m_stack.add(std::move(b_retry));
			m_stack.add(std::move(b_mainmenu));
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