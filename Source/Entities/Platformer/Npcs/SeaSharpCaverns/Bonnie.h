#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Bonnie : public PlatformerFriendly
{
public:
	static Bonnie* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Bonnie(cocos2d::ValueMap& properties);
	virtual ~Bonnie();

private:
	typedef PlatformerFriendly super;
};
