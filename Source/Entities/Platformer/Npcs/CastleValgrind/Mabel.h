#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Mabel : public PlatformerFriendly
{
public:
	static Mabel* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Mabel(cocos2d::ValueMap& properties);
	virtual ~Mabel();

private:
	typedef PlatformerFriendly super;
};
