#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class LocalizedString;

class OrcBomber : public PlatformerEnemy
{
public:
	static OrcBomber* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;

	static const std::string MapKeyOrcBomber;

private:
	typedef PlatformerEnemy super;
	OrcBomber(cocos2d::ValueMap& properties);
	~OrcBomber();
};
