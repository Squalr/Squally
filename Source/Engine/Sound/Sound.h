#pragma once

#include "Engine/Sound/SoundBase.h"

class Sound : public SoundBase
{
public:
	static Sound* create(std::string soundResource = "");
	static Sound* create(cocos2d::ValueMap& properties, std::string soundResource = "");

	static const std::string MapKey;

protected:
	Sound(cocos2d::ValueMap& properties, std::string soundResource);
	virtual ~Sound();

	void initializeListeners() override;
	void freeze() override;
	void unfreeze() override;
	float getConfigVolume() override;

private:
	typedef SoundBase super;

	static const std::string PropertyKeyResource;
};
