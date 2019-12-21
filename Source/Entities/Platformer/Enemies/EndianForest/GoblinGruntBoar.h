#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class GoblinGruntBoar : public PlatformerEnemy
{
public:
	static GoblinGruntBoar* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKeyGoblinGruntBoar;

private:
	typedef PlatformerEnemy super;
	GoblinGruntBoar(cocos2d::ValueMap& properties);
	~GoblinGruntBoar();
};
