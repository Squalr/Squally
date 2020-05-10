#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Princess : public PlatformerFriendly
{
public:
	static Princess* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Princess(cocos2d::ValueMap& properties);
	virtual ~Princess();

private:
	typedef PlatformerFriendly super;
};
