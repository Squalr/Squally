#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Lucifer : public PlatformerFriendly
{
public:
	static Lucifer* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Lucifer(cocos2d::ValueMap& properties);
	virtual ~Lucifer();

private:
	typedef PlatformerFriendly super;
};
