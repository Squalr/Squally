#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class PrincessOpal : public PlatformerFriendly
{
public:
	static PrincessOpal* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	PrincessOpal(cocos2d::ValueMap& properties);
	virtual ~PrincessOpal();

private:
	typedef PlatformerFriendly super;
};
