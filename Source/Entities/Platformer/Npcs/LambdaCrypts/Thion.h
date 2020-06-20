#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Thion : public PlatformerFriendly
{
public:
	static Thion* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Thion(cocos2d::ValueMap& properties);
	virtual ~Thion();

private:
	typedef PlatformerFriendly super;
};
