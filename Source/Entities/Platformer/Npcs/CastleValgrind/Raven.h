#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Raven : public PlatformerFriendly
{
public:
	static Raven* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Raven(cocos2d::ValueMap& properties);
	virtual ~Raven();

private:
	typedef PlatformerFriendly super;
};
