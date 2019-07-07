#pragma once

#include "Engine/Sound/SoundBase.h"

class Sound : public SoundBase
{
public:
	static Sound* create(std::string soundResource = "", bool isPositional = false);

protected:
	void initializeListeners() override;
	void onExit() override;
	void pause() override;
	void resume() override;
	float getConfigVolume() override;

private:
	typedef SoundBase super;

	Sound(std::string soundResource, bool isPositional);
	~Sound();
};
