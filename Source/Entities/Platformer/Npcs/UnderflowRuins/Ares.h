#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Ares : public PlatformerFriendly
{
public:
	static Ares* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Ares(cocos2d::ValueMap& properties);
	virtual ~Ares();

private:
	typedef PlatformerFriendly super;
};
