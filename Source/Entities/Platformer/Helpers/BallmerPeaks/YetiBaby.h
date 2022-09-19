#pragma once
#include <string>

#include "Entities/Platformer/PlatformerHelper.h"

class LocalizedString;

class YetiBaby : public PlatformerHelper
{
public:
	static YetiBaby* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	YetiBaby(cocos2d::ValueMap& properties);
	virtual ~YetiBaby();

private:
	typedef PlatformerHelper super;
};
