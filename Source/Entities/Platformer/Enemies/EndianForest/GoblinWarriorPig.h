#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class GoblinWarriorPig : public PlatformerEnemy
{
public:
	static GoblinWarriorPig* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKeyGoblinWarriorPig;

private:
	typedef PlatformerEnemy super;
	GoblinWarriorPig(cocos2d::ValueMap& properties);
	~GoblinWarriorPig();
};
