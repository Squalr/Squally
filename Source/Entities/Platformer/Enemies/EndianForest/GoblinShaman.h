#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;
class LocalizedString;

class GoblinShaman : public PlatformerEnemy
{
public:
	static GoblinShaman* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyGoblinShaman;

private:
	typedef PlatformerEnemy super;
	GoblinShaman(cocos2d::ValueMap& properties);
	~GoblinShaman();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
