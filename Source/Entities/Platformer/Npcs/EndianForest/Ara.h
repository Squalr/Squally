#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Ara : public PlatformerFriendly
{
public:
	static Ara* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Ara(cocos2d::ValueMap& properties);
	virtual ~Ara();

private:
	typedef PlatformerFriendly super;
};
