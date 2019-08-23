#pragma once
#include <string>

#include "Entities/Platformer/PlatformerEnemy.h"

class HexusOpponentData;
class LocalizedString;

class DemonShaman : public PlatformerEnemy
{
public:
	static DemonShaman* deserialize(cocos2d::ValueMap& properties);

	cocos2d::Vec2 getDialogueOffset() override;
	LocalizedString* getEntityName() override;
	static HexusOpponentData* getHexusOpponentData();

	static const std::string MapKeyDemonShaman;

private:
	typedef PlatformerEnemy super;
	DemonShaman(cocos2d::ValueMap& properties);
	~DemonShaman();

	static HexusOpponentData* HexusOpponentDataInstance;
	static const std::string HexusSaveKey;
};
