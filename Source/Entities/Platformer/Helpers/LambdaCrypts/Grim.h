#pragma once
#include <string>

#include "Entities/Platformer/PlatformerHelper.h"

class LocalizedString;

class Grim : public PlatformerHelper
{
public:
	static Grim* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Grim(cocos2d::ValueMap& properties);
	virtual ~Grim();

private:
	typedef PlatformerHelper super;
};
