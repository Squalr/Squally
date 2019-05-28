#pragma once

#include "Engine/Sound/SoundBase.h"

class Music : public SoundBase
{
public:
	static Music* create(std::string musicResource);

	void play(bool repeat = true, float startDelay = 0.0f) override;

protected:
	void initializeListeners() override;
	float getConfigVolume() override;

private:
	typedef SoundBase super;

	Music(std::string musicResource);
	~Music();
};
