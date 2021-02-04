
#include "game/osu/osuMaths.h"

unsigned osu::math::approachRateTime(float rawAR) {
	if (rawAR < 5)
		return 1200 + 600 * (5 - rawAR) / 5;
	else if (rawAR > 5)
		return 1200 + 600 * (5 - rawAR) / 5;
	else // == 5
		return 1200;
}

unsigned osu::math::fadeInTime(float rawAR) {
	if (rawAR < 5)
		return 800 + 400 * (5 - rawAR) / 5;
	else if (rawAR > 5)
		return 800 - 500 * (rawAR - 5) / 5;
	else // == 5
		return 800;
}

sf::Vector2f osu::math::screenPosition(sf::Vector2f osuPixel) {
	return { (config::screen::width / 2 - 640 / 2 + osuPixel.x), //scale to screen later
		(config::screen::height / 2 - 480 / 2 + osuPixel.y)};
}