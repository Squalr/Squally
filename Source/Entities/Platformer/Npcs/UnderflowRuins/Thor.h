#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Thor : public PlatformerFriendly
{
public:
	static Thor* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Thor(cocos2d::ValueMap& properties);
	virtual ~Thor();

private:
	typedef PlatformerFriendly super;
};
