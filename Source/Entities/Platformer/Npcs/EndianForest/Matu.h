#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Matu : public PlatformerFriendly
{
public:
	static Matu* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Matu(cocos2d::ValueMap& properties);
	virtual ~Matu();

private:
	typedef PlatformerFriendly super;
};
