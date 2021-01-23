
#pragma once

#include "engine/game.h"
#include "engine/stack.h"
#include "engine/files.h"

#include "game/globals.h"

#include "game/gui/button.h"
#include "game/gui/text.h"
#include "game/osu/pack.h"

#include "game/states/paused.h"
#include "game/states/results.h"

#include "game/osu/osu!parser.h"

namespace game::states
{
	class playing : public state
	{
	public:
		playing(engine::Game& game, osuParser::OsuParser map) : state(game)
		{
			globals::gamesession.play(map);

			auto t_status = std::make_unique<game::gui::text>("PLAYING");
			m_stack.add(std::move(t_status));
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
		engine::gui::stack m_stack;
	};
}