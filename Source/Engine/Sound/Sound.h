#pragma once

#include "Engine/Sound/SoundBase.h"

class Sound : public SoundBase
{
public:
	static Sound* create(std::string soundResource = "");
	static Sound* create(cocos2d::ValueMap& properties, std::string soundResource = "");

	static const std::string MapKeySound;

protected:
	Sound(cocos2d::ValueMap& properties, std::string soundResource);
	virtual ~Sound();

	void initializeListeners() override;
	void pause() override;
	void resume() override;
	float getConfigVolume() override;

private:
	typedef SoundBase super;

	static const std::string PropertyKeyResource;
};
