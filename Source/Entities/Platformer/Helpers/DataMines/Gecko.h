#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Gecko : public PlatformerFriendly
{
public:
	static Gecko* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Gecko(cocos2d::ValueMap& properties);
	virtual ~Gecko();

private:
	typedef PlatformerFriendly super;
};
