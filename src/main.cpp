
#include <iostream>

#include "engine/game.h"
#include "engine/state.h"

#include "game/states/menu.h"
#include "game/config.h"

int main()
{
	//config::init();

	engine::Game m_game;
	m_game.pushState<game::states::menu>(m_game);
	m_game.run();

	return 0;
}
