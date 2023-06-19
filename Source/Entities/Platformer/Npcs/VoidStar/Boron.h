#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Boron : public PlatformerFriendly
{
public:
	static Boron* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Boron(cocos2d::ValueMap& properties);
	virtual ~Boron();

private:
	typedef PlatformerFriendly super;
};
