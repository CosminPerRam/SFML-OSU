
#include "engine/game.h"
#include "engine/stack.h"

#include "game/gui/button.h"

#include "engine/files.h"

#include "game/pack.h"
#include "game/states/playing.h"
#include <SFML/Graphics.hpp>

namespace game::states
{
	class menu : public state
	{
	public:
		menu(engine::Game& game) : state(game)
		{
			m_maps = engine::utilities::files::folderContents("res/maps/", 1);
			m_play = std::make_shared<game::gui::button>(m_maps[0]);

			m_play->setFunction([&]() {
				bool p_isValid = true;
				game::osu::pack p_pack(m_maps[m_at], p_isValid);

				std::cout << p_isValid << std::endl;
				
				game.pushState(std::make_unique<game::states::playing>(game, p_pack.get()));
			});

			auto exit = std::make_unique<game::gui::button>("quit", sf::Vector2f(400, 400));
			exit->setFunction([&]() {
				game.exitGame();
			});

			m_stack.add(m_play);
			m_stack.add(std::move(exit));
		}

		void handleEvent(sf::Event e)
		{
			m_stack.handleEvent(e, m_game->getWindow());

			if (e.type == sf::Event::MouseWheelScrolled) {
				if (m_at + e.mouseWheelScroll.delta > -1 && m_at + e.mouseWheelScroll.delta < m_maps.size())
				{
					m_at = m_at + e.mouseWheelScroll.delta;
					m_play->setText(m_maps[m_at]);
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

		std::vector<std::string> m_maps;

		std::shared_ptr<game::gui::button> m_play;

		engine::gui::stack m_stack;
	};
}