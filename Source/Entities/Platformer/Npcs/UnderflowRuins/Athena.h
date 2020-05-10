#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Athena : public PlatformerFriendly
{
public:
	static Athena* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Athena(cocos2d::ValueMap& properties);
	virtual ~Athena();

private:
	typedef PlatformerFriendly super;
};
