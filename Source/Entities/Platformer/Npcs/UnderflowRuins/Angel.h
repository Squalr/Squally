#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Angel : public PlatformerFriendly
{
public:
	static Angel* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Angel(cocos2d::ValueMap& properties);
	virtual ~Angel();

private:
	typedef PlatformerFriendly super;
};
