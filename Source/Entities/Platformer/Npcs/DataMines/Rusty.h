#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Rusty : public PlatformerFriendly
{
public:
	static Rusty* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Rusty(cocos2d::ValueMap& properties);
	virtual ~Rusty();

private:
	typedef PlatformerFriendly super;
};
