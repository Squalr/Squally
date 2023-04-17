#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Pan : public PlatformerFriendly
{
public:
	static Pan* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Pan(cocos2d::ValueMap& properties);
	virtual ~Pan();

private:
	typedef PlatformerFriendly super;
};
