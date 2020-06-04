#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Finch : public PlatformerFriendly
{
public:
	static Finch* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Finch(cocos2d::ValueMap& properties);
	virtual ~Finch();

private:
	typedef PlatformerFriendly super;
};
