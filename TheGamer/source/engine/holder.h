
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "nonRules.h"
#include "manager.h"

class resourceHolder : public NonCopyable, public NonMovable
{
public:
    static resourceHolder& get()
    {
        static resourceHolder holder;

        return holder;
    }

    resourceManager<sf::Font> fonts;
    resourceManager<sf::Texture> textures;
    resourceManager<sf::SoundBuffer> soundBuffers;

private:
    resourceHolder()
        : fonts("fonts", "ttf"), textures("textures", "png"), soundBuffers("sfx", "ogg")
    {

    }
};