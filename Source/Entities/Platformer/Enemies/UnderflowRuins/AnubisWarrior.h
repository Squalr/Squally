#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class AnubisWarrior : public PlatformerEnemy
{
public:
	static AnubisWarrior* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKey;
	
protected:
	AnubisWarrior(cocos2d::ValueMap& properties);
	virtual ~AnubisWarrior();

private:
	typedef PlatformerEnemy super;
};
