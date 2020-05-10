#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class QueenElise : public PlatformerFriendly
{
public:
	static QueenElise* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	QueenElise(cocos2d::ValueMap& properties);
	virtual ~QueenElise();

private:
	typedef PlatformerFriendly super;
};
