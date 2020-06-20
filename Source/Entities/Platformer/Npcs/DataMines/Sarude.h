#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Sarude : public PlatformerFriendly
{
public:
	static Sarude* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Sarude(cocos2d::ValueMap& properties);
	virtual ~Sarude();

private:
	typedef PlatformerFriendly super;
};
