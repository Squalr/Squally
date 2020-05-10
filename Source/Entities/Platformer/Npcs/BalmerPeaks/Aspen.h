#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Aspen : public PlatformerFriendly
{
public:
	static Aspen* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Aspen(cocos2d::ValueMap& properties);
	virtual ~Aspen();

private:
	typedef PlatformerFriendly super;
};
