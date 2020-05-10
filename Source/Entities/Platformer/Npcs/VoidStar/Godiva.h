#pragma once
#include <string>

#include "Entities/Platformer/PlatformerFriendly.h"

class LocalizedString;

class Godiva : public PlatformerFriendly
{
public:
	static Godiva* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;

protected:
	Godiva(cocos2d::ValueMap& properties);
	virtual ~Godiva();

private:
	typedef PlatformerFriendly super;
};
