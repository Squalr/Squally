#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class PrincessMittens : public PlatformerFriendly
{
public:
	static PrincessMittens* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	PrincessMittens(cocos2d::ValueMap& properties);
	virtual ~PrincessMittens();

private:
	typedef PlatformerFriendly super;
};
