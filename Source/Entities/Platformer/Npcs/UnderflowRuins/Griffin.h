#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Griffin : public PlatformerFriendly
{
public:
	static Griffin* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Griffin(cocos2d::ValueMap& properties);
	virtual ~Griffin();

private:
	typedef PlatformerFriendly super;
};
