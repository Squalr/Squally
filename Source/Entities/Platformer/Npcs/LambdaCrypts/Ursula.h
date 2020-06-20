#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Ursula : public PlatformerFriendly
{
public:
	static Ursula* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Ursula(cocos2d::ValueMap& properties);
	virtual ~Ursula();

private:
	typedef PlatformerFriendly super;
};
