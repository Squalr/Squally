#pragma once

#include "Engine/Sound/SoundBase.h"

class Sound : public SoundBase
{
public:
	static Sound* create(std::string soundResource = "");

protected:
	Sound(std::string soundResource);
	~Sound();

	void initializeListeners() override;
	void pause() override;
	void resume() override;
	float getConfigVolume() override;

private:
	typedef SoundBase super;
};
