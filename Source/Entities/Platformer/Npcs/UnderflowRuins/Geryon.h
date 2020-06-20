#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Geryon : public PlatformerFriendly
{
public:
	static Geryon* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Geryon(cocos2d::ValueMap& properties);
	virtual ~Geryon();

private:
	typedef PlatformerFriendly super;
};
