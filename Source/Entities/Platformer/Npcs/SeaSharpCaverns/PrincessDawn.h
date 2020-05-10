#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class PrincessDawn : public PlatformerFriendly
{
public:
	static PrincessDawn* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	PrincessDawn(cocos2d::ValueMap& properties);
	virtual ~PrincessDawn();

private:
	typedef PlatformerFriendly super;
};
