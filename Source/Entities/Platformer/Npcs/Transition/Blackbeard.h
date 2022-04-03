#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Blackbeard : public PlatformerFriendly
{
public:
	static Blackbeard* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Blackbeard(cocos2d::ValueMap& properties);
	virtual ~Blackbeard();

private:
	typedef PlatformerFriendly super;
};
