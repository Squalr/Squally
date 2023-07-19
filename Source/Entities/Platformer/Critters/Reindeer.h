#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Reindeer : public PlatformerFriendly
{
public:
	static Reindeer* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Reindeer(cocos2d::ValueMap& properties);
	virtual ~Reindeer();

private:
	typedef PlatformerFriendly super;
};
