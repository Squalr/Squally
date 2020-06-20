#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Olive : public PlatformerFriendly
{
public:
	static Olive* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Olive(cocos2d::ValueMap& properties);
	virtual ~Olive();

private:
	typedef PlatformerFriendly super;
};
