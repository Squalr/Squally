#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Brock : public PlatformerFriendly
{
public:
	static Brock* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Brock(cocos2d::ValueMap& properties);
	virtual ~Brock();

private:
	typedef PlatformerFriendly super;
};
