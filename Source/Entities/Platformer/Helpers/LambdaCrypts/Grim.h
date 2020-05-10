#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Grim : public PlatformerFriendly
{
public:
	static Grim* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	Grim(cocos2d::ValueMap& properties);
	virtual ~Grim();

private:
	typedef PlatformerFriendly super;
};
