#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Zeus : public PlatformerFriendly
{
public:
	static Zeus* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Zeus(cocos2d::ValueMap& properties);
	virtual ~Zeus();

private:
	typedef PlatformerFriendly super;
};
