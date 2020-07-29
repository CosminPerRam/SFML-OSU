
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio.hpp>

#include "holder.h"

//add support for 3d sound

namespace sound
{
	class SoundEngine
	{
	public:
		SoundEngine(const unsigned& volume = 100, const float& pitch = 1)
		{
			m_volume = volume;
			m_pitch = pitch;
		}

		unsigned play(const std::string& resource, unsigned volume = 100, float pitch = 1)
		{
			this->update();
			sounds.emplace_back(resourceHolder::get().soundBuffers.get(resource));
			sounds[sounds.size() - 1].setVolume(volume);
			sounds[sounds.size() - 1].setPitch(pitch);
			sounds[sounds.size() - 1].play();

			return sounds.size() - 1;
		}

		unsigned play(const std::string& resource)
		{
			this->play(resource, this->m_volume);
		}

		void setVolume(unsigned& volume)
		{
			this->update();

			m_volume = volume;

			for (sf::Sound& sound : sounds)
				sound.setVolume(volume);
		}

		void setPitch(float& pitch)
		{
			this->update();

			m_pitch = pitch;

			for (sf::Sound& sound : sounds)
				sound.setPitch(pitch);
		}

		unsigned getVolume()
		{
			return m_volume;
		}

		float getPitch()
		{
			return m_pitch;
		}

		bool getAt(unsigned& index, sf::Sound* buffer)
		{
			this->update();

			if (index > sounds.size() - 1)
				return false;

			buffer = &sounds[index];

			return true;
		}

		void clear()
		{
			sounds.clear();
		}

	private:
		std::vector<sf::Sound> sounds;

		void update()
		{
			for (auto it = sounds.begin(); it != sounds.end(); )
			{
				if (it->getStatus() != sf::Music::Playing)
					it = sounds.erase(it);
				else
					it++;
			}
		}

		unsigned m_volume;
		float m_pitch;
	};
}
