
#include <iostream>
#include "engine/game.h"

#include <memory>
#include "engine/state.h"

#include "game/menu.h"

int main()
{
	Game m_game;
	m_game.pushState<game::states::menu>(m_game);
	m_game.run();

	return 0;
}
