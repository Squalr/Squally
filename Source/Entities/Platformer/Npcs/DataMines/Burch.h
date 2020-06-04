#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Burch : public PlatformerFriendly
{
public:
	static Burch* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Burch(cocos2d::ValueMap& properties);
	virtual ~Burch();

private:
	typedef PlatformerFriendly super;
};
