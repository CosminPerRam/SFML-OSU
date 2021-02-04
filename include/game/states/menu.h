
#include "engine/game.h"
#include "engine/stack.h"

#include "game/gui/button.h"

#include "engine/files.h"

#include "game/osu/pack.h"
#include "game/states/playing.h"
#include <SFML/System/Vector2.hpp>

namespace game::states
{
	class menu : public state
	{
	public:
		menu(engine::Game& game) : state(game)
		{
			m_pack = std::make_shared<game::gui::button>(globals::previews[globals::previews_at].getFolderName());
			m_diff = std::make_shared<game::gui::button>(globals::previews[globals::previews_at].get(globals::previews_diff_at, true).version, sf::Vector2f(200.0, 200.0));

			m_diff->setActivateFunction([&]() {
				game.pushState(std::make_unique<game::states::playing>(game, globals::previews[globals::previews_at].get(globals::previews_diff_at)));
			});

			auto exit = std::make_unique<game::gui::button>("quit", sf::Vector2f(400.0, 400.0));
			exit->setActivateFunction([&]() {
				game.exitGame();
			});

			m_stack.add(m_pack);
			m_stack.add(m_diff);
			m_stack.add(std::move(exit));
		}

		void handleEvent(sf::Event e)
		{
			m_stack.handleEvent(e, m_game->getWindow());

			if (e.type == sf::Event::KeyPressed)
			{
				switch (e.key.code)
				{
				case sf::Keyboard::W:
					if (globals::previews_at + 1 < globals::previews.size())
					{
						globals::previews_at++;
						globals::previews_diff_at = 0;

						m_pack->setText(globals::previews[globals::previews_at].getFolderName());
						m_diff->setText(globals::previews[globals::previews_at].get(globals::previews_diff_at, true).version);
					}
					break;
				case sf::Keyboard::S:
					if (globals::previews_at - 1 > -1)
					{
						globals::previews_at--;
						globals::previews_diff_at = 0;

						m_pack->setText(globals::previews[globals::previews_at].getFolderName());
						m_diff->setText(globals::previews[globals::previews_at].get(globals::previews_diff_at, true).version);
					}
					break;
				case sf::Keyboard::E:
					if (globals::previews_diff_at + 1 < globals::previews[globals::previews_at].size())
					{
						globals::previews_diff_at++;
						m_diff->setText(globals::previews[globals::previews_at].get(globals::previews_diff_at, true).version);
					}
					break;
				case sf::Keyboard::D:
					if (globals::previews_diff_at - 1 > -1)
					{
						globals::previews_diff_at--;
						m_diff->setText(globals::previews[globals::previews_at].get(globals::previews_diff_at, true).version);
					}
					break;
				default:
					break;
				}
			}
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
		int m_at = 0;

		std::shared_ptr<game::gui::button> m_pack, m_diff;

		engine::gui::stack m_stack;
	};
}