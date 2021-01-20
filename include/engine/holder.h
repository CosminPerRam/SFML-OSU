
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "nonRules.h"
#include "manager.h"
#include "files.h"

namespace engine::resource
{
    class holder : public NonCopyable, public NonMovable
    {
    public:
        static holder& get()
        {
            static holder t_holder;

            return t_holder;
        }

        engine::resource::manager<sf::Font> fonts;
        engine::resource::manager<sf::Texture> textures;
        engine::resource::manager<sf::SoundBuffer> soundBuffers;

    private:
        holder()
            : fonts("fonts", "ttf"), textures("textures", "png"), soundBuffers("sfx", "ogg")
        {

        }
    };

    template<typename resource>
    unsigned load(const std::string& filePath, resource& holder)
    {
        if (!engine::utilities::files::exists(filePath))
            return 0;

        if (holder.loadFromFile(filePath))
            return -1;

        return 1;
    }
}