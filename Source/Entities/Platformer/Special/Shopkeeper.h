#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Shopkeeper : public PlatformerFriendly
{
public:
	static Shopkeeper* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Shopkeeper(cocos2d::ValueMap& properties);
	virtual ~Shopkeeper();

private:
	typedef PlatformerFriendly super;
};
