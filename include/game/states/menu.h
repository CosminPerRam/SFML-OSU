
#include "engine/game.h"
#include "engine/stack.h"

#include "game/gui/button.h"

#include "engine/files.h"

#include "game/pack.h"
#include "game/states/playing.h"

namespace game::states
{
	class menu : public state
	{
	public:
		menu(engine::Game& game) : state(game)
		{
			auto b = std::make_unique<game::gui::button>("Play first map");

			b->setFunction([&game]() {
				std::vector<std::string> p_maps = engine::utilities::files::folderContents("res/maps/", 1);

				for (std::string& f : p_maps)
					std::cout << f << std::endl;

				bool p_isValid = true;
				game::osu::pack p_pack(p_maps[0], p_isValid);

				std::cout << p_isValid << std::endl;
				
				game.pushState(std::make_unique<game::states::playing>(game, p_pack.get()));
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