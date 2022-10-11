#pragma once
#include <string>

#include "Entities/Platformer/PlatformerHelper.h"

class LocalizedString;

class Robot : public PlatformerHelper
{
public:
	static Robot* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Robot(cocos2d::ValueMap& properties);
	virtual ~Robot();

private:
	typedef PlatformerHelper super;
};
