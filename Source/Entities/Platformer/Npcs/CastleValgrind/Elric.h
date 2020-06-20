#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Elric : public PlatformerFriendly
{
public:
	static Elric* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Elric(cocos2d::ValueMap& properties);
	virtual ~Elric();

private:
	typedef PlatformerFriendly super;
};
