#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Cleopatra : public PlatformerFriendly
{
public:
	static Cleopatra* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Cleopatra(cocos2d::ValueMap& properties);
	virtual ~Cleopatra();

private:
	typedef PlatformerFriendly super;
};
