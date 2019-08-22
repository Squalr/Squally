#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;

class GoblinWarriorPig : public PlatformerEnemy
{
public:
	static GoblinWarriorPig* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGoblinWarriorPig;

private:
	typedef PlatformerEnemy super;
	GoblinWarriorPig(cocos2d::ValueMap& properties);
	~GoblinWarriorPig();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
