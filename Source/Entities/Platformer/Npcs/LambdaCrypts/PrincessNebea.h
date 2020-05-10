#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class PrincessNebea : public PlatformerFriendly
{
public:
	static PrincessNebea* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	PrincessNebea(cocos2d::ValueMap& properties);
	virtual ~PrincessNebea();

private:
	typedef PlatformerFriendly super;
};
