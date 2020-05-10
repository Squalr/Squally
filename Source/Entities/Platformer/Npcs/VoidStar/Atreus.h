#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Atreus : public PlatformerFriendly
{
public:
	static Atreus* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Atreus(cocos2d::ValueMap& properties);
	virtual ~Atreus();

private:
	typedef PlatformerFriendly super;
};
