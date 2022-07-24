#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Gull : public PlatformerFriendly
{
public:
	static Gull* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Gull(cocos2d::ValueMap& properties);
	virtual ~Gull();

private:
	typedef PlatformerFriendly super;
};
