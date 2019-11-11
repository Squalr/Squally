#pragma once

#include "Engine/Sound/Sound.h"

class WorldSound : public Sound
{
public:
	static WorldSound* create(std::string soundResource = "");

protected:

private:
	typedef Sound super;

	WorldSound(std::string soundResource);
	~WorldSound();
};
