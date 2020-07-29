
#pragma once

#include <SFML/Graphics.hpp>

#include "nonRules.h"

class Game;

class state : public NonCopyable
{
public:
	state(Game& game) : m_game(&game)
	{

	}

	virtual ~state() = default;

	virtual void handleEvent(sf::Event e) {}
	virtual void handleInput() {}
	virtual void update(sf::Time deltaTime) {}
	virtual void fixedUpdate(sf::Time deltaTime) {}
	virtual void render(sf::RenderTarget& renderer) = 0;

protected:
	Game* m_game;
};