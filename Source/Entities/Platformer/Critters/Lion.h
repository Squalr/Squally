#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Lion : public PlatformerFriendly
{
public:
	static Lion* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Lion(cocos2d::ValueMap& properties);
	virtual ~Lion();

private:
	typedef PlatformerFriendly super;
};
