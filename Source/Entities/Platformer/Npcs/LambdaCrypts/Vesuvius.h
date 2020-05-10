#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Vesuvius : public PlatformerFriendly
{
public:
	static Vesuvius* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Vesuvius(cocos2d::ValueMap& properties);
	virtual ~Vesuvius();

private:
	typedef PlatformerFriendly super;
};
