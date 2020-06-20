#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Juniper : public PlatformerFriendly
{
public:
	static Juniper* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Juniper(cocos2d::ValueMap& properties);
	virtual ~Juniper();

private:
	typedef PlatformerFriendly super;
};
