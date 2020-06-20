#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Merlin : public PlatformerFriendly
{
public:
	static Merlin* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Merlin(cocos2d::ValueMap& properties);
	virtual ~Merlin();

private:
	typedef PlatformerFriendly super;
};
