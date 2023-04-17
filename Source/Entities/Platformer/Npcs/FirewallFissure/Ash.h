#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Ash : public PlatformerFriendly
{
public:
	static Ash* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Ash(cocos2d::ValueMap& properties);
	virtual ~Ash();

private:
	typedef PlatformerFriendly super;
};
