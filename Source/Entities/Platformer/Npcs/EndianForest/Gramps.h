#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Gramps : public PlatformerFriendly
{
public:
	static Gramps* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Gramps(cocos2d::ValueMap& properties);
	virtual ~Gramps();

private:
	typedef PlatformerFriendly super;
};
