#pragma once

#include "Engine/Sound/SoundBase.h"

class Sound : public SoundBase
{
public:
	static Sound* create(std::string soundResource = "");

protected:
	void initializeListeners() override;
	void onExit() override;
	float getConfigVolume() override;

private:
	typedef SoundBase super;

	Sound(std::string soundResource);
	~Sound();
};
