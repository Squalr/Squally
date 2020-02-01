#pragma once

#include "Engine/Sound/Sound.h"

class WorldSound : public Sound
{
public:
	static WorldSound* create(std::string soundResource = "");
	static WorldSound* create(cocos2d::ValueMap& properties, std::string soundResource = "");

	static const std::string MapKeyWorldSound;

protected:

private:
	typedef Sound super;

	WorldSound(cocos2d::ValueMap& properties, std::string soundResource);
	virtual ~WorldSound();
};
