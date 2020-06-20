#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Leopold : public PlatformerFriendly
{
public:
	static Leopold* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Leopold(cocos2d::ValueMap& properties);
	virtual ~Leopold();

private:
	typedef PlatformerFriendly super;
};
