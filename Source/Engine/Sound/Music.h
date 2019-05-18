#pragma once

#include "Engine/Sound/SoundBase.h"

class Music : public SoundBase
{
public:
	static Music* create(std::string musicResource);

protected:
	float getConfigVolume() override;

private:
	typedef SoundBase super;

	Music(std::string musicResource);
	~Music();
};
