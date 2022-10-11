#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Ralston : public PlatformerFriendly
{
public:
	static Ralston* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Ralston(cocos2d::ValueMap& properties);
	virtual ~Ralston();

private:
	typedef PlatformerFriendly super;
};
