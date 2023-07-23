#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Bat : public PlatformerFriendly
{
public:
	static Bat* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Bat(cocos2d::ValueMap& properties);
	virtual ~Bat();

private:
	typedef PlatformerFriendly super;
};
