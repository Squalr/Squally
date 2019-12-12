#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class OrcWarrior : public PlatformerEnemy
{
public:
	static OrcWarrior* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKeyOrcWarrior;

private:
	typedef PlatformerEnemy super;
	OrcWarrior(cocos2d::ValueMap& properties);
	~OrcWarrior();
};
