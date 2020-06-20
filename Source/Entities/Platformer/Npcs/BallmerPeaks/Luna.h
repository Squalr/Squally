#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Luna : public PlatformerFriendly
{
public:
	static Luna* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Luna(cocos2d::ValueMap& properties);
	virtual ~Luna();

private:
	typedef PlatformerFriendly super;
};
