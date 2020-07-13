#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Zana : public PlatformerFriendly
{
public:
	static Zana* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Zana(cocos2d::ValueMap& properties);
	virtual ~Zana();

private:
	typedef PlatformerFriendly super;
};
