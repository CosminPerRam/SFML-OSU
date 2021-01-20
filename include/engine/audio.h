
#pragma once

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio.hpp>

#include "holder.h"

//add support for 3d sound?

namespace engine
{
	class SoundEngine
	{
	public:
		SoundEngine(const unsigned& volume = 100, const float& pitch = 1)
		{
			m_volume = volume;
			m_pitch = pitch;
		}

		unsigned play(const sf::SoundBuffer& buffer, unsigned volume = 0, float pitch = 0)
		{
			if (volume == 0)
				volume = m_volume;
			if (pitch == 0)
				pitch = m_pitch;

			m_sounds.emplace_back(buffer);

			m_sounds[m_sounds.size() - 1].setVolume(volume);
			m_sounds[m_sounds.size() - 1].setPitch(pitch);
			m_sounds[m_sounds.size() - 1].play();

			return m_sounds.size() - 1;
		}

		unsigned play(const std::string& resource, unsigned volume = 0, float pitch = 0)
		{
			return this->play(engine::resource::holder::get().soundBuffers.get(resource), volume, pitch);
		}

		void setVolume(unsigned& volume)
		{
			this->update();

			m_volume = volume;

			for (sf::Sound& sound : m_sounds)
				sound.setVolume(volume);
		}

		void setPitch(float& pitch)
		{
			this->update();

			m_pitch = pitch;

			for (sf::Sound& sound : m_sounds)
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

	private:
		std::vector<sf::Sound> m_sounds;

		void update()
		{
			for (auto it = m_sounds.begin(); it != m_sounds.end(); )
			{
				if (it->getStatus() != sf::Music::Playing)
					it = m_sounds.erase(it);
				else
					it++;
			}
		}

		unsigned m_volume;
		float m_pitch;
	};

	class MusicEngine 
	{
	public:
		MusicEngine(const unsigned& volume = 100, const float& pitch = 1)
		{
			m_volume = volume;
			m_pitch = pitch;
		}

		void play(const std::string& filePath)
		{
			m_music.openFromFile(filePath);
			m_music.setVolume(m_volume);
			m_music.setPitch(m_pitch);
			m_music.play();
		}

		void pause() {
			m_music.pause();
		}

		void resume() {
			m_music.play();
		}

		void setVolume(unsigned& volume)
		{
			m_volume = volume;

			m_music.setVolume(volume);
		}

		void setPitch(float& pitch)
		{
			m_pitch = pitch;

			m_music.setPitch(pitch);
		}

		unsigned getVolume()
		{
			return m_volume;
		}

		float getPitch()
		{
			return m_pitch;
		}

	private:
		sf::Music m_music;

		unsigned m_volume;
		float m_pitch;
	};
}
