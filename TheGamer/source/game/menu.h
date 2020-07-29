
#include "engine/game.h"
#include "engine/stack.h"

#include "game/button.h"

namespace game::states
{
	class menu : public state
	{
	public:
		menu(Game& game) : state(game)
		{
			auto b = std::make_unique<game::gui::button>("uscat");
			b->setFunction([]() {
				std::cout << "aa" << '\n';
				});

			m_stack.add(std::move(b));
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