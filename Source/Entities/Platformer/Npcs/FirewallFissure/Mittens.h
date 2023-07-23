#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Mittens : public PlatformerFriendly
{
public:
	static Mittens* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Mittens(cocos2d::ValueMap& properties);
	virtual ~Mittens();

private:
	typedef PlatformerFriendly super;
};
