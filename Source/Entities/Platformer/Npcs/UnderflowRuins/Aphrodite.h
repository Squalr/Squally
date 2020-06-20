#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Aphrodite : public PlatformerFriendly
{
public:
	static Aphrodite* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Aphrodite(cocos2d::ValueMap& properties);
	virtual ~Aphrodite();

private:
	typedef PlatformerFriendly super;
};
