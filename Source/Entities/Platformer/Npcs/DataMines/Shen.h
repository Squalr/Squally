#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Shen : public PlatformerFriendly
{
public:
	static Shen* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Shen(cocos2d::ValueMap& properties);
	virtual ~Shen();

private:
	typedef PlatformerFriendly super;
};
