#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Horus : public PlatformerFriendly
{
public:
	static Horus* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Horus(cocos2d::ValueMap& properties);
	virtual ~Horus();

private:
	typedef PlatformerFriendly super;
};
