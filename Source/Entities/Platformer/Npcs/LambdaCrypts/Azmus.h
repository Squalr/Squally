#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Azmus : public PlatformerFriendly
{
public:
	static Azmus* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Azmus(cocos2d::ValueMap& properties);
	virtual ~Azmus();

private:
	typedef PlatformerFriendly super;
};
