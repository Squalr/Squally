#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Amelia : public PlatformerFriendly
{
public:
	static Amelia* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Amelia(cocos2d::ValueMap& properties);
	virtual ~Amelia();

private:
	typedef PlatformerFriendly super;
};
