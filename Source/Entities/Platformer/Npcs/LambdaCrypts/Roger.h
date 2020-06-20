#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Roger : public PlatformerFriendly
{
public:
	static Roger* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Roger(cocos2d::ValueMap& properties);
	virtual ~Roger();

private:
	typedef PlatformerFriendly super;
};
