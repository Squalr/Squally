#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class PrincessPepper : public PlatformerFriendly
{
public:
	static PrincessPepper* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	PrincessPepper(cocos2d::ValueMap& properties);
	virtual ~PrincessPepper();

private:
	typedef PlatformerFriendly super;
};
