#include "sfmlsoundobjectinforeference.h"

namespace SpriterEngine
{

	SfmlSoundObjectInfoReference::SfmlSoundObjectInfoReference(sf::SoundBuffer &buffer)
	{
		sound.setBuffer(buffer);
	}

	void SfmlSoundObjectInfoReference::playTrigger()
	{
		if (getTriggerCount())
		{
			sound.play();
		}
	}

	void SfmlSoundObjectInfoReference::setPlaybackVolume()
	{
		sound.setVolume(100 * getVolume());
	}

	void SfmlSoundObjectInfoReference::setPlaybackPanning()
	{
		sound.setPosition(100 * getPanning(), 0, 0);
	}

}
