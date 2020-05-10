#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Gaunt : public PlatformerFriendly
{
public:
	static Gaunt* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Gaunt(cocos2d::ValueMap& properties);
	virtual ~Gaunt();

private:
	typedef PlatformerFriendly super;
};
