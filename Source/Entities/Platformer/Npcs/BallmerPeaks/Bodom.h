#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Bodom : public PlatformerFriendly
{
public:
	static Bodom* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Bodom(cocos2d::ValueMap& properties);
	virtual ~Bodom();

private:
	typedef PlatformerFriendly super;
};
