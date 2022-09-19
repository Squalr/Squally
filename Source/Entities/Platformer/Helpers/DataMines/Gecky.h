#pragma once
#include <string>

#include "Entities/Platformer/PlatformerHelper.h"

class LocalizedString;

class Gecky : public PlatformerHelper
{
public:
	static Gecky* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Gecky(cocos2d::ValueMap& properties);
	virtual ~Gecky();

private:
	typedef PlatformerHelper super;
};
