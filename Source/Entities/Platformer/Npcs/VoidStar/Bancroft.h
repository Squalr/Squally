#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Bancroft : public PlatformerFriendly
{
public:
	static Bancroft* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Bancroft(cocos2d::ValueMap& properties);
	virtual ~Bancroft();

private:
	typedef PlatformerFriendly super;
};
