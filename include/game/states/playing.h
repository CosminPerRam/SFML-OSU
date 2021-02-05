
#pragma once

#include "engine/game.h"
#include "engine/stack.h"
#include "engine/files.h"
#include "engine/maths.h"

#include "game/globals.h"

#include "game/gui/button.h"
#include "game/gui/text.h"
#include "game/osu/pack.h"

#include "game/states/paused.h"
#include "game/states/results.h"

#include "game/osu/OsuParser.h"
#include "game/osu/OsTypes.h"

namespace game::states
{
	class playing : public state
	{
	public:
		playing(engine::Game& game, osu::parse::OsuParser map) : state(game)
		{
			globals::gamesession.play(map);

			t_accuracy = std::make_shared<game::gui::text>("Accuracy: 0.0%", sf::Vector2f(100.0, 10));
			m_stack.add(t_accuracy);

			t_score = std::make_shared<game::gui::text>("Score: 0", sf::Vector2f(250.0, 10));
			m_stack.add(t_score);

			t_combo = std::make_shared<game::gui::text>("Combo: 0x", sf::Vector2f(350.0, 10));
			m_stack.add(t_combo);
		}

		void handleInput() {
			globals::gamesession.handleInput();
		}

		void handleEvent(sf::Event e)
		{	//input, not an event, move this
			if (e.type == sf::Event::KeyPressed) {
				if (e.key.code == sf::Keyboard::Escape)
					m_game->pushState(std::make_unique<game::states::paused>(*m_game));
			}

			m_stack.handleEvent(e, m_game->getWindow());
			globals::gamesession.handleEvent(e);
		}

		void update(sf::Time deltaTime)
		{
			globals::gamesession.update(deltaTime);

			if(globals::gamesession.ended())
				m_game->pushState<game::states::results>(*m_game);
			else
			{
				t_accuracy->setText("Accuracy: " + std::to_string(globals::gamesession.getAccuracy() * 100) + '%');
				t_score->setText("Score: " + std::to_string(globals::gamesession.getScore()));
				t_combo->setText("Combo: " + std::to_string(globals::gamesession.getCombo()) + 'x');
			}
		}

		void fixedUpdate(sf::Time deltaTime)
		{
			globals::gamesession.fixedUpdate(deltaTime);
		}

		void render(sf::RenderTarget& renderer)
		{
			globals::gamesession.render(renderer);
			m_stack.render(renderer);
		}

	private:
		std::shared_ptr<game::gui::text> t_accuracy, t_score, t_combo;

		engine::gui::stack m_stack;
	};
}