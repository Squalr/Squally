#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Drak : public PlatformerFriendly
{
public:
	static Drak* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Drak(cocos2d::ValueMap& properties);
	virtual ~Drak();

private:
	typedef PlatformerFriendly super;
};
