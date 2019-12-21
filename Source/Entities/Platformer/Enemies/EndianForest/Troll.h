#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class Troll : public PlatformerEnemy
{
public:
	static Troll* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKeyTroll;

private:
	typedef PlatformerEnemy super;
	Troll(cocos2d::ValueMap& properties);
	~Troll();
};
