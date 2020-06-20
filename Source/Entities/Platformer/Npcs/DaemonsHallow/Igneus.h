#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Igneus : public PlatformerFriendly
{
public:
	static Igneus* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Igneus(cocos2d::ValueMap& properties);
	virtual ~Igneus();

private:
	typedef PlatformerFriendly super;
};
