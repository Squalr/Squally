#pragma once

#include "Engine/Sound/Sound.h"

class WorldSound : public Sound
{
public:
	static WorldSound* create(std::string soundResource = "");
	static WorldSound* create(cocos2d::ValueMap& properties, std::string soundResource = "");

	static const std::string MapKey;

protected:
	WorldSound(cocos2d::ValueMap& properties, std::string soundResource);
	virtual ~WorldSound();

	void onEnterTransitionDidFinish() override;
	void update(float dt) override;

private:
	typedef Sound super;

	void updateDistanceFade();
};
