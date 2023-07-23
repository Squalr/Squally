#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Hades : public PlatformerFriendly
{
public:
	static Hades* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Hades(cocos2d::ValueMap& properties);
	virtual ~Hades();

private:
	typedef PlatformerFriendly super;
};
