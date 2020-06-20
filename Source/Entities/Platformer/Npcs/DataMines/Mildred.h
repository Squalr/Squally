#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Mildred : public PlatformerFriendly
{
public:
	static Mildred* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Mildred(cocos2d::ValueMap& properties);
	virtual ~Mildred();

private:
	typedef PlatformerFriendly super;
};
