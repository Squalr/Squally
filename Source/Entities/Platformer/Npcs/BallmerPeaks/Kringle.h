#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Kringle : public PlatformerFriendly
{
public:
	static Kringle* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Kringle(cocos2d::ValueMap& properties);
	virtual ~Kringle();

private:
	typedef PlatformerFriendly super;
};
