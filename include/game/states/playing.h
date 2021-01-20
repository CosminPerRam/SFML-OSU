
#include "engine/game.h"
#include "engine/stack.h"
#include "engine/files.h"

#include "game/globals.h"

#include "game/gui/button.h"
#include "game/gui/text.h"
#include "game/pack.h"

#include "game/states/paused.h"

#include "game/osu/osu!parser.h"

namespace game::states
{
	class playing : public state
	{
	public:
		playing(engine::Game& game, osuParser::OsuParser map) : state(game)
		{
			this->map = map;

			auto t_status = std::make_unique<game::gui::text>("PLAYING");
			m_stack.add(std::move(t_status));

			globals::music.play("res\\maps\\1 test\\audio.ogg");
		}

		void handleEvent(sf::Event e)
		{
			if (e.type == sf::Event::KeyPressed) {
				if (e.key.code == sf::Keyboard::Escape)
					m_game->pushState(std::make_unique<game::states::paused>(*m_game));
			}

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
		osuParser::OsuParser map;

		engine::gui::stack m_stack;
	};
}