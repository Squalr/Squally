#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Scaldor : public PlatformerFriendly
{
public:
	static Scaldor* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Scaldor(cocos2d::ValueMap& properties);
	virtual ~Scaldor();

private:
	typedef PlatformerFriendly super;
};
