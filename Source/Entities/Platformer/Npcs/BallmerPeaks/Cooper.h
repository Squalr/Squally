#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Cooper : public PlatformerFriendly
{
public:
	static Cooper* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Cooper(cocos2d::ValueMap& properties);
	virtual ~Cooper();

private:
	typedef PlatformerFriendly super;
};
