
#pragma once

#include <SFML/System/Vector2.hpp>

#include "game/config.h"

namespace osu::math
{
	unsigned approachRateTime(float rawAR);

	unsigned fadeInTime(float rawAR);

	sf::Vector2f screenPosition(sf::Vector2f osuPixel);
}