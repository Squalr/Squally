#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Brine : public PlatformerFriendly
{
public:
	static Brine* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Brine(cocos2d::ValueMap& properties);
	virtual ~Brine();

private:
	typedef PlatformerFriendly super;
};
