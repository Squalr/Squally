#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Appolo : public PlatformerFriendly
{
public:
	static Appolo* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Appolo(cocos2d::ValueMap& properties);
	virtual ~Appolo();

private:
	typedef PlatformerFriendly super;
};
