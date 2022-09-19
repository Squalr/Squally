#pragma once
#include <string>

#include "Entities/Platformer/PlatformerHelper.h"

class LocalizedString;

class Snowman : public PlatformerHelper
{
public:
	static Snowman* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Snowman(cocos2d::ValueMap& properties);
	virtual ~Snowman();

private:
	typedef PlatformerHelper super;
};
